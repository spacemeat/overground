#include "shader-provider.h"

using namespace std;
using namespace overground;


ShaderAsset::ShaderAsset(asset::asset_t const & desc)
: PluginAssetBase(desc)
{
}


ShaderAsset::~ShaderAsset()
{

}


size_t ShaderAsset::getCompiledBufferSize() const
{

}


void ShaderAsset::compileToBuffer(fs::path const & srcPath, asset::asset_t & desc, std::byte * buffer)
{

}
