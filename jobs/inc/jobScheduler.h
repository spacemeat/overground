#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>

namespace overground
{
  enum class ScheduleKind
  {
    synchronous,
    asynchronous
  };

  class Job;

  class JobScheduler
  {
  public:
    JobScheduler(ScheduleKind kind = ScheduleKind::asynchronous);
    ~JobScheduler();
    ScheduleKind getKind() { return kind; }
    void beginJobGroup();
    void scheduleJob(Job * job);
    void cancelJobGroup();
    void runJobGroup();

  private:
    ScheduleKind kind;
    std::vector<Job *> jobGroup;
    bool grouping = false;
  };
}

#endif // #ifndef SCHEDULER_H
