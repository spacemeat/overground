#ifndef CONFIG_H
#define CONFIG_H

#include <array>
#include <string>
#include "pool.h"
#include "humon.h"
#include "utils.h"
#include "asset.h"
#include "configData.h"

namespace overground
{
  class ResourceManager;
  class FileReference;

  extern std::unique_ptr<Asset> makeConfig(
    ResourceManager * resMan,
    std::string const & assetName,
    FileReference * assetDescFile, 
    humon::HuNode & descFromFile,
    bool cache, bool compress,
    bool monitor);

  class Config : public Asset
  {
  public:
    Config(ResourceManager * resMan,
      std::string const & assetName,
      FileReference * assetDescFile, 
      humon::HuNode & descFromFile,
      bool cache, bool compress,
      bool monitor);

    // void setFileInfo(FileReference * newFileInfo);
    // FileReference * getFileInfo() { return fileInfo; }

    virtual std::string getSrcExtension() override
      { return "config"; }

    virtual void compileSrcAsset(
      path_t const & srcPath) override;

    virtual void applyToEngine() override;

  public:
    ConfigData data;
  };
}

#endif // #ifndef CONFIG_H
