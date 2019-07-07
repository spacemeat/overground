#ifndef ASSET_H
#define ASSET_H

#include <fstream>
#include "utils.h"
//#include "fileReference.h"

namespace overground
{
  class ResourceManager;
  class FileReference;

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
    virtual ~Asset();

    bool isCached() const { return thisIsCached; }
    bool isCompiled() const { return thisIsCompiled; }
    bool isMonitored() const { return thisIsMonitored; }

    humon::HuNode const & getDesc() const { return *desc; }
    void setDesc(humon::HuNode const & desc);

    bool doesNeedUpdateFromSrc()
      { return needsUpdateFromSrc; }
    bool doesNeedUpdateFromOpt()
      { return needsUpdateFromOpt; }
    bool didReloadAssetData()
      { return didReload; }
    
    void setNeedsUpdateFromSrc()
      { needsUpdateFromSrc = true; }
    void setNeedsUpdateFromOpt()
      { needsUpdateFromOpt = true; }
    void setDidReloadAssetData()
      { didReload = true; }

    void clearNeedUpdateFromSrc()
      { needsUpdateFromSrc = false; }
    void clearNeedUpdateFromOpt()
      { needsUpdateFromOpt = false; }
    void clearDidReloadAssetData()
      { didReload = false; }

    using compiledAssetLoader_t = std::ifstream;
    using compiledAssetSaver_t = std::ofstream;

  protected:
    virtual std::string getSrcExtension() = 0;
    virtual std::string getCompiledExtension();

  public:
    void compileSrcAsset();
    void loadCompiledAsset();
    void saveCompiledAsset();
    
  protected:
    virtual void compileSrcAsset_impl(path_t const & path);
    virtual void loadCompiledAsset_impl(
      compiledAssetLoader_t & file);
    virtual void saveCompiledAsset_impl(
      compiledAssetSaver_t & file);

  public:
    virtual uint64_t getCompiledSize();
    virtual void * getCompiledData();

    virtual int getGraphicsBufferId();
    virtual uint64_t getGraphicsBufferSize();

    void applyToBuffer(void * targetBuffer);
    void applyToEngine();

  protected:
    virtual void applyToBuffer_impl(void * targetBuffer);
    virtual void applyToEngine_impl();

  protected:
    ResourceManager * getResMan() { return resMan; }

  private:
    ResourceManager * resMan;
    std::string assetName;
    FileReference * assetDescFile;
    humon::nodePtr_t desc;
    path_t srcFilePath;
    path_t optFilePath;
    bool thisIsCached;
    bool thisIsCompiled;
    bool thisIsMonitored;

    bool needsUpdateFromSrc = true;
    bool needsUpdateFromOpt = true;
    bool didReload = true;
  };
}

#endif // #ifndef ASSET_H