#ifndef WORKER_H
#define WORKER_H

#include <thread>
#include <condition_variable>
#include <chrono>
#include <atomic>

namespace overground
{
  class JobManager;
  class Job;

  class Worker
  {
  public:
    Worker(JobManager * jobManager, int workerId);
    Worker(Worker const & rhs);
    ~Worker();

    int getId() { return id; }

    bool isEmployed() const { return employed; }
    bool isTasked() const { return tasked; }

    void start();
    bool nudge();
    void stop();
    void die();   // called by owner when it should terminate its thread.
    void join();
  
  private:
    Job * getNextJob();

    void threadFn();

    JobManager * jobManager = nullptr;
    int id;
    std::atomic<bool> employed = false;
    std::atomic<bool> tasked = false;
    std::atomic<bool> gettingAJob = true;
    std::atomic<bool> running = false;
    std::atomic<bool> dying = false;

    std::thread thread;
    std::mutex mx_start;
    std::condition_variable cv_start;
    std::mutex mx_jobReady;
    std::condition_variable cv_jobReady;

    std::chrono::milliseconds jobReadyWaitDuration;
  };
}

#endif // #ifndef WORKER_H
