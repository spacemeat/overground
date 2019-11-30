#ifndef MEMORYPLAN_H
#define MEMORYPLAN_H

#include <vector>
#include "memoryPlan-gen.h"
#include "graphicsUtils.h"

namespace overground
{
  struct MemorySubresource
  { // size and offset into vkBuffer / vkImage
    std::string assetName;
    size_t offset;
    size_t size;
    size_t refCount = 0;
  };

  // TODO: There's a vk enum for this. Need it even? Have the variant.
//  enum class ResourceType { buffer, image };

  struct MemoryBackedResource
  {
//    ResourceType type;   // buffer or image or ...
    std::variant<vk::Buffer, vk::Image> vulkanResource;
    std::vector<MemorySubresource> subresources;
    size_t offset;
    size_t size;
    bool priority;
  };

  struct MemoryAlloc
  {
//    size_t memoryTypeIdx;
    size_t size;
    size_t freeSize;
    vk::DeviceMemory alloc;

    std::vector<MemoryBackedResource> resources;
  };

  struct MemoryType
  {
    vk::MemoryPropertyFlags memoryProps;
    size_t allocChunkSize;
    bool mappable;
    std::vector<MemoryAlloc> allocs;
  };

  struct AllocAddress
  {
    size_t memoryTypeIdx;
    size_t memoryAllocIdx;
    size_t resourceIdx;
    size_t subresourceIdx;
  };

  struct MemoryUsageType
  {
    std::vector<size_t> memoryTypeIdxs;
    std::unordered_map<std::string, AllocAddress> assetAllocMap; 
  };

  class MemoryPlan
  {
  public:
    MemoryPlan(memoryPlan::memoryPlan_t const & data);
    ~MemoryPlan();

    stringDict<MemoryUsageType> const & getMemoryUsageTypes() const noexcept;

    void addObjects(std::string_view usageType, std::vector<std::string> assets, bool priority);
    void reprioritize(std::string_view usageType, std::vector<std::string> assets, bool priority);
    void removeObjects(std::string_view usageType, std::vector<std::string> assets);
    void moop();

  private:
    void allocateStagingMemory();

    size_t numAllocRetries;
    size_t stagingSize;
    std::vector<MemoryType> memoryTypes;
    stringDict<MemoryUsageType> memoryUsageTypes;
    vk::PhysicalDeviceMemoryProperties deviceMemProps;
    std::vector<MemoryType> memoryTypes;

    vk::DeviceMemory stagingAlloc;
    size_t stagingSize = 0;
  };


  stringDict<MemoryUsageType> const & MemoryPlan::getMemoryUsageTypes() const noexcept
  {
    return memoryUsageTypes;
  }
}

#endif // #ifndef MEMORYPLAN_H
