#ifndef ALLOCDESC_H
#define ALLOCDESC_H

#include "utils.h"

namespace overground
{
  struct AllocDescEntry
  {
    std::string assetName;
    size_t offset;
    size_t size;
  };

  class AllocDesc
  {
  public:
    void trackAsset(std::string_view assetName, size_t size);
    void setAssetOffset(std::string_view assetName, size_t offset);
    size_t getAllocSize();
    stringDict<AllocDescEntry> const & getBufferDesc() const noexcept;

  private:
    void * allocBlock = nullptr;
    size_t totalAllocSize = 0;
    stringDict<AllocDescEntry> bufferDesc;
  };
}


#endif // #ifndef ALLOCDESC_H
