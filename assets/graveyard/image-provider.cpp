#include "image-provider.h"

using namespace std;
using namespace overground;


ImageAsset::ImageAsset(asset::asset_t const & desc)
: PluginAssetBase(desc)
{
}


ImageAsset::~ImageAsset()
{

}


size_t ImageAsset::getCompiledBufferSize() const
{

}


void ImageAsset::compileToBuffer(fs::path const & srcPath, asset::asset_t & desc, std::byte * buffer)
{

}
