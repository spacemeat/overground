#ifndef CONFIG_H
#define CONFIG_H

#include <array>
#include <string>
#include "pool.h"
#include "humon.h"
#include "utils.h"
#include "asset.h"
#include "config-gen.h"

namespace overground
{
  class ResourceManager;
  class FileReference;

  extern std::unique_ptr<Asset> makeConfig(
    ResourceManager * resMan,
    std::string_view assetName,
    FileReference * assetDescFile, 
    humon::HuNode & descFromFile,
    bool cache, bool compress,
    bool monitor);


  class Config : public Asset
  {
  public:
    enum class Deltas : int
    {
      None                = 0,
      JobManagement       = 1 << 0,
      Window              = 1 << 1,
      WindowExtents       = 1 << 2,
      VulkanInstance      = 1 << 3,
      PhysicalDevice      = 1 << 4,
      LogicalDevice       = 1 << 5,
      Swapchain           = 1 << 6,

      Framebuffer         = 1 << 7,
      RenderPasses        = 1 << 8,
      NumConcurrentFrames = 1 << 9,
      GraphicsPipelines   = 1 << 10,
    };

    Config(ResourceManager * resMan,
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
    config_t data;
  };


  Config::Deltas integrate(config_t & lhs, config_t const & rhs);
}

#endif // #ifndef CONFIG_H
