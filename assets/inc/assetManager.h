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
#include "allocDesc.h"


namespace overground
{
  class AssetManager
  {
  public:

    void initializeAssetDatabase();
    void synchronizeCache();

    // void trackAsset(std::string_view assetName, std::string_view tableauName, fs::path const & srcPath, fs::path const & cmpPath);
    // void untrackAsset(std::string_view assetName, std::string_view tableauName);
    // void untrackTableau(std::string_view tableauName);
    void checkForUpdatedFiles() noexcept;
    
    std::unordered_map<std::string, std::unique_ptr<Asset>> const & getAssets() const noexcept;

  private:
    void compileAssets(std::vector<std::string> const & assets);

    bool assNeedsToStore = false;
    std::unordered_map<std::string, std::unique_ptr<Asset>> currAssetMap;
    std::unordered_map<std::string, std::unique_ptr<Asset>> workAssetMap;

    AllocDesc currCacheMap;
    AllocDesc workCacheMap;
  }; 
  
  std::unordered_map<std::string, std::unique_ptr<Asset>> const & AssetManager::getAssets() const noexcept
  {
    return assetMap;
  }

  static inline std::optional<AssetManager> assetMan;
}


#endif // #ifndef ASSETMANAGER_H
