#ifndef ASSET_H
#define ASSET_H

#include <fstream>
#include "utils.h"
#include "fileReference.h"
#include "resourceManager.h"

namespace overground
{
  class AssetData;

  class Asset
  {
  public:
    Asset(
      ResourceManager * resMan,
      std::string const & assetName,
      FileReference * assetDescFile, 
      humon::HuNode & descFromFile,
      bool cache, bool compress,
      bool monitor);

    bool isCached() const { return isCached; }
    bool isCompiled() const { return isCompiled; }
    bool isMonitored() const { return isMonitored; }

    humon::HuNode const & getDesc() const { return *desc; }

    AssetData * getAssetData() const;
    void updateFileModTimes();

    enum class Status
    {
      upToDate,
      srcFileIsNew,
      compiledFileIsNew,  // if compiled asset
      hostBufferIsNew     // iif host-backed asset
    };

    Status getStatus() { return status; }
    void setUpdated();

    using compiledAssetLoader_t = std::ifstream;
    using compiledAssetSaver_t = std::ofstream;

    virtual std::string getSrcExtension() = 0;
    virtual std::string getCompiledExtension();

    virtual void compileSrcAsset(
      path_t const & srcPath);
    virtual void loadCompiledAsset(
      compiledAssetLoader_t & file);
    virtual void saveCompiledAsset(
      compiledAssetSaver_t & file);

    virtual uint64_t getCompiledSize();
    virtual void * getCompiledData();

    virtual int getGraphicsBufferId();
    virtual uint64_t getGraphicsBufferSize();
    virtual void applyToBuffer(void * targetBuffer);

    virtual void applyToEngine();

  protected:
    ResourceManager * getResMan() { return resMan; }

  private:
    ResourceManager * resMan;
    std::string assetName;
    FileReference * assetDescFile;
    humon::nodePtr_t desc;
    bool isCached;
    bool isCompiled;
    bool isMonitored;
    time_t modTime;
    time_t runtimeModTime;

    Status status = Status::compiledFileIsNew;
    AssetData * assetData;
  };
}

#endif // #ifndef ASSET_H
