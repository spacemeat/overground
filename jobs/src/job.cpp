#include "job.h"
#include "jobManager.h"
#include <cassert>

using namespace std;
using namespace overground;


// only useful if *this hasn't started the job yet; TODO: assert(state == JobState::idle)?
void Job::waitFor(Job * jobThisWaitsFor)
{
  jobThisWaitsFor->notifyWhenDone(this);
  numJobsThisIsWaitingFor += 1;
}


void Job::run(JobManager * jobManager)
{
  state = JobState::started;
  if (numJobsThisIsWaitingFor > 0)
  {
    if (jobManager != nullptr)
    { jobManager->increaseWorkers(); }

    {
      unique_lock<mutex> lock(mxNumJobsThisIsWaitingForThatAreDone);
      cvJobsThisIsWaitingForAreDone.wait(lock,
        [&]{ return numJobsThisIsWaitingForThatAreDone == numJobsThisIsWaitingFor; });
    }

    if (jobManager != nullptr)
    { jobManager->decreaseWorkers(); }
  }

  run_impl(jobManager);

  for (auto job : jobsWaitingForThis)
  {
    job->onJobThisIsWaitingForIsDone();
  }
  state = JobState::idle;
}


void Job::notifyWhenDone(Job * waitingJob)
{
  assert(state == JobState::idle);
  jobsWaitingForThis.push_back(waitingJob);
}


void Job::onJobThisIsWaitingForIsDone()
{
  int numJobsDone;
  {
    lock_guard<mutex> lock(mxNumJobsThisIsWaitingForThatAreDone);
    numJobsDone = numJobsThisIsWaitingForThatAreDone += 1;
  }

  if (numJobsDone == numJobsThisIsWaitingFor)
  {
    cvJobsThisIsWaitingForAreDone.notify_one();
  }
}

