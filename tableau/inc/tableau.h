#ifndef TABLEAU_H
#define TABLEAU_H

#include <vector>
#include "objectManager.h"
#include "tableau-gen.h"

namespace overground
{
  enum class TableauState
  {
    disabled,
    enabled
  };


  class Tableau
  {
  public:
    Tableau(tableau::tableau_t const & desc);
    virtual ~Tableau();

    inline TableauState state();
    inline void setState(TableauState newState);

    template <typename Fn>
    inline void forEachObject(Fn fn);

  protected:

  private:
    std::vector<size_t> objects_;
    TableauState state_;
  };


#pragma region inline impl

  inline TableauState Tableau::state()
  {
    return state_;
  }


  inline void Tableau::setState(TableauState newState)
  {
    state_ = newState;
    if (newState == TableauState::disabled)
    {
      forEachObject([newState](Object & f)
        { /* turn off */ });
    }
    else
    {
      forEachObject([newState](Object & f)
        { /* turn on */ });
    }
  }


  template <typename Fn>
  inline void Tableau::forEachObject(Fn fn)
  {
    std::for_each(objects_.begin(), objects.end(), 
      [](size_t id){ fn(objectMan->objects()[id]) });
  }

  #pragma endregion


  using makeTableauFn_t = std::function<
    std::unique_ptr<Tableau>(
      tableau::tableau_t const & desc
  )>;


  template <class T> // TODO: requires T derived from Tableau
  static std::unique_ptr<T> makeTableau(tableau::tableau_t const & desc)
  {
    return std::make_unique(desc);
  }
}

#endif // #ifndef TABLEAU_H
