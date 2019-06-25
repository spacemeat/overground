#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>
#include "asset.h"
#include "assetData.h"

namespace overground
{
  class Engine;
  class FileReference;

  using AssetFileInfo = std::pair<std::unique_ptr<FileReference>, std::vector<std::string>>;


  class ResourceManager
  {
  public:
    ResourceManager(Engine * engine,
      std::string const & baseAssetPath,
      std::string const & baseAssetDataPath);
    
    Engine * getEngine() { return engine; }

    AssetFileInfo & addAssetDescFile(std::string const & assetFile);
    void removeAssetDescFile(AssetFileInfo const & assetDescFileInfo);

    AssetData * addAssetDataFile(std::string const & assetDataFiles);
    void removeAssetDataFile(std::string const &);

    void informAssetsChanged();

    void checkForAnyFileUpdates(bool synchronous);
    void checkForAssetDescFileUpdate(FileReference * file);
    void checkForAssetUpdates(bool synchronous);
    void updateFromFreshAssets(bool synchronous);

  private:

    Engine * engine;
    std::string baseAssetDir;
    std::string baseAssetDataDir;

    bool assetsChanged = false;

    std::map<std::string, AssetFileInfo> assetFiles;
    //std::map<std::string, std::unique_ptr<FileReferenc>> assetDataFiles;
    
    std::map<std::string, std::unique_ptr<Asset>> assets;

    std::map<std::string, AssetData> assetDataFiles;
  };
}

#endif // #ifndef RESOURCEMANAGER_H
