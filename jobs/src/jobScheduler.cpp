#include "jobScheduler.h"
#include "job.h"
#include "jobManager.h"

using namespace std;
using namespace overground;


JobScheduler::JobScheduler(ScheduleKind kind)
: kind(kind)
{
}


JobScheduler::~JobScheduler()
{
  runJobGroup();
}


void JobScheduler::beginJobGroup()
{
  grouping = true;
  jobGroup.clear();
}


void JobScheduler::scheduleJob(Job * job)
{
  job->setScheduleKind(kind);

  if (grouping)
    { jobGroup.push_back(job); }
  else
  {
    if (kind == ScheduleKind::asynchronous)
      { jobMan->enqueueJob(job); }
    else
      { job->run(); }
  }
}


void JobScheduler::cancelJobGroup()
{
  grouping = false;
  jobGroup.clear();
}


void JobScheduler::runJobGroup()
{
  if (grouping)
  {
    grouping = false;
    if (kind == ScheduleKind::asynchronous)
    {
      for (auto it = jobGroup.rbegin(); it != jobGroup.rend(); ++it)
        { jobMan->enqueueJob(*it); }
    }
    else
    {
      for (auto it = jobGroup.begin(); 
        it != jobGroup.end(); ++it)
        { (*it)->run(); }
    }
  }
  jobGroup.clear();
}
