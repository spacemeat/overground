#include "assetManager.h"
#include "assemblyManager.h"

using namespace std;
using namespace overground;


PluginAssetBase::PluginAssetBase(string_view assetName)
: assetName(assetName)
{
}


size_t PluginAssetBase::getCompiledBufferSize(asset::asset_t const & asset) const
{
  log(thId, logTags::err, fmt::format("Asset plugin '{}' does not implement required virtual function 'getCompiledBufferSize'. DO IT, even if it doesn't use the video buffer.", assetName));
}


void PluginAssetBase::compileToBuffer(asset::asset_t const & asset, fs::path const & srcPath, asset::asset_t & desc, std::byte * buffer)
{
  log(thId, logTags::err, fmt::format("Asset plugin '{}' does not implement required virtual function 'compileToBuffer'. DO IT, even if it doesn't use the video buffer.", assetName));
}
