#ifndef JOB_H
#define JOB_H

#include <vector>
#include <map>
#include <condition_variable>
#include <mutex>
#include "jobScheduler.h"


namespace overground
{
  class JobManager;

  class Job
  {
    enum class JobState { larval = 0, available, posted, pending, started };

  public:
    Job(std::string_view jobTitle);
    virtual ~Job();

    bool isAvailable()
      { return state == JobState::available; }
    bool isPosted()
      { return state == JobState::posted; }
    bool isPending()
      { return state == JobState::pending; }
    bool isStarted()
      { return state == JobState::started; }

    void setPosted()
      { state = JobState::posted; }
    void setPending()
      { state = JobState::pending; }

    void waitFor(Job * dependency);

    ScheduleKind getScheduleKind()
      { return scheduleKind; }
    void setScheduleKind(ScheduleKind kind);
    void run();
    void skip();

  protected:
    virtual void run_impl() = 0;

  private:
    void notifyWhenDone(Job * waitingJob);
    void onJobThisIsWaitingForIsDone();

    long id;
    std::string jobTitle;
    ScheduleKind scheduleKind;

    JobState state = JobState::larval;

    // dependents -- things what have to be told that I'm done
    std::vector<Job *> jobsWaitingForThis;

    // dependencies -- things what have to get done for me to start
    int numJobsThisIsWaitingFor = 0;
    int numJobsThisIsWaitingForThatAreDone = 0;
    std::mutex mxNumJobsThisIsWaitingForThatAreDone;
    std::condition_variable cvJobsThisIsWaitingForAreDone;
  };

}

#endif // #ifndef JOB_H
