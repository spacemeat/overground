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
    size_t size;
    std::optional<AllocDescImageData> imageData;
  };

  class AllocDesc
  {
  public:
    void reset(bool computeAlignments);
    void trackAsset(std::string_view assetName, size_t cacheOffset, size_t cacheSize);
    void trackAsset(std::string_view assetName, size_t cacheOffset, size_t cacheSize, std::array<size_t, 3> const & dims, size_t numMipLevels, vk::Format format);
    void trackAsset(Asset * asset);
    void computeMap();
    size_t getAllocSize();
    stringDict<AllocDescEntry> const & getBufferDesc() const noexcept;

  private:
    bool 
computeAlignments = false;
    size_t totalAllocSize = 0;
    stringDict<AllocDescEntry> bufferDesc;
  };
}


#endif // #ifndef ALLOCDESC_H
