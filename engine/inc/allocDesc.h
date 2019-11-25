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
    void reset(bool computeAlignments);
    void trackAsset(std::string_view assetName);
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
