#include "mesh-provider.h"

using namespace std;
using namespace overground;


MeshAsset::MeshAsset(asset::asset_t const & desc)
: Asset(desc)
{
}


MeshAsset::~MeshAsset()
{

}


size_t MeshAsset::getCompiledBufferSize() const
{

}


void MeshAsset::compileToBuffer(fs::path const & srcPath, asset::asset_t & desc, std::byte * buffer)
{

}
