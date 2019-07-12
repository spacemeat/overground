#include "utils.h"
#include "worker.h"
#include "job.h"
#include "jobManager.h"

using namespace std;
using namespace std::chrono_literals;
using namespace overground;

constexpr bool debugOut = true;
constexpr bool spamOut = false;


Worker::Worker(JobManager * jobManager, int workerId)
: jobManager(jobManager),
  id(workerId),
  thread([this]{ this->threadFn(); }),
  jobReadyWaitDuration(1ms)
{
}


Worker::Worker(Worker const & rhs)
: jobManager(rhs.jobManager),
  thread([this]{ this->threadFn(); }),
  jobReadyWaitDuration(1ms)
{
}


Worker::~Worker()
{
}


void Worker::start()
{
  if (running == false)
  {
    log(thId, fmt::format("start() worker {}", id));
  
    running = true;
    cv_start.notify_one();
  }
}


// NOTE: The thread that is getting nudged may
// not be the thread that takes the next task.
// Just so's ya know.
bool Worker::nudge()
{
  if (available)
  {
    log(thId, fmt::format("nudge() worker {}", id));
    cv_jobReady.notify_one();
    return true;
  }

  return false;
}


void Worker::stop()
{
  log(thId, fmt::format("stop() worker {}", id));
  running = false;
}


void Worker::die()
{
  log(thId, fmt::format("die() worker {}", id));
  dying = true;
  running = false;
  // don't even wait for the timeout; just die now pls
  cv_jobReady.notify_one();   // in case we're waiting for jobs
  cv_start.notify_one();      // in case we're stopped
}


void Worker::joinDyingThread()
{
  thread.join();
}


Job * Worker::getNextJob()
{
  Job * jayobee = nullptr;
  while (running && jayobee == nullptr)
  {
    log(thId, logTags::verb, "trying to dequeue.");
    jayobee = jobManager->dequeueJob();
    if (jayobee != nullptr)
    {
      log(thId, "got a job.");
      break;
    }

    log(thId, logTags::verb, "got no job; waiting for nudge or timeout.");

    {
      auto lock = unique_lock<mutex>(mx_jobReady);
      available = true;
      cv_jobReady.wait_for(lock, jobReadyWaitDuration);

      log(thId, logTags::verb, "got nudged or timeout waiting.");
    }
  }

  available = (jayobee == nullptr);
  return jayobee;
}


void Worker::threadFn()
{
  thId = createLogChannel(
    fmt::format("wk {}", id), logTags::dbg, logTags::dev, & cout, & coutMx);

  log(thId, "thread start");
  
  while (dying == false)
  {
    while (running == false && dying == false)
    {
      log(thId, "lock start mx.");
      auto lock = unique_lock<mutex>(mx_start);

      log(thId, "wait for start notify.");
      cv_start.wait(lock, [&]{ return running || dying; });
    }

    if (dying == false)
    {
      log(thId, "getting next job.");

      Job * jayobee = getNextJob();
      if (jayobee != nullptr)
      {
        log(thId, "running job.");
        jayobee->run(jobManager);

        log(thId, "did job.");
        jobManager->jobDone();
      }
      else
      {
        log(thId, "bored now.");
      }
      
      // NOTE: Here we forget jayobee. Its lifetime has to
      // be managed elsewise.
    }
  }

  log(thId, "about to die.");

  // Calling this results in the destructor being called.
  // DO NOTHING with *this after this call.
  jobManager->workerDying(id);
}

