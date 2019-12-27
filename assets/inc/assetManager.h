#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <array>
#include <vector>
#include <optional>
#include <variant>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <new>
#include "utils.h"
#include "fileReference.h"
#include "graphicsUtils.h"
#include "assembly-gen.h"
#include "asset.h"
#include "allocDesc.h"


namespace overground
{
  class AssetManager
  {
  public:
    AssetManager();
    ~AssetManager();

    Asset * getAsset(std::string_view name);

    void handleConfigChanges(config::config_t const & config);
    path_t findCacheFile() const;
    path_t getNextCacheFileName() const;

    void heyCheckForFileChanges();
    void heySynchronizeCache();

    void checkForFileChanges();
  private:
    void checkForUpdatedFiles();
    void loadAdbFile();
    void storeAdbFile();
  public:
    void buildWorkCacheMap(
      assembly::assembly_t const & workAsm, 
      assembly::assemblyDiffs_t & assemblyDiffs);

    void synchronizeCache();

    void fillWorkCache(int cFd, int wFd);

    void rebuildWorkCache(int wFd);

    std::unordered_map<std::string, std::shared_ptr<Asset>> const & getCurrAssets() const noexcept;
    std::unordered_map<std::string, std::shared_ptr<Asset>> const & getWorkAssets() const noexcept;

  private:
    bool dying = false;

    path_t adbPath;
    path_t cacheDir;
    std::string cacheFile;
    FileRef adbFileRef;
    FileRef cacheFileRef;
    size_t cacheMapWindowSize;

    fs::file_time_type lastAdbLoadTime;

    std::unordered_map<std::string, std::shared_ptr<Asset>> currAssetMap;
    std::unordered_map<std::string, std::shared_ptr<Asset>> workAssetMap;

    AllocDesc currCacheMap;
    AllocDesc workCacheMap;

    std::thread checkForFileChangesThread;
    std::mutex checkForFileChangesMx;
    std::condition_variable checkForFileChangesCv;

    std::thread synchronizeCacheThread;
    std::mutex synchronizeCacheMx;
    std::condition_variable synchronizeCacheCv;

    // TODO: Interleave above things in here to save memory
    alignas(cacheLineSizeDestructive)
    std::atomic<bool> checkingForFileChanges = false;
    alignas(cacheLineSizeDestructive)
    std::atomic<bool> synchronizingCache = false;
    alignas(cacheLineSizeDestructive)
    std::atomic<bool> shouldCheckFiles = false;
    alignas(cacheLineSizeDestructive)
    std::atomic<bool> checkingAssetFiles = false;
    alignas(cacheLineSizeDestructive)
    std::atomic<bool>
    assetFilesChanged = false;
    alignas(cacheLineSizeDestructive)
    std::atomic<bool>
    adbFileChanged = false;
    alignas(cacheLineSizeDestructive)
    std::atomic<bool>
    cacheFileChanged = false;
  };
  
  std::unordered_map<std::string, std::shared_ptr<Asset>> const & AssetManager::getCurrAssets() const noexcept
  {
    return currAssetMap;
  }

  std::unordered_map<std::string, std::shared_ptr<Asset>> const & AssetManager::getWorkAssets() const noexcept
  {
    return workAssetMap;
  }

  static inline std::optional<AssetManager> assetMan;
}


#endif // #ifndef ASSETMANAGER_H
