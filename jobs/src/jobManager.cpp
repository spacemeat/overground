#include "jobManager.h"
#include "job.h"
#include "worker.h"
#include "utils.h"
#include "framePlan.h"
#include <thread>
#include <cassert>
#include <algorithm>

using namespace std;
using namespace overground;


unsigned int JobManager::getNumCores()
{
  return std::thread::hardware_concurrency();
}


JobManager::JobManager()
{
}


JobManager::~JobManager()
{
}


void JobManager::allocateWorkers(unsigned int numWorkers)
{
  if (workers.size() > 0)
  {
    throw runtime_error("Not currently supporting changing the workers once they're running.");
  }
 
  workers.reserve(numWorkers);
  int nextWorkerId = 0;

  while (workers.size() < numWorkers)
  { 
    workers.emplace_back(
      new Worker(this, nextWorkerId ++));
  }
}


void JobManager::increaseNumEmployedWorkers(
  unsigned int numWorkers)
{
  lock_guard lock(mxWorkers);

  setNumEmployedWorkers_int(numEmployedWorkers + numWorkers);
}


void JobManager::decreaseNumEmployedWorkers(
  unsigned int numWorkers)
{
  lock_guard lock(mxWorkers);

  setNumEmployedWorkers_int(numEmployedWorkers - min(
    static_cast<unsigned int>(numEmployedWorkers), numWorkers));
}


void JobManager::setNumEmployedWorkers(
  unsigned int numWorkers)
{
  lock_guard lock(mxWorkers);

  setNumEmployedWorkers_int(numWorkers);
}


void JobManager::setNumEmployedWorkers_int(
  unsigned int numWorkers)
{
  log(thId, fmt::format("JobManager::setNumEmployedWorkers({})", 
    numWorkers));

  numEmployedWorkers = std::min((size_t) numWorkers, workers.size());

  for (unsigned int i = 0; 
       i < numEmployedWorkers; ++i)
  {
    if (workers[i]->isEmployed() == false)
      { workers[i]->start(); }
  }

  for (unsigned int i = numEmployedWorkers; 
       i < workers.size(); ++i)
  {
    if (workers[i]->isEmployed())
      { workers[i]->stop(); }
  }
}


void JobManager::stopAndJoin()
{
  logFn();

  running = false;
  setNumEmployedWorkers(0);

  for (auto worker : workers)
    { worker->die(); }

  for (auto worker : workers)
    { worker->join(); }
}


void JobManager::enqueueJob(Job * job)
{
  job->setPending();
  
  {
    lock_guard<mutex> lock(mxJobs);
    jobs.push_back(job);
  }

  nudgeAnyone();
}


void JobManager::enqueueJobs(stack<Job *> jobGroup)
{
  auto numJobs = jobGroup.size();
  if (numJobs == 0)
    { return; }

  while(jobGroup.size() != 0)
  {
    auto job = jobGroup.top();
    jobGroup.pop();

    job->setPending();
  
    {
      auto lock = lock_guard<mutex>(mxJobs);
      jobs.push_back(job);
    }
  }

  nudgeManyone(numJobs);
}


int JobManager::getNumJobsEnqueued()
{
  int num = 0;

  {
    auto lock = lock_guard<mutex>(mxJobs);
    num = jobs.size();
  }
  
  return num;
}


void JobManager::nudgeAnyone(Worker * but)
{
  lock_guard<mutex> lock(mxWorkers);
  for (auto worker : workers)
  {
    if (worker != but && 
        worker->isEmployed() && 
        worker->isTasked() == false)
    { 
      worker->nudge();
      break;
    }
  }
}


void JobManager::nudgeManyone(size_t howMany, Worker * but)
{
  lock_guard<mutex> lock(mxWorkers);
  size_t numNudged = 0;

  // Check if any threads are asleep, and nudge as many as we can/need if so
  for (auto worker : workers)
  {
    if (worker->isEmployed() && 
        worker->isTasked() == false)
    {
      worker->nudge();

      if (++numNudged == howMany)
        { break; }
    }
  }
}


void JobManager::nudgeEveryone(Worker * but)
{
  lock_guard<mutex> lock(mxWorkers);
  for (auto worker : workers)
  {
    if (worker != but && 
        worker->isEmployed() && 
        worker->isTasked() == false)
      { worker->nudge(); }
  }
}


void JobManager::workerDying(int workerId)
{
  log(thId, fmt::format("JobManager::workerDying({})", workerId));
}

// TODO: Get this into engine.
size_t frameId = 0;

Job * JobManager::dequeueJob(Worker * worker)
{
  auto lock = lock_guard<mutex>(mxJobs);
  if (jobs.size() != 0)
  {
    auto job = jobs.front();
    jobs.pop_front();
    ++ numJobsStarted;
    return job;
  }
  else
  {
    // if we're the first worker to notice that the phase needs to change,
    if (changingPhase == false)
    {
      unique_lock<std::mutex> phaseLock(mxPhaseBarrier);

      do
      {
        // get some phase info
        auto & phases = framePlan->getPhases();

        auto newPhaseIdx = nextPhaseIdx;
        nextPhaseIdx = newPhaseIdx + 1;
        if (nextPhaseIdx >= phases.size())
        {
          frameId += 1;
          nextPhaseIdx %= phases.size();
        }

        auto & phase = phases[newPhaseIdx];

        log(thId, logTags::phase, fmt::format("{}frame {}{}{}: phase {}{}{} - {}{}{} ({}{}{}): {}{}{} jobs{}",
          ansi::darkBlue,
          ansi::lightBlue, frameId, ansi::darkBlue,
          ansi::lightBlue, newPhaseIdx, ansi::darkBlue,
          ansi::lightBlue, phase.getName(), ansi::darkBlue,
          ansi::lightBlue, to_string(phase.getKind()), ansi::darkBlue,
          ansi::lightBlue, phase.getJobBoard().getNumJobs(), ansi::darkBlue,
          ansi::off));
        
        auto numJobs = phase.getJobBoard().getNumJobs();
        auto traits = phaseKindTraits[newPhaseIdx];
        bool runBarrier = true;

        if (phase.hasBarrierJob() == false)
          runBarrier = false;
        if (numJobs == 0 && traits.skipBarrierJobIfEmpty)
          runBarrier = false;

        if (runBarrier)
        {
          log(thId, logTags::barrier, fmt::format("{}**** {}BARRIER UP{} ****{}", ansi::darkBlue, ansi::lightYellow, ansi::darkBlue, ansi::off));
          // tell all workers to wait on the phase barrier
          changingPhase = true;
          // wait for n workers to check in
          mxJobs.unlock();
          cvPhaseBarrier.wait(phaseLock, [&, worker]
          {
            // Is every other employed worker untasked? If so, we're done waiting, and can run the transition job. After that, we set JM's phase and nudge everyone else to get going again.
            lock_guard<mutex> lock(mxWorkers);
            return all_of(workers.begin(),
              workers.end(), [&, worker](auto w) 
                { return w->isEmployed() == false ||
                  w->isTasked() == false ||
                  w == worker; });
          });
//          mxJobs.lock();

          log(thId, logTags::barrier, fmt::format("{}**** {}BARRIER JOINED{} ****{}", ansi::darkBlue, ansi::lightYellow, ansi::darkBlue, ansi::off));
        }

        // Get the next phase's jobs
        phase.forEachJob([this](auto job)
          {
            job->setPending();
            jobs.push_back(job);
          });

        auto barrierJob = phase.getBarrierJob();
        if (barrierJob != nullptr)
        {
          if (runBarrier)
          {
            // perform first job (sets renderpass, etc) synchronously
            ++ numJobsStarted;
            barrierJob->setScheduleKind(ScheduleKind::synchronous);
            barrierJob->run();
            jobDone();
          }
          else
          {
            barrierJob->skip();
          }
        }

        // change the phase index on jobManager
        phaseIdx = newPhaseIdx;
      } while (jobs.size() == 0);

      // clear workers' obligations to wait on the phase barrier
      changingPhase = false;

      // we're here to dequeue after all
      Job * job = jobs.front();
      jobs.pop_front();

      //mxJobs.unlock();

      return job;
    }
    else // else, if we were not the first to notice we need to change phase, let the lucky winner know we're done. Note that these aren't counted; every time we notify, it checks the state of all workers.
    {
      cvPhaseBarrier.notify_one();
      return nullptr;
    }
    return nullptr;
  }
}

