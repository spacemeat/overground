#ifndef MEMORYPLAN_H
#define MEMORYPLAN_H

#include <vector>
#include "memoryPlan-gen.h"
#include "graphicsUtils.h"

namespace overground
{
  struct MemoryType
  {
    vk::MemoryPropertyFlagBits memoryProps;
    size_t allocChunkSize;
    bool mappable;
  };

  struct MemorySubresource
  { // size and offset into vkBuffer / vkImage
    std::string assetName;
    size_t offset;
    size_t size;
  };

  // TODO: There's a vk enum for this. Need it even? Have the variant.
//  enum class ResourceType { buffer, image };

  struct MemoryBackedResource
  {
//    ResourceType type;   // buffer or image or ...
    std::variant<vk::Buffer, vk::Image> vulkanResource;
    std::vector<MemorySubresource> subresources;
    bool priority;
  };

  struct MemoryAlloc
  {
    size_t typeIdx;
    vk::DeviceMemory alloc;
    std::vector<MemoryBackedResource> resources;
  };

  struct MemoryUsageType
  {
    std::vector<MemoryType> types;
    std::vector<MemoryAlloc> allocs;
  };

  class MemoryPlan
  {
  public:
    MemoryPlan(memoryPlan::memoryPlan_t const & data);
    ~MemoryPlan();

    stringDict<MemoryUsageType> const & getMemoryTypes() const noexcept;



  private:
    stringDict<std::vector<MemoryType>> memoryTypes;
  };
}

#endif // #ifndef MEMORYPLAN_H
