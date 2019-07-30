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
    auto jobPostingId = std::min(
      recurringJobs.front().first,
      oneTimeJobs.front().first) - 1;
    
    auto lastJobPostingId = std::max(
      recurringJobs.back().first,
      oneTimeJobs.back().first);
    
    size_t idx = 0;
    
    while (idx < recurringJobs.size() &&
          oneTimeJobs.size() > 0)
    {
      auto recurrer = recurringJobs[idx].first;
      auto oneTimer = oneTimeJobs.front().first;
      Job * job;
      if (oneTimer < recurrer)
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
