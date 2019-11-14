#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "featureManager.h"
#include "tableau-gen.h"

namespace overground
{
  enum class ObjectState
  {
    disabled,
    enabled
  };


  class Object
  {
  public:
    Object(tableau::object_t const & desc);
    virtual ~Object();

    inline ObjectState state();
    inline void setState(ObjectState newState);

    template <typename Fn>
    inline void forEachFeature(Fn fn);

  protected:

  private:
    std::vector<size_t> features_;
    ObjectState state_;
  };


#pragma region inline impl

  inline ObjectState Object::state()
  {
    return state_;
  }


  inline void Object::setState(ObjectState newState)
  {
    state_ = newState;
    if (newState == ObjectState::disabled)
    {
      forEachFeature([newState](Feature & f)
        { /* turn off */ });
    }
    else
    {
      forEachFeature([newState](Feature & f)
        { /* turn on */ });
    }
  }


  template <typename Fn>
  inline void Object::forEachFeature(Fn fn)
  {
    std::for_each(features_.begin(), features.end(), 
      [](size_t id){ fn(featureMan->features()[id]) });
  }

  #pragma endregion


  using makeObjectFn_t = std::function<
    std::unique_ptr<Object>(
      tableau::object_t const & desc
  )>;


  static std::unique_ptr<Object> makeObject(tableau::object_t const & desc);
}

#endif // #ifndef OBJECT_H
