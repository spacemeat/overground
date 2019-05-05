#ifndef WORKER_H
#define WORKER_H

#include <thread>
#include <condition_variable>
#include <chrono>

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

    bool isAvailable() const { return available; }

    void start();
    bool nudge();
    void stop();
    void die();   // called by owner when it should delete itself.

    void joinDyingThread();
  
  private:
    Job * getNextJob();

    void threadFn();

    JobManager * jobManager = nullptr;
    int id;
    bool available = true;
    bool running = false;
    bool dying = false;

    std::thread thread;
    std::mutex mx_start;
    std::condition_variable cv_start;
    std::mutex mx_jobReady;
    std::condition_variable cv_jobReady;

    std::chrono::milliseconds jobReadyWaitDuration;
  };
}

#endif // #ifndef WORKER_H
