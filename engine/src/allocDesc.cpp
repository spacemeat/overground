#include "allocDesc.h"

using namespace std;
using namespace overground;


void AllocDesc::trackAsset(string_view assetName, size_t size)
{
  bufferDesc.push_back(assetName, AllocDescEntry { string(assetName), 0, size });
}


void AllocDesc::setAssetOffset(string_view assetName, size_t offset)
{
  bufferDesc[assetName].offset = offset;
}


size_t AllocDesc::getAllocSize()
{
  return totalAllocSize;
}


stringDict<AllocDescEntry> const & AllocDesc::getBufferDesc() const noexcept
{
  return bufferDesc;
}
