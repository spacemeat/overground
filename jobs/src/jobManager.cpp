#include "jobManager.h"
#include "job.h"
#include "worker.h"
#include <thread>
#include <cassert>
#include <algorithm>

using namespace std;
using namespace overground;


JobManager::JobManager()
{
  numCores = std::thread::hardware_concurrency();
}


JobManager::~JobManager()
{
}


void JobManager::setNumWorkers(unsigned int numWorkers, Worker * callingWorker)
{
  assert(numWorkers <= numCores * 8);

  auto numWorkersBefore = workers.size();

  if (numWorkersBefore < numWorkers)
  {
    lock_guard lock(mx_workers);
    while (workers.size() < numWorkers)
      { workers.emplace_back(new Worker(this)); }
  }  

  else
  {
    for (int i = 0; i < (int) numWorkersBefore - (int) numWorkers; ++i)
    {
      // The worker will be removed from workers when its
      // current job is done.
      workers[workers.size() - i - 1]->die();
    }
  }
  
  if (running && numWorkers > numWorkersBefore)
  {
    for (auto it = workers.begin() + numWorkersBefore; it < workers.end(); ++it)
    {
      (* it)->start();
    }
  }
}


void JobManager::increaseWorkers(unsigned int numWorkers)
{
  setNumWorkers(workers.size() + numWorkers, nullptr);
}


void JobManager::decreaseWorkers(unsigned int numWorkers, Worker * callingWorker)
{
  setNumWorkers(workers.size() - min(
    static_cast<unsigned int>(workers.size()), numWorkers), callingWorker);
}


void JobManager::startWorkers()
{
  if (running == false)
  {
    lock_guard lock(mx_workers);
    running = true;
    for (auto worker : workers)
    {
      worker->start();
    }
  }
}


void JobManager::stopWorkers()
{
  if (running)
  {
    lock_guard lock(mx_workers);
    running = false;
    for (auto worker : workers)
    {
      worker->stop();
    }
  }
}


void JobManager::join()
{
  setNumWorkers(0);

  {
    size_t ws = 0;
    {
      lock_guard lock(mx_workers);
      ws = workers.size();
    }

    while (ws > 0)
    {
      unique_lock<mutex> lock(mx_join);
      cv_join.wait(lock, [&]
      {
        {
          lock_guard lock(mx_workers);
          ws = workers.size();
        }

        return ws == 0;
      });
    }
  }
}


void JobManager::enqueueJob(Job * job)
{
  job->setPending();
  
  auto lock = lock_guard<mutex>(mxJobs);
  jobs.push_back(job);

  // Check if any threads are asleep, and nudge one if so
  for (auto worker : workers)
  {
    if (worker->isAvailable())
    {
      worker->nudge();
      break;
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


void JobManager::workerDying(Worker * worker)
{
  for (auto it = workers.rbegin(); it != workers.rend(); ++it)
  {
    if (* it == worker)
    {
      {
        lock_guard lock(mx_workers);
        workers.erase((it + 1).base());
      }
      // The Worker object has now been destroyed.
      // The caller was a member fn of Worker, and this
      // is the very last thing it's doing. THIS MUST
      // ALWAYS BE THE CASE or I will find you and I will
      // do things even Liam Neeson wouldn't do.

      // Notify a new cv for anyone trying to join on this thread.
      cv_join.notify_one();

      break;
    }
  }
}


Job * JobManager::dequeueJob()
{
  auto lock = lock_guard<mutex>(mxJobs);
  if (jobs.size() > 0)
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
