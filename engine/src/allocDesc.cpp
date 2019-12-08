#include <numeric>
#include "allocDesc.h"
#include "assetManager.h"
#include "graphics.h"
#include "assets.image.h"

using namespace std;
using namespace overground;


void AllocDesc::reset(bool computeAlignments)
{
  this->computeAlignments = computeAlignments;

  totalAllocSize = 0;
  bufferDesc.clear();
}


void AllocDesc::trackAsset(string_view assetName, size_t cacheOffset, size_t cacheSize)
{
  bufferDesc.push_back(assetName, AllocDescEntry { string(assetName), cacheOffset, cacheSize });

  // This will get recompued if computeMap() is used.
  if (this->computeAlignments == false)
    { totalAllocSize = max(totalAllocSize, cacheOffset + cacheSize); }
}


void AllocDesc::trackAsset(string_view assetName, size_t cacheOffset, size_t cacheSize, array<size_t, 3> const & dims, size_t numMipLevels, vk::Format format)
{
  bufferDesc.push_back(assetName, AllocDescEntry { string(assetName), cacheOffset, cacheSize, AllocDescImageData { dims, numMipLevels, format } });

  if (this->computeAlignments == false)
    { totalAllocSize = max(totalAllocSize, cacheOffset + cacheSize); }
}


void AllocDesc::trackAsset(Asset * asset)
{
  if (asset->isImage())
  {
    Image * image = dynamic_cast<Image *>(asset);
    bufferDesc.push_back(asset->getName(), AllocDescEntry { 
      string(asset->getName()), 
      asset->getCacheOffset(), 
      asset->getCacheSize(), 
      AllocDescImageData { 
        image->getDims(), 
        image->getNumMipLevels(), 
        image->getFormat() } } );
  }
  else
  {
    bufferDesc.push_back(asset->getName(), AllocDescEntry {
      string(asset->getName()), 
      asset->getCacheOffset(), 
      asset->getCacheSize() } );
  }
}


/*
void AllocDesc::computeMap()
{
  if (this->computeAlignments == false)
    { return; }

  bool prevBufferWasImage = false;

  // compute buffer/image offsets

  totalAllocSize = accumulate(bufferDesc.vect().begin(), bufferDesc.vect().end(), 0, 
    [&](size_t lhs, AllocDescEntry & rhs)
  {
    // lhs is the total buffer size so far. It must be rounded up to the next alignmet multiple that rhs's asset type requires. That sets the offset for rhs, and then we compute rhs's asset size and end-of-block alignment. That's also the new end-of-buffer size we return.

    Asset * rhsAsset = assetMan->getAsset(rhs.assetName);
    size_t sizeAlignment = 0;
    size_t offsetAlignment = 0;
    // Calc the starting alignment.
    if (rhsAsset->isImage())
    {
    }
    else
    {
      
    }
    
    sizeAlignment = rhsAsset->
      getDeviceMemoryRequirements().alignment;
    offsetAlignment = sizeAlignment;
    if (rhsAsset->isImage() != prevBufferWasImage)
    {
      vk::PhysicalDeviceLimits pdl;
      graphics->getPhysicalDeviceLimits(pdl);
      offsetAlignment = max(offsetAlignment, pdl.bufferImageGranularity);
    }

    // round up the offset
    rhs.offset = lhs;
    if (offsetAlignment > 0 && rhs.offset % offsetAlignment > 0)
      { rhs.offset += offsetAlignment - (rhs.offset % offsetAlignment); }

    // round up the size
    rhs.size = rhsAsset->getCacheSize();
    if (sizeAlignment > 0 && rhs.size % sizeAlignment > 0)
      { rhs.size += sizeAlignment - (rhs.size % sizeAlignment); }

    prevBufferWasImage = rhsAsset->isImage();

    return rhs.offset + rhs.size;
  });
}
*/


//void AllocDesc::setAssetOffset(string_view assetName, size_t offset)
//{
//  bufferDesc[assetName].offset = offset;
//}


size_t AllocDesc::getAllocSize()
{
  return totalAllocSize;
}


stringDict<AllocDescEntry> const & AllocDesc::getBufferDesc() const noexcept
{
  return bufferDesc;
}
