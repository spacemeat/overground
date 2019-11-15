#ifndef ASSETS_MESH_H
#define ASSETS_MESH_H

#include "asset.h"

namespace overground
{
  class Mesh : public Asset
  {
  public:
    Mesh(asset::asset_t const & desc);
    virtual ~Mesh();

  protected:
    virtual void loadAssetInfo_impl(path_t file, bool loadFromSrc) override;

    virtual void compileToAss_impl()  override;
    virtual void compileToBuffer_impl(std::byte * buffer)  override;
  };
}

#endif // #ifndef ASSETS_MESH_H
