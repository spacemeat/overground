#ifndef POOL_H
#define POOL_H

#include <array>
#include <mutex>
#include <vector>
#include <map>


namespace overground
{
  template <class JobType>
  class JobPool
  {
  public:
    JobPool() { }
    size_t size() { return data.size(); }
    JobType * next();

  private:
    std::vector<JobType *> data;
    size_t cursor = 0;
    std::mutex mx;
  };


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
//      data.resize(data.size() + 1);
//      obj = data[data.size() - 1];
    }

    return obj;
  }


  template <class Type>
  class ObjectMap
  {
  public:
    ObjectMap() { }
    size_t size() { return data.size(); }
    Type & getOrCreate(std::string const & key);

  private:
    std::map<std::string, Type> data;
    size_t cursor = 0;
    std::mutex mx;
  };
  

  template <class Type>
  Type & ObjectMap<Type>::getOrCreate(std::string const & key)
  {
    /*
//    std::pair<typename std::map<std::string, Type>::iterator, bool> itb = data.try_emplace(key);
    auto itb = data.try_emplace(key);
    if (itb.second)
    {
      (itb.first)->setName(key);
    }
    return *itb;
    */
    /*
    auto f = data.find(key);
    bool didContain = f != data.end();
    if (didContain == false)
    {
      f = data.emplace(key).first;
      f.second->setName(key);
    }
    return *f;    
    */

    data.try_emplace(key);
    auto & val = data[key];
    val.setName(key);
    return val;
  }
}

#endif // #ifdef POOL_H

