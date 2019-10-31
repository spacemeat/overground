#ifndef IMAGE_PROVIDER_H
#define IMAGE_PROVIDER_H

#include "assetManager.h"

namespace overground
{
  class ImageAsset : public PluginAssetBase
  {
    ImageAsset(asset::asset_t const & desc);
    virtual ~ImageAsset();

    virtual size_t getCompiledBufferSize() const override;
    virtual void compileToBuffer(fs::path const & srcPath, asset::asset_t & desc, std::byte * buffer) override;
  };

}

#endif // ifndef IMAGE_PROVIDER_H
