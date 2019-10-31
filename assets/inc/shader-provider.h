#ifndef SHADER_PROVIDER_H
#define SHADER_PROVIDER_H

#include "assetManager.h"

namespace overground
{
  class ShaderAsset : public PluginAssetBase
  {
    ShaderAsset(asset::asset_t const & desc);
    virtual ~ShaderAsset();

    virtual size_t getCompiledBufferSize() const override;
    virtual void compileToBuffer(fs::path const & srcPath, asset::asset_t & desc, std::byte * buffer) override;
  };

}

#endif // ifndef SHADER_PROVIDER_H
