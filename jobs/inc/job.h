#ifndef JOB_H
#define JOB_H

#include <vector>
#include <map>
#include <condition_variable>
#include <mutex>


namespace overground
{
  class JobManager;

  class Job
  {
    enum class JobState { idle = 0, pending, started };

  public:
    Job() { }
    virtual ~Job() { }

    bool isIdle() { return state == JobState::idle; }
    bool isPending() { return state == JobState::pending; }
    bool isStarted() { return state == JobState::started; }

    void setPending() { state = JobState::pending; }

    void waitFor(Job * dependency);
  
    void run(JobManager * jobManager = nullptr);

  protected:
    virtual void run_impl(JobManager * jobManager) = 0;

  private:
    void dependsOn(Job * dependent);
    void dependencyDone();

    JobState state = JobState::idle;

    // dependents -- things what have to be told that I'm done
    std::vector<Job *> dependents;

    // dependencies -- things what have to get done for me to start
    int numDependencies = 0;
    int numDependenciesDone = 0;
    std::mutex mxNumDependenciesDone;
    std::condition_variable cvDependenciesDone;
  };

}

#endif // #ifndef JOB_H
