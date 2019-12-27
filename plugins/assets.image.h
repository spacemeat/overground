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

    std::array<size_t, 3> const & getExtents() const;
    size_t getNumMipLevels() const;

    vk::ComponentMapping getComponentMapping() const noexcept;

  protected:
    virtual std::string getAssetType_impl() const noexcept;
//    virtual void loadAssetInfo_impl(path_t file, bool loadFromSrc) override;

    virtual void computeImportData_impl() override;
    virtual void compileToBuffer_impl(std::byte * buffer) override;

  private:
    size_t numImages = 1;
    vk::Extent3D extents;
    size_t numMipLevels;
    vk::ComponentMapping componentMapping;
  };

  Image::Image(asset::asset_t const & desc)
  : Asset(desc)
  {
    auto & descData = std::get<asset::image_t>(desc.importData);

//    descData.type
    extents = vk::Extent3D(descData.dims[0], descData.dims[1], descData.dims[2]);
    numMipLevels = descData.numMipLevels;
  }
}

#endif // #ifndef ASSETS_IMAGE_H
