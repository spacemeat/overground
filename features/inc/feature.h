#ifndef FEATURE_H
#define FEATURE_H

#include <functional>
#include <variant>
#include <string>
#include <type_traits>
#include "tableau-gen.h"
#include "graphicsUtils.h"

namespace overground
{
  class Asset;

  class Feature
  {
  public:
    using reportGraphicsSubresourceFn_t = std::function<
      void(
        Asset * asset, 
        std::variant<vk::ImageCreateFlagBits, vk::BufferCreateFlagBits> createFlags, 
        std::variant<vk::ImageUsageFlagBits, vk::BufferUsageFlagBits> usageFlags,
        vk::MemoryPropertyFlagBits additionalMemoryProps,
        std::vector<int32_t> && sortedQueueFamilyIndices)>;
  
    Feature(tableau::feature_t const & desc);
    virtual ~Feature();

    void error();

    std::string_view getName() { return name; }

    virtual void forEachGraphicsSubresourceNeeded(
      reportGraphicsSubresourceFn_t reportFn);

    /*
    void forEachFeature(Fn && visitor);
    void forEachRenderPlan(Fn && visitor);
    void forEachMaterial(Fn && visitor);
    void forEachAsset(Fn && visitor);
    */

  protected:

  private:
    std::string name;
  };


  void Feature::forEachGraphicsSubresourceNeeded(
    reportGraphicsSubresourceFn_t reportFn)
  {
    log(thId, logTags::warn, fmt::format("Feature {} does not implement forEachGraphicsSubresourceNeeded().", name));
  }


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
