#ifndef ASSETS_IMAGE_H
#define ASSETS_IMAGE_H

#include <array>
#include "asset.h"
#include "graphicsUtils.h"

namespace overground
{
  class Image : public Asset
  {
  public:
    Image(asset::asset_t const & desc);
    virtual ~Image();

    std::array<size_t, 3> const & getDims() const;
    size_t getNumMipLevels() const;
    vk::Format getFormat() const;

  protected:
    virtual void loadAssetInfo_impl(path_t file, bool loadFromSrc) override;

    virtual void compileToAss_impl() override;
    virtual void compileToBuffer_impl(std::byte * buffer) override;

  private:
    std::array<size_t, 3> dims;
    size_t numMipLevels;
    vk::Format format;
  };

  Image::Image(asset::asset_t const & desc)
  : Asset(desc)
  {
    auto & descData = std::get<asset::image_t>(desc.importData);

    dims = descData.dims;
    numMipLevels = descData.numMipLevels;
    format = descData.format;
  }
}

#endif // #ifndef ASSETS_IMAGE_H
