#ifndef FRAMEPLAN_AP_H
#define FRAMEPLAN_AP_H

#include <array>
#include <string>
#include "pool.h"
#include "humon.h"
#include "utils.h"
#include "asset.h"
#include "framePlan-gen.h"

namespace overground
{
  class ResourceManager;
  class FileReference;

  extern std::unique_ptr<Asset> makeFramePlan(
    std::string_view assetName,
    FileReference * assetDescFile, 
    humon::HuNode & descFromFile,
    bool cache, bool compress,
    bool monitor);


  class FramePlanAsset : public Asset
  {
  public:
    FramePlanAsset(
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
    framePlan_t data;
  };
}

#endif // #ifndef FRAMEPLAN_AP_H
