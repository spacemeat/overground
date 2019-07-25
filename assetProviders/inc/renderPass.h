#ifndef CONFIG_H
#define CONFIG_H

#include <array>
#include <string>
#include "pool.h"
#include "humon.h"
#include "utils.h"
#include "asset.h"
#include "renderPass-gen.h"

namespace overground
{
  class ResourceManager;
  class FileReference;

  extern std::unique_ptr<Asset> makeRenderPass(
    std::string_view assetName,
    FileReference * assetDescFile, 
    humon::HuNode & descFromFile,
    bool cache, bool compress,
    bool monitor);


  class RenderPass : public Asset
  {
  public:
    RenderPass(
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
    renderPass_t data;
  };
}

#endif // #ifndef CONFIG_H
