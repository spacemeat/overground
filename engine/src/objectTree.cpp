#include <numeric>
#include "objectTree.h"
#include "object.h"
#include "graphics.h"

using namespace std;
using namespace overground;


ObjectTree::ObjectTree(assembly::assembly_t const & assembly, std::string_view tableauGroup)
{
  for (auto & tableauIdx : assembly.tableauGroups[tableauGroup])
  {
    auto & tab = assembly.tableaux[tableauIdx];

    for (auto const & obj : tab.objects.vect())
    {
      auto objC = makeObject(obj);
      objects_.push_back(move(objC));

      Object * objP = objects_.back().get();
      
      for (auto & fea : obj.features)
      {
        auto feaC = make_unique<Feature>(fea);
        features_.push_back(move(feaC));
      }
    }
  }

  // compute buffer/image order for device memory
  forEachAsset([&](Asset * asset)
  {
    allocDesc_.trackAsset(asset->name, asset->bufferSize);)
  });

  bool prevBufferWasImage = false;

  // compute buffer/image offsets
  totalAllocSize = accumulate(bufferDesc.begin(), bufferDesc.end(), 0, 
    [&](size_t lhs, AllocDescEntry & rhs)
  {
    // lhs is the total buffer size so far. It must be rounded up to the next alignmet multiple that rhs's asset type requires. That sets the offset for rhs, and then we compute rhs's asset size and end-of-block alignment. That's also the new end-of-buffer size we return.

    // Calc the starting alignment.
    bool useBig = rhs.asset->isImage() != prevBufferWasImage;
    size_t resAlignment = rhs.asset->
      getDeviceMemoryRequirements().alignment;
    size_t alignment = alignment;
    if (useBig)
    {
      vk::PhysicalDeviceLimits pdl;
      graphics->getPhysicalDeviceLimits(pdl);
      alignment = max(alignment, pdl.bufferImageGranularity);
    }

    rhs.offset = lhs + alignment - (lhs % alignment);

    // Calc the size alignment.
    rhs.size = rhs.asset->bufferSize + resAlignment - (rhs.asset->bufferSize % resAlignment);

    prevBufferWasImage = rhs.asset->isImage();

    return rhs.offset + rhs.size;
  });
}
