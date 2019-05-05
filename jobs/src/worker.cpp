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


void Worker::die()
{
  sout { debugOut } << "....Worker " << id << " sentenced to death." << endl;
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
    sout { spamOut } << "....Worker " << id << " trying to dequeue." << endl;
    jayobee = jobManager->dequeueJob();
    if (jayobee != nullptr)
    {
      sout { debugOut } << "++++Worker " << id << " got a job." << endl;
      break;
    }

    sout { spamOut } << "....Worker " << id << " got no job, waiting for nudge or tineout." << endl;

    {
      auto lock = unique_lock<mutex>(mx_jobReady);
      available = true;
      cv_jobReady.wait_for(lock, jobReadyWaitDuration);

      sout { spamOut } << "....Worker " << id << " got nudged or timed out waiting." << endl;
    }
  }

  available = (jayobee == nullptr);
  return jayobee;  
}


void Worker::threadFn()
{
  sout { debugOut } << "....Worker " << id << " thread start." << endl;
  
  while (dying == false)
  {
    while (running == false && dying == false)
    {
      sout { debugOut } << "....Worker " << id << " lock start mx." << endl;
      auto lock = unique_lock<mutex>(mx_start);

      sout { debugOut } << "....Worker " << id << " wait for start notify." << endl;
      cv_start.wait(lock, [&]{ return running || dying; });
    }

    if (dying == false)
    {
      sout { debugOut } << "....Worker " << id << " getting next job." << endl;

      Job * jayobee = getNextJob();
      if (jayobee != nullptr)
      {
        sout { debugOut } << "++++Worker " << id << " running job." << endl;
        jayobee->run(jobManager);

        sout { debugOut } << "++++Worker " << id << " did job." << endl;
        jobManager->jobDone();
      }
      else
      {
        sout { debugOut } << "....Worker " << id << " bored, now." << endl;
      }
      
      // NOTE: Here we forget jayobee. Its lifetime has to
      // be managed elsewise.
    }
  }

  sout { debugOut } << "....Worker " << id << " about to die." << endl;

  // Calling this results in the destructor being called.
  // DO NOTHING with *this after this call.
  jobManager->workerDying(id);
}

