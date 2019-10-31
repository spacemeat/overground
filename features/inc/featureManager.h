#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <array>
#include <vector>
#include <optional>
#include "feature.h"
#include "utils.h"
#include "graphicsUtils.h"


namespace overground
{
  class FeatureManager
  {
  public:
    void installPlugin(std::string_view name, makeFeatureFn_t plugin);

    inline std::unordered_map<std::string, makeFeatureFn_t> const & plugins() const noexcept;

    inline std::vector<std::unique_ptr<Feature>> const & featuers() const noexcept;
    
    inline std::vector<std::unique_ptr<Feature>> & featues() noexcept;

  private:
    std::unordered_map<std::string, std::unique_ptr<Feature>> featurePlugins_;

    std::vector<std::unique_ptr<Feature>> features_;
  };

  inline std::unordered_map<std::string, makeFeatureFn_t> const & FeatureManager::plugins() const noexcept
  {
    return featurePlugins_;
  }


  inline std::vector<std::unique_ptr<Feature>> const & FeatureManager::featuers() const noexcept
  {
    return features_;
  }


  inline std::vector<std::unique_ptr<Feature>> & FeatureManager::featues() noexcept
  {
    return features_;
  }


  static inline std::optional<FeatureManager> featureMan;
}


#endif // #ifndef ASSETMANAGER_H
