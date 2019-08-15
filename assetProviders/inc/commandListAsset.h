#ifndef COMMANDLIST_AP_H
#define COMMANDLIST_AP_H

#include <array>
#include <string>
#include "pool.h"
#include "humon.h"
#include "utils.h"
#include "asset.h"
#include "commandList-gen.h"

namespace overground
{
  class ResourceManager;
  class FileReference;

  extern std::unique_ptr<Asset> makeCommandList(
    std::string_view assetName,
    FileReference * assetDescFile, 
    humon::HuNode & descFromFile,
    bool cache, bool compress,
    bool monitor);


  class CommandListAsset : public Asset
  {
  public:
    CommandListAsset(
      std::string_view assetName,
      FileReference * assetDescFile, 
      humon::HuNode & descFromFile,
      bool cache, bool compress,
      bool monitor);

    virtual std::string getSrcExtension() override
      { return "hu"; }

    std::string print() const;

  protected:
    virtual void compileSrcAsset_impl(path_t const & path) override;

    virtual void applyToEngine_impl() override;

  public:
    commandList_t data;
  };
}

#endif // #ifndef COMMANDLIST_AP_H
