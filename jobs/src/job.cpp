#include "job.h"
#include "jobManager.h"
#include "utils.h"
#include <cassert>

using namespace std;
using namespace overground;


long id = 0;


Job::Job(string_view jobTitle)
  : id(::id++), jobTitle(jobTitle)
{ }

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
    log(thId, fmt::format("{}delaying {}{}{}(job id {}{}{}){}", 
      ansi::darkBlue, ansi::lightBlue, jobTitle, 
      ansi::darkBlue, ansi::lightBlue, id,
      ansi::darkBlue, ansi::off));
    if (jobManager != nullptr)
    { jobManager->increaseNumEmployedWorkers(); }

    {
      unique_lock<mutex> lock(mxNumJobsThisIsWaitingForThatAreDone);
      cvJobsThisIsWaitingForAreDone.wait(lock,
        [&]{ return numJobsThisIsWaitingForThatAreDone == numJobsThisIsWaitingFor; });
    }

    if (jobManager != nullptr)
    { jobManager->decreaseNumEmployedWorkers(); }
  }

  log(thId, fmt::format("{}starting {}{}{}(job id {}{}{}){}", 
    ansi::darkMagenta, ansi::lightMagenta, jobTitle, 
    ansi::darkMagenta, ansi::lightMagenta, id,
    ansi::darkMagenta, ansi::off));
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

