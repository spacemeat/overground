#ifndef POOL_H
#define POOL_H

#include <array>
#include <mutex>
#include <vector>
#include <map>
#include <new>
#include "logger.h"


namespace overground
{
  template <class JobType>
  class JobPool
  {
  public:
    JobPool() { }
    size_t size() { return data.size(); }

    template <class ...Args>
    JobType * next(std::string_view jobTitle, Args && ...args);

  private:
    std::vector<std::unique_ptr<JobType>> data;
    size_t cursor = 0;
    std::mutex mx;
  };


  template <class JobType>
  template <class ...Args>
  JobType * JobPool<JobType>::next(std::string_view jobTitle, Args &&  ...args)
  {
    std::lock_guard<std::mutex> lock(mx);

    auto job = std::make_unique<JobType>(
      jobTitle,
      std::forward<Args>(args)...);
    
    for (size_t i = 0; i < data.size(); ++i)
    {
      auto j = (i + cursor) % data.size();      
      if (data[j]->isAvailable())
      {
        log(thId, fmt::format("REUSING {}", jobTitle));
        data[j].release();
        data[j] = std::move(job);
        return data[j].get();
      }

      cursor += 1;
      cursor %= data.size();
    }

    data.push_back(std::move(job));
    return data.back().get();
  }
}


#endif // #ifdef POOL_H

