#ifndef JOBBOARD_H
#define JOBBOARD_H

#include <vector>
#include <queue>
#include "utils.h"

namespace overground
{
  class Job;

  class JobBoard
  {
  public:
    JobBoard(std::string_view name);

    void clear();
    void postJob(Job * job, bool recurring);

    size_t getNumJobs() const
      { return recurringJobs.size() + 
        oneTimeJobs.size(); }

    template <typename T>
    void forEachJob(T fn);

  private:
    std::string name;
    std::vector<std::pair<unsigned int, Job *>> recurringJobs;
    std::queue<std::pair<unsigned int, Job *>> oneTimeJobs;
  };

  template <typename T>
  void JobBoard::forEachJob(T fn)
  {
    size_t idx = 0;
    
    while (idx < recurringJobs.size() ||
          oneTimeJobs.size() > 0)
    {
      Job * job;
      if (recurringJobs.size() == 0)
      {
        job = oneTimeJobs.front().second;
        oneTimeJobs.pop();
      }
      else if (oneTimeJobs.size() == 0)
      {
        job = recurringJobs[idx].second;
        idx += 1;
      }
      else if (oneTimeJobs.front().first < recurringJobs[idx].first)
      {
        job = oneTimeJobs.front().second;
        oneTimeJobs.pop();
      }
      else
      {
        job = recurringJobs[idx].second;
        idx += 1;
      }
      fn(job);
    }
  }
}

#endif // #ifndef JOBBOARD_H
