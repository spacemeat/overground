#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <array>
#include <vector>
#include <optional>
#include <variant>
#include "utils.h"
#include "fileReference.h"
#include "graphicsUtils.h"
#include "asset-gen.h"
#include "asset.h"


namespace overground
{
  class AssetManager
  {
  public:
    void trackAsset(std::string_view assetName, std::string_view tableauName, fs::path const & srcPath, fs::path const & cmpPath);
    void untrackAsset(std::string_view assetName, std::string_view tableauName);
    void untrackTableau(std::string_view tableauName);
    void checkForUpdatedFiles() noexcept;
    
    void installPlugin(std::string_view name, makeAssetFn_t plugin);

    std::unordered_map<std::string, std::unique_ptr<Asset>> const & assets() const noexcept;

  private:
    void compileAssets(std::vector<std::string> const & assets);
    std::unordered_map<std::string, std::unique_ptr<Asset>> assetMap;

    std::unordered_map<std::string, makeAssetFn_t> assetPlugins;
  }; 
  
  std::unordered_map<std::string, std::unique_ptr<Asset>> const & AssetManager::assets() const noexcept
  {
    return assetMap;
  }

  static inline std::optional<AssetManager> assetMan;
}


#endif // #ifndef ASSETMANAGER_H
