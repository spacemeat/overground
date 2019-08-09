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


Job::~Job()
{ }


// only useful if *this hasn't started the job yet; TODO: assert(state == JobState::idle)?
void Job::waitFor(Job * jobThisWaitsFor)
{
  jobThisWaitsFor->notifyWhenDone(this);
  numJobsThisIsWaitingFor += 1;
}


void Job::setScheduleKind(ScheduleKind kind)
{
  scheduleKind = kind;
}


void Job::run()
{
  bool wasPosted = isPosted();
  state = JobState::started;
  if (numJobsThisIsWaitingFor > 0)
  {
    log(thId, logTags::job, fmt::format("{}delaying {}{}{} (job {}{}{}).{}", 
      ansi::darkBlue, 
      ansi::lightBlue, jobTitle, 
      ansi::darkBlue, 
      ansi::lightBlue, id,
      ansi::darkBlue, 
      ansi::off));
    if (scheduleKind == ScheduleKind::asynchronous)
      { jobMan->increaseNumEmployedWorkers(); }

    {
      unique_lock<mutex> lock(mxNumJobsThisIsWaitingForThatAreDone);
      cvJobsThisIsWaitingForAreDone.wait(lock,
        [&]{ return numJobsThisIsWaitingForThatAreDone == numJobsThisIsWaitingFor; });
    }

    if (scheduleKind == ScheduleKind::asynchronous)
    { jobMan->decreaseNumEmployedWorkers(); }
  }

  log(thId, logTags::job, fmt::format("{}starting {}{}{} (job {}{}{}).{}", 
    ansi::darkMagenta, 
    ansi::lightMagenta, jobTitle, 
    ansi::darkMagenta, 
    ansi::lightMagenta, id,
    ansi::darkMagenta, 
    ansi::off));

  run_impl();

  log(thId, logTags::job, fmt::format("{}Job done {}{}{} (job {}{}{}).{}", 
    ansi::darkMagenta, 
    ansi::lightMagenta, jobTitle, 
    ansi::darkMagenta, 
    ansi::lightMagenta, id,
    ansi::darkMagenta, 
    ansi::off));

  for (auto job : jobsWaitingForThis)
    { job->onJobThisIsWaitingForIsDone(); }

  state = wasPosted ? 
    JobState::posted : 
    JobState::available;
}


void Job::skip()
{
  bool wasPosted = isPosted();
  state = JobState::started;

  log(thId, logTags::job, fmt::format("{}skipping {}{}{} (job {}{}{}).{}", 
    ansi::lightYellow, 
    ansi::lightMagenta, jobTitle, 
    ansi::darkMagenta, 
    ansi::lightMagenta, id,
    ansi::darkMagenta, 
    ansi::off));

  for (auto job : jobsWaitingForThis)
    { job->onJobThisIsWaitingForIsDone(); }

  state = wasPosted ? 
    JobState::posted : 
    JobState::available;
}


void Job::notifyWhenDone(Job * waitingJob)
{
  assert(state == JobState::larval ||
         state == JobState::pending);
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

