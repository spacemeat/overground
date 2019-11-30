#include "memoryPlan.h"
#include "graphics.h"
#include "assetManager.h"
#include "feature.h"

using namespace std;
using namespace overground;


MemoryPlan::MemoryPlan(memoryPlan::memoryPlan_t const & data)
{
  numAllocRetries = data.allocRetries;
  stagingSize = data.stagingSize;

  deviceMemProps = graphics->getPhysicalDevice().getMemoryProperties();

  // First, get the memory types. We only record the assembly data that matches the exact properties, and in the same order as deviceMemProps.memoryTypes (so we can use the same index).
  for (size_t typeIdx = 0; typeIdx < deviceMemProps.memoryTypeCount; ++typeIdx)
  {
    auto & vkMemType = deviceMemProps.memoryTypes[typeIdx];

    for (auto & mt : data.memoryTypes)
    {
      vk::MemoryPropertyFlags combinedProps = (vk::MemoryPropertyFlags) 0;
      for (auto & mp : mt.memoryProps)
        { combinedProps |= mp; }

      // Exactly equals; we're recording all the possible combinations.
      if (combinedProps == vkMemType.propertyFlags)
      {
        memoryTypes.emplace_back(MemoryType 
          { combinedProps, mt.chunkSize, mt.mappable } );
        break;
      }
    }
  }

  // Next, find the best memory types for each usage type.
  for (auto & usageType : data.usageTypes.vect())
  {
    auto & mut = memoryUsageTypes.push_back(usageType.name, MemoryUsageType { });

    for (auto & opv : usageType.memoryProps)
    {
      vk::MemoryPropertyFlags combinedProps = (vk::MemoryPropertyFlags) 0;
      for (auto & mp : opv)
        { combinedProps |= mp; }

      // Find the first matching memory type the device supports, and record its index.
      for (size_t typeIdx = 0; typeIdx < deviceMemProps.memoryTypeCount; ++typeIdx)
      {
        auto & vkMemType = deviceMemProps.memoryTypes[typeIdx];
        if ((vkMemType.propertyFlags & combinedProps) != (vk::MemoryPropertyFlagBits) 0)
        {
          mut.memoryTypeIdxs.push_back(typeIdx);
          break;
        }
      }
    }
  }

  // Next, find the staging type, and allocate blocks sufficient for staging with n threads.
  allocateStagingMemory();
}


// This is called by Feature instances. Some usage info may come from them, but hmmm.
void MemoryPlan::addObjects(Feature * feature)
{
  // let's get all the asset objs
  vector<Asset *> assetPtrs;
  feature->forEachSubresourceNeeded([&](
    auto & assetName, std::string_view usageType, 
    std::variant<vk::ImageCreateFlagBits, vk::BufferCreateFlagBits> createFlags, 
    std::variant<vk::ImageUsageFlagBits, vk::BufferUsageFlagBits> usageFlags)
  {
    if (Asset * asset = assetMan->getAsset(assetName);
        asset != nullptr)
    {
      // If asset is alredy where it should be, just addref it.
      if (auto it = ut.assetAllocMap.find(asset->name);
        it != ut.assetAllocMap.end())
      {
        AllocAddress const & aa = it->second;
        ut.allocs[aa.memoryAllocIdx].resources[aa.resourceIdx].subresources[aa.subresourceIdx].refCount += 1;
      }
      else
      {
        assetPtrs.push_back(asset);
      }
    }
    // TODO: else what?
    log(thId, logTags::err, fmt::format("Catastrophe! Bad asset name: {}", assetName));
  });

  // sort assetPtrs into groupable subresources for vkBuffers or vkImages. Try to combine images into an image array, but note that formats and sizes and such must be compatible.
  std::sort(assetPtrs.begin(), assetPtrs.end(), [](Asset * a, Asset * b)
  {
    if (a->isImage() == true  && b->isImage() == false) { return true; }
    if (a->isImage() == false && b->isImage() == true ) { return false; }
    if (a->isImage())
    {

    }
    else
    {

    }
  });

  // Find an appropriate allocation. Must have room for -all- the assets (packed as images and buffers).
  MemoryAlloc * palloc = nullptr;
  for (size_t allocIdx = 0; allocIdx < ut.allocs.size(); ++allocIdx)
  {
    MemoryAlloc * pallocCand = & ut.allocs[allocIdx];
    if (pallocCand->freeSize >= totalAllocSize)
    {
      palloc = pallocCand;

      break;
    }
  }

  // If there isn't one, make an allocation in the best memory type (the best device heap, basically).
  if (palloc == nullptr)
  {
    // get memory types from physical device
    vk::PhysicalDeviceMemoryProperties devMemoryProps =
      graphics->getPhysicalDevice().getMemoryProperties();

    for (auto & typ : ut.types)
    {
      // Try to allocate a block. If it fails, continue to the next memory type.

      // find the appropriate memory type index
      size_t vkMemTypeIdx = devMemoryProps.memoryTypeCount;
      for (size_t idx = 0; idx < devMemoryProps.memoryTypeCount; ++idx)
      {
        if (devMemoryProps.memoryTypes[idx].propertyFlags == typ.memoryProps)
        {
          vkMemTypeIdx = idx;
          break;
        }
      }

      if (vkMemTypeIdx == devMemoryProps.memoryTypeCount)
      {
        // None of the memory types support this memory type combo. That's okay; move on to the next one.
        continue;
      }
      else
      {
        auto allocResult = graphics->getDevice().allocateMemory(vk::MemoryAllocateInfo { typ.allocChunkSize, vkMemTypeIdx });
        if (! allocResult)
        {
          // Not enough room to allocate a new block. That's okay; move on to the next memory type.
          log(thId, logTags::info, "Out of memory blocks in memory type {}. Falling back.");
          continue;
        }
        else
        {
          palloc = & ut.allocs.emplace_back( MemoryAlloc {
            vkMemTypeIdx,
            typ.allocChunkSize,
            typ.allocChunkSize - totalAllocSize,
            allocResult,
            {}
          });
          break;
        }
      }

      // We have an allocation. Let's use it.
      if (palloc)
        { break; }
    }
  }

  if (palloc)
  {

    // make the image out of the packed assets
    if (imageDataSize > 0)
    {
      vk::Image newImage;
      palloc->resources.emplace_back( MemoryBackedResource {

      });
    }

    // make the buffer out of the packed assets
    if (bufferDataSize > 0)
    {
      vk::Buffer newBuffer;
      palloc->resources.emplace_back();
    }
  }
  else
  {

  }
}


void MemoryPlan::reprioritize(std::string_view usageType, std::vector<std::string> assets, bool priority)
{

}


void MemoryPlan::removeObjects(std::string_view usageType, std::vector<std::string> assets)
{

}


void MemoryPlan::moop()
{

}


void MemoryPlan::allocateStagingMemory()
{
  auto & mut = memoryUsageTypes["staging"];
  for (size_t mtIdx = 0; mtIdx < mut.memoryTypeIdxs.size(); ++mtIdx)
  {
    auto & mt = memoryTypes[mut.memoryTypeIdxs[mtIdx]];

    size_t allocSize = stagingSize;
    for (size_t retryIdx = 0; retryIdx < numAllocRetries; ++retryIdx)
    {
      auto allocResult = graphics->getDevice().allocateMemory(
        vk::MemoryAllocateInfo { mt.allocChunkSize, mtIdx });
      if (! allocResult)
      {
        // Not enough room to allocate a new block. That's okay; move on to the next memory type.
        log(thId, logTags::warn, fmt::format("Failed allocateMemory() size {}, type index {}, retry {}. Falling back.", allocSize, mtIdx, retryIdx));
        allocSize /= 2;
      }
      else
      {
        log(thId, logTags::info, fmt::format("allocateMemory() size {}, type index {}, retry {}.", allocSize, mtIdx, retryIdx));
        stagingAlloc = allocResult;
        stagingSize = allocSize;
        // break out of the outer loop
        mtIdx = mut.memoryTypeIdxs.size();
        break;
      }
    }
  }
}
