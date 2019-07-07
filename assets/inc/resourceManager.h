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

  using AssetFileInfo = std::pair<std::unique_ptr<FileReference>, std::vector<std::string>>;

  using makeAssetFn_t = std::function<
    std::unique_ptr<Asset>(
      ResourceManager * resMan,
      std::string const & assetName,
      FileReference * assetDescFile, 
      humon::HuNode & descFromFile,
      bool cache, bool compress,
      bool monitor
  )>;

  class ResourceManager
  {
  public:
    ResourceManager(Engine * engine, 
      JobManager * jobManager,
      path_t const & baseAssetDescPath,
      path_t const & baseAssetDataPath);
    
    Engine * getEngine() { return engine; }
    JobManager * getJobManager() { return jobManager; }

    path_t const & getBaseAssetDescDir() const
      { return baseAssetDescDir; }
    path_t const & getBaseAssetDataDir() const
      { return baseAssetDataDir; }

    void registerAssetProvider(
      std::string const & assetKind,
      makeAssetFn_t const & fn);    

    std::unique_ptr<Asset> makeAsset(
      std::string const & assetName,
      FileReference * assetDescFile, 
      humon::HuNode & descFromFile,
      bool cache, bool compress,
      bool monitor);

    AssetDescFile * addAssetDescFile(std::string const & assetFile);
    void removeAssetDescFile(AssetFileInfo const & assetDescFileInfo);

    AssetDataFile * addAssetDataFile(std::string const & newAssetDataFile, bool asCompiledFile);
    void removeAssetDataFile(std::string const & file, bool asCompiledFile);

    AssetDataFile * addAssetSrcFile(std::string const & assetDataFiles);
    void removeAssetSrcFile(std::string const & file);

    AssetDataFile * addAssetOptFile(std::string const & assetDataFiles);
    void removeAssetOptFile(std::string const & file);

    void informAssetsChanged();

    void checkForAnyFileUpdates(bool synchronous);
    void checkForAssetDescFileUpdate(FileReference * file);
    void checkForAssetUpdates(bool synchronous);
    void updateFromFreshAssets(bool synchronous);

  private:
    std::map<std::string, makeAssetFn_t> assetProviders;

    Engine * engine;
    JobManager * jobManager;
    path_t baseAssetDescDir;
    path_t baseAssetDataDir;

    bool assetsChanged = false;

    std::map<std::string, AssetDescFile> assetDescFiles;
    std::map<std::string, AssetDataFile> assetSrcFiles;
    std::map<std::string, AssetDataFile> assetOptFiles;



    //std::map<std::string, AssetFileInfo> assetFiles;
    //std::map<std::string, std::unique_ptr<FileReferenc>> assetDataFiles;
    
    std::map<std::string, std::unique_ptr<Asset>> assets;
  };
}

#endif // #ifndef RESOURCEMANAGER_H
