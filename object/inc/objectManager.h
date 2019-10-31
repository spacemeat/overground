#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <string>
#include <unordered_map>
#include "object.h"

namespace overground
{
  class ObjectManager
  {
  public:
    void installPlugin(std::string_view name, makeObjectFn_t plugin);

    inline std::unordered_map<std::string, makeObjectFn_t> const & plugins() const noexcept;

    inline std::vector<std::unique_ptr<Object>> objects() const noexcept;

  private:
    std::unordered_map<std::string, makeObjectFn_t> plugins_;
    std::vector<std::unique_ptr<Object>> objects_;
  };


  #pragma region inline impl

  inline std::unordered_map<std::string, makeObjectFn_t> const & ObjectManager::plugins() const noexcept
  {
    return plugins_;
  }

  inline std::vector<std::unique_ptr<Object>> ObjectManager::objects() const noexcept
  {
    return objects_;
  }

  #pragma endregion


  static inline std::optional<ObjectManager> objectMan;
}

#endif // OBJECTMANAGER_H
