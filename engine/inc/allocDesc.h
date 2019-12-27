#ifndef ALLOCDESC_H
#define ALLOCDESC_H

#include "utils.h"
#include "graphicsUtils.h"

namespace overground
{
  struct AllocDescImageData
  {
    std::array<size_t, 3> dims;
    size_t numMipLevels;
    vk::Format format;
  };

  struct AllocDescEntry
  {
    std::string assetName;
    size_t offset;
    size_t dataSize;
    size_t storageSize;
    std::optional<AllocDescImageData> imageData;
  };


  enum class alignmentRule
  {
    none,
    cacheLine,
    cacheMap,
  };


  class AllocDesc
  {
  public:
    AllocDesc(alignmentRule align = alignmentRule::cacheLine);
    void reset(alignmentRule align = alignmentRule::cacheLine);
    void track(std::string_view assetName, size_t dataSize);
    void track(std::string_view assetName, size_t offset, size_t dataSize, size_t storageSize);
    void track(std::string_view assetName, size_t offset, size_t dataSize, size_t storageSize, std::array<size_t, 3> dims,size_t numMipLevels, vk::Format format);
    void track(Asset * asset);

  private:
    size_t alignSize(size_t size);
    size_t skipVerbotenAlignments(size_t offset, size_t size);

  public:
    size_t getAllocSize();
    stringDict<AllocDescEntry> const & getAllocDescEntries() const noexcept;

  private:
    alignmentRule align;
    size_t alignmentValue;
    size_t verbotenAlignmentValue;

    size_t totalAllocSize = 0;
    stringDict<AllocDescEntry> allocDescEntries;
  };


}


#endif // #ifndef ALLOCDESC_H
