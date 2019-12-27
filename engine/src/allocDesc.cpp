#include <numeric>
#include <new>
#include "allocDesc.h"
#include "assetManager.h"
#include "graphics.h"
#include "assets.image.h"

using namespace std;
using namespace overground;


AllocDesc::AllocDesc(alignmentRule align)
{
  reset(align);
}


void AllocDesc::reset(alignmentRule align = alignmentRule::none)
{
  this->align = align;

  switch (align)
  {
  case alignmentRule::none:
    alignmentValue = 1;
    verbotenAlignmentValue = std::numeric_limits<size_t>::max();
    break;
  case alignmentRule::cacheLine:
    alignmentValue = cacheLineSizeDestructive;
    verbotenAlignmentValue = std::numeric_limits<size_t>::max();
    break;
  case alignmentRule::cacheMap:
    alignmentValue = cacheLineSizeDestructive;
    verbotenAlignmentValue = pageLineSize;
    break;
  }

  totalAllocSize = 0;
  allocDescEntries.clear();
}


void AllocDesc::track(string_view assetName, size_t dataSize)
{
  if (dataSize > verbotenAlignmentValue)
  {
    log(thId, logTags::err, fmt::format("asset '{assetName}' size {} is larger than the map window size {}.", assetName, dataSize, verbotenAlignmentValue));
    return;
  }
  auto offset = totalAllocSize;
  auto storageSize = alignSize(dataSize);
  offset = skipVerbotenAlignments(offset, storageSize);
  allocDescEntries.push_back(assetName, AllocDescEntry { 
    string(assetName), offset, dataSize, storageSize } );
}


void AllocDesc::track(std::string_view assetName, size_t offset, size_t dataSize, size_t storageSize)
{
  allocDescEntries.push_back(assetName, AllocDescEntry { 
    string(assetName), offset, dataSize, storageSize } );
}


void AllocDesc::track(std::string_view assetName, size_t offset, size_t dataSize, size_t storageSize, std::array<size_t, 3> dims,size_t numMipLevels, vk::Format format)
{
  allocDescEntries.push_back(assetName, AllocDescEntry { 
    string(assetName), offset, dataSize, storageSize, 
    AllocDescImageData { dims, numMipLevels, format } } );
}


void AllocDesc::track(Asset * asset)
{
  auto offset = totalAllocSize;
  auto dataSize = asset->getDataSize();
  auto storageSize = alignSize(dataSize);
  offset = skipVerbotenAlignments(offset, storageSize);

  if (asset->isImage())
  {
    Image * image = dynamic_cast<Image *>(asset);
    allocDescEntries.push_back(asset->getName(), AllocDescEntry { 
      string(asset->getName()), offset, dataSize, storageSize,
        AllocDescImageData { image->getDims(), image->getNumMipLevels(), image->getFormat() } } );
  }
  else
  {
    allocDescEntries.push_back(asset->getName(), AllocDescEntry { 
      string(asset->getName()), offset, dataSize, storageSize } );
  }
}


size_t AllocDesc::alignSize(size_t size)
{
  switch (align)
  {
    case alignmentRule::none:
      return size;

    case alignmentRule::cacheLine:
    case alignmentRule::cacheMap:
    {
      auto b = (size % alignmentValue) > 0 ? 1 : 0;
      return size / alignmentValue + b * (alignmentValue - size % alignmentValue);
    }
  }
}


size_t AllocDesc::skipVerbotenAlignments(size_t offset, size_t size)
{
  // if the alloc straddles a forbidden alignment,
  if (offset / verbotenAlignmentValue < 
      (offset + size) / verbotenAlignmentValue)
  {
    return (offset / verbotenAlignmentValue) + 1 * verbotenAlignmentValue;
  }
  return offset;
}


size_t AllocDesc::getAllocSize()
{
  return totalAllocSize;
}


stringDict<AllocDescEntry> const & AllocDesc::getAllocDescEntries() const noexcept
{
  return allocDescEntries;
}
