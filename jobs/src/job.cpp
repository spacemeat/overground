#include "job.h"
#include "jobManager.h"
#include <cassert>

using namespace std;
using namespace overground;


// only useful if *this hasn't started the job yet; TODO: assert(state == JobState::idle)?
void Job::waitFor(Job * dependency)
{
  dependency->dependsOn(this);
  numDependencies += 1;
}


void Job::run(JobManager * jobManager)
{
  state = JobState::started;
  if (numDependencies > 0)
  {
    if (jobManager != nullptr)
    { jobManager->increaseWorkers(); }

    {
      unique_lock<mutex> lock(mxNumDependenciesDone);
      cvDependenciesDone.wait(lock,
        [&]{ return numDependenciesDone == numDependencies; });
    }

    if (jobManager != nullptr)
    { jobManager->decreaseWorkers(); }
  }
  run_impl(jobManager);
  for (auto job : dependents)
  {
    job->dependencyDone();
  }
  state = JobState::idle;
}


void Job::dependsOn(Job * dependent)
{
  assert(state == JobState::idle);
  dependents.push_back(dependent);
}


void Job::dependencyDone()
{
  {
    lock_guard<mutex> lock(mxNumDependenciesDone);
    numDependenciesDone += 1;
  }

  if (numDependenciesDone == numDependencies)
  {
    cvDependenciesDone.notify_one();
  }
}

