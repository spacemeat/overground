#ifndef MEMORYPLAN_H
#define MEMORYPLAN_H

#include <vector>
#include "memoryPlan-gen.h"
#include "graphicsUtils.h"
#include "feature.h"

namespace overground
{
  size_t padTo(size_t value, size_t alignment)
  {
    auto rem = value % alignment;
    if (rem > 0)
    {
      value = alignment * (value / alignment + 1);
    }

    return value;
  }


  struct Subresource
  { // size and offset into vkBuffer / vkImage
    std::variant<vk::BufferView, vk::ImageView> vulkanSubresource;
    std::string assetName;
    size_t offset;
    size_t size;
    size_t refCount = 0;
  };

  // TODO: There's a vk enum for this. Need it even? Have the variant.
//  enum class ResourceType { buffer, image };

  struct Resource
  {
//    ResourceType type;   // buffer or image or ...
    std::variant<vk::Buffer, vk::Image> vulkanResource;
    std::vector<Subresource> subresources;
    bool priority;
  };

  struct MemoryAlloc
  {
//    size_t memoryTypeIdx;
    size_t size;
    size_t freeSize;
    vk::DeviceMemory alloc;

    std::vector<Resource> resources;
  };

  struct MemoryType
  {
    vk::MemoryPropertyFlags memoryProps;
    size_t allocChunkSize;
    std::vector<MemoryAlloc> allocs;

    MemoryAlloc & getAlloc(vk::MemoryRequirements const & reqs);
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

    void beBlessed();

    void addObjects(Feature * feature, bool priority);
    void reprioritize(Feature * feature, bool priority);
    void removeObjects(Feature * feature);
    void moop();

  private:
    void allocateStagingMemory();
    Resource & allocateResource(std::variant<vk::Buffer, vk::Image> resourceObject, vk::MemoryRequirements const & reqs);
    void registerSubresource(Resource & ogResource, std::variant<vk::BufferView, vk::ImageView> subresourceView);

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
