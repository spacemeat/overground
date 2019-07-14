#ifndef POOL_H
#define POOL_H

#include <array>
#include <mutex>
#include <vector>
#include <map>
#include <new>


namespace overground
{
  template <class JobType>
  class JobPool
  {
  public:
    JobPool() { }
    size_t size() { return data.size(); }
    //JobType * next();

    template <class ...Args>
    JobType * next(std::string_view jobTitle, Args && ...args);

  private:
    std::vector<JobType *> data;
    size_t cursor = 0;
    std::mutex mx;
  };


  /*
  template <class JobType>
  JobType * JobPool<JobType>::next()
  {
    std::lock_guard<std::mutex> lock(mx);
    JobType * obj = nullptr;

    for (size_t i = 0; i < data.size(); ++i)
    {
      size_t j = (cursor + i) % data.size();
      cursor += 1;
      cursor %= data.size();
      if (data[j]->isIdle())
      {
        obj = data[j];
        break;
      }
    }

    if (obj == nullptr)
    {
      obj = new JobType();
      data.emplace_back(obj);
    }

    return obj;
  }
   */

  template <class JobType>
  template <class ...Args>
  JobType * JobPool<JobType>::next(std::string_view jobTitle, Args &&  ...args)
  {
    std::lock_guard<std::mutex> lock(mx);

    auto job = new JobType(
      jobTitle,
      std::forward<Args>(args)...);

    for (size_t i = 0; i < data.size(); ++i)
    {
      size_t j = (cursor + i) % data.size();
      cursor += 1;
      cursor %= data.size();
      if (data[j]->isIdle())
      {
        data[j] = job;
        return job;
      }
    }

    data.emplace_back(job);
    return job;
  }


}

#endif // #ifdef POOL_H

