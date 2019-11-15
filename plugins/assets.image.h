#ifndef ASSETS_IMAGE_H
#define ASSETS_IMAGE_H

#include "asset.h"

namespace overground
{
  class Image : public Asset
  {
  public:
    Image(asset::asset_t const & desc);
    virtual ~Image();

  protected:
    virtual void loadAssetInfo_impl(path_t file, bool loadFromSrc) override;

    virtual void compileToAss_impl()  override;
    virtual void compileToBuffer_impl(std::byte * buffer)  override;
  };
}

#endif // #ifndef ASSETS_IMAGE_H
