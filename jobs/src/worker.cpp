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
  jobReadyWaitDuration(1s)
{
}


Worker::Worker(Worker const & rhs)
: jobManager(rhs.jobManager),
  thread([this]{ this->threadFn(); }),
  jobReadyWaitDuration(1s)
{
}


Worker::~Worker()
{
}


void Worker::start()
{
  if (employed == false)
  {
    log(thId, fmt::format("start() worker {}", id));
  
    employed = true;
    gettingAJob = true;
    cv_start.notify_one();
  }
}


// NOTE: The thread that is getting nudged may
// not be the thread that takes the next task.
// Just so's ya know.
bool Worker::nudge()
{
  if (employed && tasked == false)
  {
    log(thId, logTags::verb, fmt::format("nudge() worker {}", id));
    gettingAJob = true;
    cv_start.notify_one();
    return true;
  }

  return false;
}


void Worker::stop()
{
  if (employed)
  {
    log(thId, fmt::format("stop() worker {}", id));
    employed = false;
  }
}


void Worker::die()
{
  log(thId, fmt::format("die() worker {}", id));
  employed = false;
  dying = true;
  // don't even wait for the timeout; just die now pls
  cv_start.notify_one();      // in case we're stopped
}


void Worker::join()
{
  log(thId, fmt::format("join() worker {}", id));
  thread.join();
}


// new
void Worker::threadFn()
{
  thId = createLogChannel(
    fmt::format("wk {}", id), logTags::dbg, logTags::macro,
    & cout, & coutMx);

  log(thId, "thread start");

  while (dying == false)
  {
    {
      unique_lock<mutex> lock(mx_start);
      log(thId, logTags::verb, "waiting for work.");
      cv_start.wait_for(lock, 
        jobReadyWaitDuration, [&]
        { return (employed && gettingAJob) || dying; });
    }
    gettingAJob = false;
    
    while (employed && dying == false)
    {
      log(thId, logTags::verb, "getting next job.");

      auto jayobee = jobManager->dequeueJob(this);
      if (jayobee != nullptr)
      {
        tasked = true;

        try
          { jayobee->run(); }
        catch(const std::exception& e)
          { std::cerr << e.what() << '\n'; }
        
        jobManager->jobDone();
      }
      else
      {
        log(thId, logTags::verb, "bored now.");
        tasked = false;
        break;
      }
    }
  }

  log(thId, "about to die.");

  jobManager->workerDying(id);
}

