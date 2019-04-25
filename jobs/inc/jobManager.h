#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <deque>
#include <vector>
#include <mutex>
#include <atomic>   // -latomic
#include "job.h"
#include "worker.h"

namespace overground
{
  class JobManager
  {
  public:
    JobManager();
    ~JobManager();

    // users of jobManager call these fns
    void setNumWorkers(unsigned int numWorkers, Worker * callingWorker = nullptr);
    unsigned int getNumWorkers() { return workers.size(); }
    void increaseWorkers(unsigned int numWorkers = 1);
    void decreaseWorkers(unsigned int numWorkers = 1, Worker * callingWorker = nullptr);

    void startWorkers();
    void stopWorkers();
    void join();

    bool isRunning() { return running; }
    void enqueueJob(Job * job);

    int getNumJobsStarted() { return numJobsStarted; }
    int getNumJobsEnqueued();
    int getNumJobsDone() { return numJobsDone; }

    // workers call these fns
    void jobDone() { ++ numJobsDone; }
    void workerDying(Worker * worker);
    Job * dequeueJob();

  private:
    std::vector<Worker *> workers;
    std::mutex mx_workers;

    std::deque<Job *> jobs;
    std::mutex mxJobs;

    bool running = false;

    std::condition_variable cv_join;
    std::mutex mx_join;

    unsigned int numCores;
    std::atomic_int_fast32_t numJobsStarted = 0;
    std::atomic_int_fast32_t numJobsDone = 0;
  };
}

#endif // #ifndef JOBMANAGER_H
