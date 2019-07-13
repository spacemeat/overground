#include "jobManager.h"
#include "job.h"
#include "worker.h"
#include "utils.h"
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
  try
  {
    stopAndJoin();
  }
  catch(const std::exception& e)
  {
    log(thId, fmt::format("Caught an error in ~JobManager(): {}", e.what()));
  }
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


void JobManager::setNumEmployedWorkers(
  unsigned int numWorkers)
{
  log(thId, fmt::format("JobManager::setNumEmployedWorkers({})", 
    numWorkers));

  lock_guard lock(mxWorkers);

  numWorkers = std::min((size_t) numWorkers, workers.size());

  for (unsigned int i = 0; i < numWorkers; ++i)
  {
    if (workers[i]->isEmployed() == false)
      { workers[i]->start(); }
  }

  for (unsigned int i = numWorkers; i < workers.size(); ++i)
  {
    if (workers[i]->isEmployed())
      { workers[i]->stop(); }
  }
}


void JobManager::increaseNumEmployedWorkers(
  unsigned int numWorkers)
{
  setNumEmployedWorkers(workers.size() + numWorkers);
}


void JobManager::decreaseNumEmployedWorkers(
  unsigned int numWorkers, Worker * callingWorker)
{
  setNumEmployedWorkers(workers.size() - min(
    static_cast<unsigned int>(workers.size()), numWorkers));
}


void JobManager::stopAndJoin()
{
  log(thId, "JobManager::stopAndJoin()");

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
    auto lock = lock_guard<mutex>(mxJobs);
    jobs.push_back(job);
  }

  // Check if any threads are asleep, and nudge one if so
  for (auto worker : workers)
  {
    if (worker->isEmployed() && 
        worker->isTasked() == false)
    {
      worker->nudge();
      break;
    }
  }
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

  // Check if any threads are asleep, and nudge as many as we can/need if so
  for (auto worker : workers)
  {
    if (worker->isEmployed() && 
        worker->isTasked() == false)
    {
      worker->nudge();

      if (--numJobs == 0)
        { break; }
    }
  }
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


void JobManager::workerDying(int workerId)
{
  log(thId, fmt::format("JobManager::workerDying({})", workerId));
}


Job * JobManager::dequeueJob()
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
    return nullptr;
  }
}
