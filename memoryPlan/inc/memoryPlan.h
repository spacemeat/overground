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


  struct VertexBufferView
  {
  };


  struct IndexBufferView
  {
  };


  using subresourceVariant = variant<vk::BufferView, vk::ImageView, VertexBufferView, IndexBufferView>;


  struct Subresource
  { // size and offset into vkBuffer / vkImage
    subresourceVariant vulkanSubresource;
    std::string subresourceName;
    size_t offset;
    size_t size;
    size_t refCount = 1;
    bool loadFromAsset;
    std::string assetName; // TODO: Explore storing an Asset * instead.
    bool ready = false;
  };

  // TODO: There's a vk enum for this. Need it even? Have the variant.
//  enum class ResourceType { buffer, image };

  struct Resource
  {
//    ResourceType type;   // buffer or image or ...
    std::variant<vk::Buffer, vk::Image> vulkanResource;
    size_t offset;
    size_t size;
    std::vector<Subresource> subresources;
    bool priority;
  };

  struct MemoryAlloc
  {
//    size_t memoryTypeIdx;
    size_t size;
    size_t usedSize;
    vk::DeviceMemory alloc;

    std::vector<Resource> resources;

    size_t getNextImageOffset(size_t imageAlignment);
    size_t getNextBufferOffset(size_t bufferAlignment);

    size_t getFreeImageSize(size_t imageAlignment);
    size_t getFreeBufferSize(size_t bufferAlignment);
  };

  struct MemoryType
  {
    size_t memoryTypeIdx;
    vk::MemoryPropertyFlags memoryProps;
    size_t allocChunkSize;
    std::vector<MemoryAlloc> allocs;

    Resource * allocateResource(
      std::variant<vk::Buffer, vk::Image> resourceObject, vk::MemoryRequirements const & reqs);
  };

  struct AllocAddress
  {
    size_t memoryTypeIdx;
    size_t memoryAllocIdx;
    size_t resourceIdx;
    size_t subresourceIdx;
  };

  class MemoryPlan
  {
  public:
    MemoryPlan(memoryPlan::memoryPlan_t const & data);
    ~MemoryPlan();

    void beBlessed();

    void addResources(Feature * feature, bool priority);
    void reprioritizeResources(Feature * feature, bool priority);
    void removeResources(Feature * feature);
    void moop();
    Subresource * getSubresource(AllocAddress const & address);

  private:
    void allocateStagingMemory();
    Resource * allocateResource(std::variant<vk::Buffer, vk::Image> resourceObject, vk::MemoryPropertyFlagBits additionalMemoryProps, vk::MemoryRequirements const & reqs);
    Subresource & registerSubresource(Resource & ogResource, subresourceVariant subresourceView, std::string_view subresourceName, size_t offset = 0, size_t size = 0);

    size_t numAllocRetries;
    size_t stagingSize;
    std::vector<MemoryType> memoryTypes;
    vk::PhysicalDeviceMemoryProperties deviceMemProps;

    vk::DeviceMemory stagingAlloc;
    size_t stagingSize = 0;
    void * mappedStagingMemory;

    std::unordered_map<std::string, AllocAddress> assetAllocMap;
  };
}

#endif // #ifndef MEMORYPLAN_H
