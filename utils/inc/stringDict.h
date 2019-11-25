#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace overground
{
  template <class T>
  class stringDict
  {
  public:
    void clear()
    {
      keyMap.clear();
      dataVect.clear();
    }
    
    void push_back(std::string_view key, T const & value)
    {
      keyMap.insert_or_assign(key, dataVect.size());
      dataVect.push_back(value);
    }

    void push_back(std::string_view key, T const && value)
    {
      keyMap.insert_or_assign(key, dataVect.size());
      dataVect.push_back(std::move(value));
    }

    void remove(std::string_view key)
    {
    // TODO: Remove this ridic. cast when std=c++20
      auto idx = keyMap[(std::string)key];
    // TODO: Remove this ridic. cast when std=c++20
      keyMap.erase((std::string)key);
      dataVect.erase(std::remove(dataVect.begin(), dataVect.end(), idx), dataVect.end());
      std::for_each(dataVect.begin(), dataVect.end(), [idx](auto & i){ i = (i < idx) ? i : i - 1; });
    }

    // TODO: Remove this ridic. cast when std=c++20
    bool hasKey(std::string_view key) const noexcept
      { return keyMap.find((std::string)key) != keyMap.end(); }

    // TODO: Remove this ridic. cast when std=c++20
    T & operator[](std::string_view key) const noexcept
    {
      auto it = keyMap.find((std::string) key);
      return dataVect.at(it->second);
     }

    T & operator[](size_t idx) const noexcept
      { return dataVect[idx]; }

    std::unordered_map<std::string, size_t> const & keys() const noexcept
      { return keyMap; }
    
    std::vector<T> const & vect() const noexcept
      { return dataVect; }

    size_t size() const noexcept
      { return dataVect.size(); }
    
    void merge(stringDict<T> && rhs);

  private:
    std::unordered_map<std::string, size_t> keyMap;
    std::vector<T> dataVect;
  };

  template <class T>
  bool operator == (stringDict<T> const & lhs, stringDict<T> const & rhs)
  {
    return lhs.keyMap == rhs.keyMap && lhs.dataVect == rhs.dataVect;
  }

  template <class T>
  bool operator != (stringDict<T> const & lhs, stringDict<T> const & rhs)
  {
    return !(lhs == rhs);
  }

  template <class T>
  void stringDict<T>::merge(stringDict<T> && rhs)
  {
    for (auto & [key, idx] : rhs.keys())
    {
      if (auto it = keyMap.find(key); it == keyMap.end())
      {
        keyMap.emplace({key, dataVect.size()});
        dataVect.push_back(move(rhs.dataVect[idx]));
      }
    }
  }
}

