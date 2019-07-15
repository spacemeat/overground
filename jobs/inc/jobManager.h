#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <deque>
#include <vector>
#include <mutex>
#include <atomic>   // -latomic
// also, TODO: Let's make sure we're doing atomic stuff right.
#include <stack>
#include "job.h"
#include "fnJob.h"
#include "worker.h"

namespace overground
{
  class JobManager
  {
  public:
    static unsigned int getNumCores();

    JobManager();
    ~JobManager();

    void allocateWorkers(unsigned int numWorkers);

    // users of jobManager call these fns
    unsigned int getNumEmployedWorkers()
      { return numEmployedWorkers; }
    void increaseNumEmployedWorkers(
      unsigned int numWorkers = 1);
    void decreaseNumEmployedWorkers(
      unsigned int numWorkers = 1);
    void setNumEmployedWorkers(
      unsigned int numWorkers);
  private:
    void setNumEmployedWorkers_int(
      unsigned int numWorkers);

  public:
    void stopAndJoin();

    bool isRunning() { return running; }
    void enqueueJob(Job * job);
    void enqueueJobs(std::stack<Job *> jobs);

    int getNumJobsStarted() { return numJobsStarted; }
    int getNumJobsEnqueued();
    int getNumJobsDone() { return numJobsDone; }

    // workers call these fns
    void jobDone() { ++ numJobsDone; }
    void workerDying(int workerId);
    Job * dequeueJob();

  private:
    std::vector<Worker *> workers;
    std::mutex mxWorkers;
    size_t numEmployedWorkers = 0;

    std::deque<Job *> jobs;
    std::mutex mxJobs;

    bool running = true;

    unsigned int numCores;
    std::atomic_int_fast32_t numJobsStarted = 0;
    std::atomic_int_fast32_t numJobsDone = 0;
  };

  extern JobManager jobMan;
}

#endif // #ifndef JOBMANAGER_H
