#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <functional>
#include "asset.h"
#include "assetFiles.h"
#include "jobManager.h"

namespace overground
{
  class Engine;
  class FileReference;
  class JobScheduler;

  using makeAssetFn_t = std::function<
    std::unique_ptr<Asset>(
      std::string_view assetName,
      FileReference * assetDescFile, 
      humon::HuNode & descFromFile,
      bool cache, bool compress,
      bool monitor
  )>;

  class ResourceManager
  {
  public:
    ResourceManager(
      path_t const & baseAssetDescPath,
      path_t const & baseAssetDataPath);
    
    path_t const & getBaseAssetDescDir() const
      { return baseAssetDescDir; }
    path_t const & getBaseAssetDataDir() const
      { return baseAssetDataDir; }

    void registerAssetProvider(
      std::string_view assetKind,
      makeAssetFn_t const & fn);    

    std::unique_ptr<Asset> makeAsset(
      std::string_view assetName,
      FileReference * assetDescFile, 
      humon::HuNode & descFromFile,
      bool cache, bool compress,
      bool monitor);

    AssetDescFile * addAssetDescFile(std::string_view assetFile);
    void removeAssetDescFile(std::string_view file);

    AssetDataFile * addAssetDataFile(std::string_view newAssetDataFile, bool asCompiledFile);
    void removeAssetDataFile(std::string_view file, bool asCompiledFile);

    AssetDataFile * addAssetSrcFile(std::string_view assetDataFiles);
    void removeAssetSrcFile(std::string_view file);

    AssetDataFile * addAssetOptFile(std::string_view assetDataFiles);
    void removeAssetOptFile(std::string_view file);

    void informAssetsChanged();

    void checkForAnyFileUpdates(JobScheduler & sched);
    void checkForAssetDescFileUpdate(FileReference * file);
    void checkForAssetUpdates(JobScheduler & sched);

    void updateDeviceBuffers(ScheduleKind scheduleKind);
    void updateFromFreshAssets(JobScheduler & sched);

  private:
    std::map<std::string, makeAssetFn_t, std::less<>> assetProviders;

    path_t baseAssetDescDir;
    path_t baseAssetDataDir;

    bool assetsChanged = false;

    std::map<std::string, AssetDescFile, std::less<>> assetDescFiles;
    std::map<std::string, AssetDataFile, std::less<>> assetSrcFiles;
    std::map<std::string, AssetDataFile, std::less<>> assetOptFiles;
    
    std::map<std::string, std::unique_ptr<Asset>, std::less<>> assets;
  };
}

#endif // #ifndef RESOURCEMANAGER_H
