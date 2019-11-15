#ifndef ASSETS_SHADER_H
#define ASSETS_SHADER_H

#include "asset.h"

namespace overground
{
  class Shader : public Asset
  {
  public:
    Shader(asset::asset_t const & desc);
    virtual ~Shader();

  protected:
    virtual void loadAssetInfo_impl(path_t file, bool loadFromSrc) override;

    virtual void compileToAss_impl()  override;
    virtual void compileToBuffer_impl(std::byte * buffer)  override;
  };
}

#endif // #ifndef ASSETS_SHADER_H
