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


void JobManager::setNumWorkers(unsigned int numWorkers)
{
  assert(numWorkers <= numCores * 8);

  auto numWorkersBefore = workers.size();
  while (workers.size() < numWorkers)
  {
    workers.emplace_back(new Worker(this));
  }
  while (workers.size() > numWorkers)
  {
    delete workers.back();
    workers.pop_back();
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
  setNumWorkers(workers.size() + numWorkers);
}


void JobManager::decreaseWorkers(unsigned int numWorkers)
{
  setNumWorkers(workers.size() - min(
    static_cast<unsigned int>(workers.size()), numWorkers));
}


void JobManager::startWorkers()
{
  if (running == false)
  {
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
  for (auto worker : workers)
  {
    worker->join();
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
