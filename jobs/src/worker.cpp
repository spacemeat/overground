#include "worker.h"
#include "job.h"
#include "jobManager.h"

using namespace std;
using namespace std::chrono_literals;
using namespace overground;


Worker::Worker(JobManager * jobManager)
: jobManager(jobManager),
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
  dying = true;
  running = false;
  thread.join();
}


void Worker::start()
{
  if (running == false)
  {
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
    cv_jobReady.notify_one();
    return true;
  }

  return false;
}


void Worker::stop()
{
  running = false;
}


void Worker::join()
{
  thread.join();
}


Job * Worker::getNextJob()
{
  Job * jayobee = nullptr;
  while (running && jayobee == nullptr)
  {
    jayobee = jobManager->dequeueJob();
    if (jayobee != nullptr)
      { break; }

    {  
      auto lock = unique_lock<mutex>(mx_jobReady);
      available = true;
      cv_jobReady.wait_for(lock, jobReadyWaitDuration);
    }
  }

  available = (jayobee == nullptr);
  return jayobee;  
}


void Worker::threadFn()
{
  while (dying == false)
  {
    while (running == false && dying == false)
    {
      auto lock = unique_lock<mutex>(mx_start);
      cv_start.wait(lock, [&]{ return running || dying; });
    }

    if (dying == false)
    {
      Job * jayobee = getNextJob();
      if (jayobee != nullptr)
      {
        jayobee->run(jobManager);
        jobManager->jobDone();
      }
      // NOTE: Here we forget jayobee. Its lifetime has to
      // be managed elsewise.
    }
  }
}

