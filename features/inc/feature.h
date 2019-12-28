#ifndef FEATURE_H
#define FEATURE_H

#include <string>
#include <type_traits>
#include "tableau-gen.h"

namespace overground
{
  class Feature
  {
  public:
    Feature(tableau::feature_t const & desc);
    virtual ~Feature();

    void error();

    template <typename Fn>
    void forEachGraphicsSubresourceNeeded(Fn && visitor);
 
    template <typename Fn>
    void forEachFeature(Fn && visitor);
    template <typename Fn>
    void forEachRenderPlan(Fn && visitor);
    template <typename Fn>
    void forEachModel(Fn && visitor);
    template <typename Fn>
    void forEachMaterial(Fn && visitor);
    template <typename Fn>
    void forEachAsset(Fn && visitor);

  protected:

  private:
  };


  using makeFeatureFn_t = std::function<
    std::unique_ptr<Feature>(
      tableau::feature_t const & desc
  )>;


  template <class T,
            class = std::enable_if_t<std::is_base_of_v<Feature, T>>>
  static std::unique_ptr<T> makeFeature(tableau::feature_t const & desc) // requires std::is_base_of<Feature, T> and kill the sfinae
  {
    return std::make_unique(desc);
  }
}

#endif // #ifndef FEATURE_H
