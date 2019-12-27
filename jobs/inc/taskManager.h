#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>

#include "utils.h"

namespace overground
{
  using taskFn_t = std::function<void()>;

  class TaskWorker
  {
  public:
    TaskWorker(TaskManager & manager, size_t id);
    ~TaskWorker();

    void activate();
    void deactivate();
    void joinActivity();
    void killAndJoinWorker();

  private:
    void threadFn();

    alignas(cacheLineSizeDestructive)
    std::atomic<bool> isActive = false;
    std::condition_variable cvActivate;
    std::mutex mxActivate;

    alignas(cacheLineSizeDestructive)
    std::atomic<bool> isDying = false;

    alignas(cacheLineSizeDestructive)
    std::atomic<int> tasksDone = 0;
    std::condition_variable cvTaskDone;
    std::mutex mxTaskDone;

    TaskManager & manager;
    size_t id;

    std::thread workerThread;

    taskFn_t currentTask;
  };


  class TaskManager
  {
  public:
    TaskManager(size_t numWorkers, size_t numActiveWorkers = 0);
    ~TaskManager();

    void setNumWorkers(size_t numWorkers);
    void setNumActiveWorkers(size_t numActiveWorkers);

    void enqueueTask(taskFn_t fn);

    void joinAllTasks();
    void killAndJoinAllWorkers();

  // called by TaskWorker
    std::optional<taskFn_t> getNextTask();
    void workerDeactivating(size_t id); 

  private:
    std::vector<TaskWorker> workers;
    std::deque<taskFn_t> taskQueue;

    std::condition_variable cvTaskQueue;
    std::mutex mxTaskQueeue;
  };

  inline std::optional<TaskManager> taskMan;
}

#endif // #ifndef TASKMANAGER_H
