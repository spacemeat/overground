#ifndef FEATURE_H
#define FEATURE_H

#include <string>
#include "tableau-gen.h"

namespace overground
{
  class Feature
  {
  public:
    Feature(tableau::feature_t const & desc);
    virtual ~Feature();

    inline std::vector<std::string> const & referencedAssets() const noexcept;

    template <typename Fn>
    void forEachAsset(Fn && visitor);
    template <typename Fn>
    void forEachFeature(Fn && visitor);

  protected:
    void trackAsset(std::string_view assetName);
    void trackFeature(std::string_view featureName);

  private:
    std::vector<std::string> assetRefs;
    std::vector<std::string> featureRefs;
  };

  inline std::vector<std::string> const & Feature::referencedAssets() const noexcept
  {
    return assetRefs;
  }


  using makeFeatureFn_t = std::function<
    std::unique_ptr<Feature>(
      tableau::feature_t const & desc
  )>;

  template <class T> // TODO: requires T derived from Feature
  static std::unique_ptr<T> makeFeature(tableau::feature_t const & desc)
  {
    return std::make_unique(desc);
  }
}

#endif // #ifndef FEATURE_H
