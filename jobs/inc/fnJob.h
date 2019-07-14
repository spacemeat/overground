#ifndef FNJOB_H
#define FNJOB_H

#include "job.h"
#include "pool.h"

namespace overground
{
  template <class Callable>
  class FnJob : public Job
  {
  public:
    FnJob(std::string_view jobTitle,
      Callable fn)
      : Job(jobTitle), jobFn(fn)
      { }

    virtual ~FnJob()
      { }

  protected:
    virtual void run_impl(JobManager * jobManager)
    {
      jobFn(jobManager);
    }

  private:
    Callable jobFn;

  public:
    static JobPool<FnJob<Callable>> fnJobs;
  };

  template <class Callable>
  JobPool<FnJob<Callable>> FnJob<Callable>::fnJobs;

  template <class Callable>
  FnJob<Callable> * makeFnJob(std::string_view name, Callable jobFn)
  {
    auto job = FnJob<Callable>::fnJobs.next(name, jobFn);
    return job;
  }
}

#endif // #ifndef FNJOB_H
