#include "taskManager.h"
#include <chrono>

using namespace std::chrono_literals;
using namespace std;
using namespace overground;


TaskWorker::TaskWorker(TaskManager & manager, size_t id)
: manager(manager), id(id), workerThread([this](){ threadFn(); })
{
}


TaskWorker::~TaskWorker()
{
  killAndJoinWorker();
}


void TaskWorker::activate()
{
  isActive = true;
  cvActivate.notify_one();  
}


void TaskWorker::deactivate()
{
  isActive = false;
}


void TaskWorker::joinActivity()
{
  if (isActive == false || isDying)
    { return; }

  while(isActive)
  {
    std::unique_lock lock(mxTaskDone);
    cvTaskDone.wait_for(lock, 1ms, [this]
      { return isActive == false; });
  }
}


void TaskWorker::killAndJoinWorker()
{
  if (isDying)
    { return; }

  isDying = true;
  if (isActive == false)
    { cvActivate.notify_one(); }

  if (workerThread.joinable())
  {
    workerThread.join();
  }
}


void TaskWorker::threadFn()
{
  while (isDying == false)
  {
    if (isActive == false)
    {
      std::unique_lock lock(mxActivate);
      cvActivate.wait_for(lock, 1ms, [this]{ return isActive || isDying; });
    }

    if (isDying)
      { continue; }

    // get a task
    auto newTask = manager.getNextTask();
    if (newTask.has_value())
    {
      currentTask = move(*newTask);
      currentTask();
      tasksDone += 1;
      cvTaskDone.notify_all();
    }
    else
    {
      isActive = false;
      manager.workerDeactivating(id);
    }    
  }
}


// TaskManager

TaskManager::TaskManager(size_t numWorkers, size_t numActiveWorkers)
{
  setNumWorkers(numWorkers);
  setNumActiveWorkers(numActiveWorkers);
}


TaskManager::~TaskManager()
{
  setNumWorkers(0);
}


void TaskManager::setNumWorkers(size_t numWorkers)
{
  workers.resize(numWorkers);
}


void TaskManager::setNumActiveWorkers(size_t numActiveWorkers)
{
  numActiveWorkers = max(numActiveWorkers, workers.size());
  for (size_t i = 0; i < workers.size(); ++i)
  {
    if (i < numActiveWorkers)
      { workers[i].activate(); }
    else
      { workers[i].deactivate(); }
  }
}


void TaskManager::enqueueTask(taskFn_t fn)
{
  lock_guard lock(mxTaskQueeue);
  taskQueue.emplace_back(fn);
}


void TaskManager::joinAllTasks()
{
  for (size_t i = 0; i < workers.size(); ++i)
    { workers[i].joinActivity(); }
}


void TaskManager::killAndJoinAllWorkers()
{
  workers.clear();
}


std::optional<taskFn_t> TaskManager::getNextTask()
{
  lock_guard lock(mxTaskQueeue);
  if (taskQueue.size())
  {
    auto task = move(taskQueue.front());
    taskQueue.pop_front();
    return task;
  }
  else
    { return {}; }
}


void TaskManager::workerDeactivating(size_t id)
{
}
