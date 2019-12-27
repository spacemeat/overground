#include "memoryPlan.h"
#include "graphics.h"
#include "assetManager.h"
#include "feature.h"
#include "assets.image.h"


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
          { combinedProps, mt.chunkSize } );
        break;
      }
    }
  }

  /*
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
  */
}


// Start using GPU resources. Training is over. Today the real work begins. Go with Dog.
void MemoryPlan::beBlessed()
{
  allocateStagingMemory();
}


constexpr int getFormatSortValue(vk::Format format)
{
  switch (format)
  {
  case vk::Format::eR4G4UnormPack8:
  case vk::Format::eR8Unorm:
  case vk::Format::eR8Snorm:
  case vk::Format::eR8Uscaled:
  case vk::Format::eR8Sscaled:
  case vk::Format::eR8Uint:
  case vk::Format::eR8Sint:
  case vk::Format::eR8Srgb:
    return __COUNTER__;

  case vk::Format::eR4G4B4A4UnormPack16:
  case vk::Format::eB4G4R4A4UnormPack16:
  case vk::Format::eR5G6B5UnormPack16:
  case vk::Format::eB5G6R5UnormPack16:
  case vk::Format::eR5G5B5A1UnormPack16:
  case vk::Format::eB5G5R5A1UnormPack16:
  case vk::Format::eA1R5G5B5UnormPack16:
  case vk::Format::eR8G8Unorm:
  case vk::Format::eR8G8Snorm:
  case vk::Format::eR8G8Uscaled:
  case vk::Format::eR8G8Sscaled:
  case vk::Format::eR8G8Uint:
  case vk::Format::eR8G8Sint:
  case vk::Format::eR8G8Srgb:
  case vk::Format::eR16Unorm:
  case vk::Format::eR16Snorm:
  case vk::Format::eR16Uscaled:
  case vk::Format::eR16Sscaled:
  case vk::Format::eR16Uint:
  case vk::Format::eR16Sint:
  case vk::Format::eR16Sfloat:
    return __COUNTER__;

  case vk::Format::eR8G8B8Unorm:
  case vk::Format::eR8G8B8Snorm:
  case vk::Format::eR8G8B8Uscaled:
  case vk::Format::eR8G8B8Sscaled:
  case vk::Format::eR8G8B8Uint:
  case vk::Format::eR8G8B8Sint:
  case vk::Format::eR8G8B8Srgb:
  case vk::Format::eB8G8R8Unorm:
  case vk::Format::eB8G8R8Snorm:
  case vk::Format::eB8G8R8Uscaled:
  case vk::Format::eB8G8R8Sscaled:
  case vk::Format::eB8G8R8Uint:
  case vk::Format::eB8G8R8Sint:
  case vk::Format::eB8G8R8Srgb:
    return __COUNTER__;

  case vk::Format::eR8G8B8A8Unorm:
  case vk::Format::eR8G8B8A8Snorm:
  case vk::Format::eR8G8B8A8Uscaled:
  case vk::Format::eR8G8B8A8Sscaled:
  case vk::Format::eR8G8B8A8Uint:
  case vk::Format::eR8G8B8A8Sint:
  case vk::Format::eR8G8B8A8Srgb:
  case vk::Format::eB8G8R8A8Unorm:
  case vk::Format::eB8G8R8A8Snorm:
  case vk::Format::eB8G8R8A8Uscaled:
  case vk::Format::eB8G8R8A8Sscaled:
  case vk::Format::eB8G8R8A8Uint:
  case vk::Format::eB8G8R8A8Sint:
  case vk::Format::eB8G8R8A8Srgb:
  case vk::Format::eA8B8G8R8UnormPack32:
  case vk::Format::eA8B8G8R8SnormPack32:
  case vk::Format::eA8B8G8R8UscaledPack32:
  case vk::Format::eA8B8G8R8SscaledPack32:
  case vk::Format::eA8B8G8R8UintPack32:
  case vk::Format::eA8B8G8R8SintPack32:
  case vk::Format::eA8B8G8R8SrgbPack32:
  case vk::Format::eA2R10G10B10UnormPack32:
  case vk::Format::eA2R10G10B10SnormPack32:
  case vk::Format::eA2R10G10B10UscaledPack32:
  case vk::Format::eA2R10G10B10SscaledPack32:
  case vk::Format::eA2R10G10B10UintPack32:
  case vk::Format::eA2R10G10B10SintPack32:
  case vk::Format::eA2B10G10R10UnormPack32:
  case vk::Format::eA2B10G10R10SnormPack32:
  case vk::Format::eA2B10G10R10UscaledPack32:
  case vk::Format::eA2B10G10R10SscaledPack32:
  case vk::Format::eA2B10G10R10UintPack32:
  case vk::Format::eA2B10G10R10SintPack32:
  case vk::Format::eR16G16Unorm:
  case vk::Format::eR16G16Snorm:
  case vk::Format::eR16G16Uscaled:
  case vk::Format::eR16G16Sscaled:
  case vk::Format::eR16G16Uint:
  case vk::Format::eR16G16Sint:
  case vk::Format::eR16G16Sfloat:
  case vk::Format::eR32Uint:
  case vk::Format::eR32Sint:
  case vk::Format::eR32Sfloat:
  case vk::Format::eB10G11R11UfloatPack32:
  case vk::Format::eE5B9G9R9UfloatPack32:
    return __COUNTER__;

  case vk::Format::eR16G16B16Unorm:
  case vk::Format::eR16G16B16Snorm:
  case vk::Format::eR16G16B16Uscaled:
  case vk::Format::eR16G16B16Sscaled:
  case vk::Format::eR16G16B16Uint:
  case vk::Format::eR16G16B16Sint:
  case vk::Format::eR16G16B16Sfloat:
    return __COUNTER__;

  case vk::Format::eR16G16B16A16Unorm:
  case vk::Format::eR16G16B16A16Snorm:
  case vk::Format::eR16G16B16A16Uscaled:
  case vk::Format::eR16G16B16A16Sscaled:
  case vk::Format::eR16G16B16A16Uint:
  case vk::Format::eR16G16B16A16Sint:
  case vk::Format::eR16G16B16A16Sfloat:
  case vk::Format::eR32G32Uint:
  case vk::Format::eR32G32Sint:
  case vk::Format::eR32G32Sfloat:
  case vk::Format::eR64Uint:
  case vk::Format::eR64Sint:
  case vk::Format::eR64Sfloat:
    return __COUNTER__;

  case vk::Format::eR32G32B32Uint:
  case vk::Format::eR32G32B32Sint:
  case vk::Format::eR32G32B32Sfloat:
    return __COUNTER__;

  case vk::Format::eR32G32B32A32Uint:
  case vk::Format::eR32G32B32A32Sint:
  case vk::Format::eR32G32B32A32Sfloat:
  case vk::Format::eR64G64Uint:
  case vk::Format::eR64G64Sint:
  case vk::Format::eR64G64Sfloat:
    return __COUNTER__;

  case vk::Format::eR64G64B64Uint:
  case vk::Format::eR64G64B64Sint:
  case vk::Format::eR64G64B64Sfloat:
    return __COUNTER__;

  case vk::Format::eR64G64B64A64Uint:
  case vk::Format::eR64G64B64A64Sint:
  case vk::Format::eR64G64B64A64Sfloat:
    return __COUNTER__;

  case vk::Format::eBc1RgbUnormBlock:
  case vk::Format::eBc1RgbSrgbBlock:
    return __COUNTER__;

  case vk::Format::eBc1RgbaUnormBlock:
  case vk::Format::eBc1RgbaSrgbBlock:
    return __COUNTER__;

  case vk::Format::eBc2UnormBlock:
  case vk::Format::eBc2SrgbBlock:
    return __COUNTER__;

  case vk::Format::eBc3UnormBlock:
  case vk::Format::eBc3SrgbBlock:
    return __COUNTER__;

  case vk::Format::eBc4UnormBlock:
  case vk::Format::eBc4SnormBlock:
    return __COUNTER__;

  case vk::Format::eBc5UnormBlock:
  case vk::Format::eBc5SnormBlock:
    return __COUNTER__;

  case vk::Format::eBc6HUfloatBlock:
  case vk::Format::eBc6HSfloatBlock:
    return __COUNTER__;

  case vk::Format::eBc7UnormBlock:
  case vk::Format::eBc7SrgbBlock:
    return __COUNTER__;

  case vk::Format::eEtc2R8G8B8UnormBlock:
  case vk::Format::eEtc2R8G8B8SrgbBlock:
    return __COUNTER__;

  case vk::Format::eEtc2R8G8B8A1UnormBlock:
  case vk::Format::eEtc2R8G8B8A1SrgbBlock:
    return __COUNTER__;

  case vk::Format::eEtc2R8G8B8A8UnormBlock:
  case vk::Format::eEtc2R8G8B8A8SrgbBlock:
    return __COUNTER__;

  case vk::Format::eEacR11UnormBlock:
  case vk::Format::eEacR11SnormBlock:
    return __COUNTER__;

  case vk::Format::eEacR11G11UnormBlock:
  case vk::Format::eEacR11G11SnormBlock:
    return __COUNTER__;

  case vk::Format::eAstc4x4UnormBlock:
  case vk::Format::eAstc4x4SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc5x4UnormBlock:
  case vk::Format::eAstc5x4SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc5x5UnormBlock:
  case vk::Format::eAstc5x5SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc6x5UnormBlock:
  case vk::Format::eAstc6x5SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc6x6UnormBlock:
  case vk::Format::eAstc6x6SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc8x5UnormBlock:
  case vk::Format::eAstc8x5SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc8x6UnormBlock:
  case vk::Format::eAstc8x6SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc8x8UnormBlock:
  case vk::Format::eAstc8x8SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc10x5UnormBlock:
  case vk::Format::eAstc10x5SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc10x6UnormBlock:
  case vk::Format::eAstc10x6SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc10x8UnormBlock:
  case vk::Format::eAstc10x8SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc10x10UnormBlock:
  case vk::Format::eAstc10x10SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc12x10UnormBlock:
  case vk::Format::eAstc12x10SrgbBlock:
    return __COUNTER__;

  case vk::Format::eAstc12x12UnormBlock:
  case vk::Format::eAstc12x12SrgbBlock:
    return __COUNTER__;

  case vk::Format::eD16Unorm:
    return __COUNTER__;

  case vk::Format::eX8D24UnormPack32:
    return __COUNTER__;

  case vk::Format::eD32Sfloat:
    return __COUNTER__;

  case vk::Format::eS8Uint:
    return __COUNTER__;

  case vk::Format::eD16UnormS8Uint:
    return __COUNTER__;

  case vk::Format::eD24UnormS8Uint:
    return __COUNTER__;

  case vk::Format::eD32SfloatS8Uint:
    return __COUNTER__;
  }
}


struct FeatureResource
{
  Asset * assetPtr;
  std::string_view usageType;
  std::variant<vk::ImageCreateFlagBits, vk::BufferCreateFlagBits> createFlags; 
  std::variant<vk::ImageUsageFlagBits, vk::BufferUsageFlagBits> usageFlags;
  std::vector<int32_t> sortedQueueFamilyIndices;
};

bool canShareAResourceObject(FeatureResource const & a, FeatureResource const & b)
{
  if (a.assetPtr->isImage() != b.assetPtr->isImage())
    { return false; }

  // compare creation and usage flags
  if (a.createFlags != b.createFlags)
    { return false; }

  // compare qfi's
  if (a.sortedQueueFamilyIndices != b.sortedQueueFamilyIndices)
    { return false; }

  // comparing images
  if (a.assetPtr->isImage())
  {
    Image * ia = dynamic_cast<Image *>(a.assetPtr);
    Image * ib = dynamic_cast<Image *>(b.assetPtr);

    // compare extents
    auto const & ad = ia->getExtents();
    auto const & bd = ib->getExtents();
    if (ad[0] != bd[0])
      { return false; }
    if (ad[1] != bd[1])
      { return false; }
    if (ad[2] != bd[2])
      { return false; }
    
    // compare mip levels
    auto const & am = ia->getNumMipLevels();
    auto const & bm = ib->getNumMipLevels();
    if (am != bm)
      { return false; }

    // compare formats
    auto const & af = getFormatSortValue(ia->getFormat());
    auto const & bf = getFormatSortValue(ib->getFormat());
    if (af != bf)
      { return false; }

    return true;
  }
  else  // comparing buffers -- they can always share a vk::Buffer if they have the same create/usage/etc
  {
    return true;
  }
}

bool operator <(FeatureResource & a, FeatureResource & b)
{
  // compare on image / buffer
  if (a.assetPtr->isImage() == true  && b.assetPtr->isImage() == false)
    { return true; }
  if (a.assetPtr->isImage() == false && b.assetPtr->isImage() == true )
    { return false; }

  // compare creation and usage flags
  if (a.createFlags != b.createFlags)
    { return a.createFlags < b.createFlags; }
  if (a.usageFlags != b.usageFlags)
    { return a.createFlags < b.createFlags; }

  // compare qfi's
  if (a.sortedQueueFamilyIndices != b.sortedQueueFamilyIndices)
  {
    if (a.sortedQueueFamilyIndices.size() != b.sortedQueueFamilyIndices.size())
      { return a.sortedQueueFamilyIndices.size() < b.sortedQueueFamilyIndices.size(); }
    for (size_t i = a.sortedQueueFamilyIndices.size(); i < a.sortedQueueFamilyIndices.size(); ++i)
    {
      if (a.sortedQueueFamilyIndices[i] != b.sortedQueueFamilyIndices[i])
        { return a.sortedQueueFamilyIndices[i] != b.sortedQueueFamilyIndices[i]; }
    }
  }

  // comparing images
  if (a.assetPtr->isImage())
  {
    Image * ia = dynamic_cast<Image *>(a.assetPtr);
    Image * ib = dynamic_cast<Image *>(b.assetPtr);

    // compare extents
    auto const & ad = ia->getExtents();
    auto const & bd = ib->getExtents();
    if (ad[0] != bd[0])
      { return ad[0] < bd[0]; }
    if (ad[1] != bd[1])
      { return ad[1] < bd[1]; }
    if (ad[2] != bd[2])
      { return ad[2] < bd[2]; }
    
    // compare mip levels
    auto const & am = ia->getNumMipLevels();
    auto const & bm = ib->getNumMipLevels();
    if (am != bm)
      { return am < bm; }

    // compare formats
    auto const & af = getFormatSortValue(ia->getFormat());
    auto const & bf = getFormatSortValue(ib->getFormat());
    if (af != bf)
      { return af < bf; }

    return & ia->getName() < & ib->getName(); // just something quick and guaranteed consistent
  }
  else  // comparing buffers
  {
    return & a.assetPtr->getName() < & b.assetPtr->getName(); // just something quick and guaranteed consistent
  }
}


// This is called by Feature instances passing 'this'. Some usage info may come from them, but hmmm.
void MemoryPlan::addObjects(Feature * feature, bool priority)
{
  // let's get all the asset objs
  //vector<Asset *> assetPtrs;
  vector<FeatureResource> featureResources;
  feature->forEachGraphicsSubresourceNeeded([&](
    Asset * asset, std::string_view usageType, // usageType probably goes away 
    variant<vk::ImageCreateFlagBits, vk::BufferCreateFlagBits> createFlags, 
    variant<vk::ImageUsageFlagBits, vk::BufferUsageFlagBits> usageFlags,
    vector<int32_t> && sortedQueueFamilyIndices)
  {
    auto mut = memoryUsageTypes[usageType];
    // We have to check each memory type for the asset. For small projects, this is probably one or two.
    for (size_t memTypeIdx = 0; memTypeIdx < mut->memoryTypeIdxs.size(); ++memTypeIdx)
    {
      MemoryType & mt = memoryTypes[mut->memoryTypeIdxs[memTypeIdx]];
      if (mt.allocs.size() == 0)
        { continue; }
      
      // If asset is alredy where it should be, just addref it.
      if (auto it = mut->assetAllocMap.find((string)asset->getName());
        it != mut->assetAllocMap.end())
      {
        AllocAddress const & aa = it->second;
        mt.allocs[aa.memoryAllocIdx].resources[aa.resourceIdx].subresources[aa.subresourceIdx].refCount += 1;
        return;
      }
    }

//    assetPtrs.push_back(asset);
    featureResources.emplace_back(asset, usageType, createFlags, usageFlags, move(sortedQueueFamilyIndices) );
  });

  // sort assetPtrs into groupable subresources for vkBuffers or vkImages. Try to combine images into an image array, but note that formats and sizes and such must be compatible.
  std::sort(featureResources.begin(), featureResources.end());

  // Determine the subresource packing. Optimize packing for compatible dims|mipLevels|formats.
  size_t imgPackBegin = 0;
  size_t imgPackEnd = 0; // one past the last, like std::end()
  size_t bufPackBegin = 0;
  size_t bufPackEnd = 0; // "
  vector<size_t> resourceGroups;
  resourceGroups.reserve(featureResources.size());  // at worst, one each

  if (featureResources.size() > 0)
  {
    resourceGroups.emplace_back(1);
    for (size_t i = 1; i < featureResources.size(); ++i)
    {
      auto & a = featureResources[i - 1];
      auto & b = featureResources[i];

      if (canShareAResourceObject(a, b))
        { resourceGroups.back() += 1; }
      else
        { resourceGroups.push_back(1); }
    }
  }

  auto pdev = graphics->getPhysicalDevice();
  auto dev = graphics->getDevice();

  // Now make the ROs
  if (resourceGroups.size() > 0)
  {
    Resource resource;
    size_t firstIdx = 0;

    for (auto & resourceGroupSize : resourceGroups)
    {
      auto & featureResource = featureResources[firstIdx];
      if (featureResource.assetPtr->isImage())
      {
        Image * firstImage = dynamic_cast<Image *>(featureResource.assetPtr);

        auto extents = firstImage->getExtents();
        vk::ImageType vkImageType = vk::ImageType::e3D;
        if (extents[2] == 1)
          { vkImageType = vk::ImageType::e2D; }
        if (extents[1] == 1)
          { vkImageType = vk::ImageType::e1D; }

        // create the vkImage
        auto createFlags = std::get<vk::ImageCreateFlagBits>(featureResource.createFlags);
        if (resourceGroupSize > 1)
          { createFlags |= vk::ImageCreateFlagBits::eMutableFormat; }

        auto vkImage = dev.createImage( vk::ImageCreateInfo {
          createFlags, 
          vkImageType,
          firstImage->getFormat(),
          vk::Extent3D(extents[0], extents[1], extents[2]),
          (uint32_t) firstImage->getNumMipLevels(),
          (uint32_t) resourceGroupSize,
          vk::SampleCountFlagBits::e1, // TODO: Support msaa
          vk::ImageTiling::eOptimal,
          std::get<vk::ImageUsageFlagBits>(featureResource.usageFlags),
          vk::SharingMode::eExclusive,  // TODO: resource sharing!
          (uint32_t) featureResource.sortedQueueFamilyIndices.size(),
          reinterpret_cast<uint32_t const *> (featureResource.sortedQueueFamilyIndices.data()),
          vk::ImageLayout::eTransferDstOptimal  // Images are always staged, even if they're in host-visible ram
        });

        // get the memory alloc, size, alignment for the image
        auto reqs = dev.getImageMemoryRequirements(vkImage);

        // make the Resource object
        auto & ogResource = allocateResource(vkImage, reqs);

        // make the Subresource objects
        for (size_t i = firstIdx; i < firstIdx + resourceGroupSize; ++i)
        {
          auto & featureSubResource = featureResources[i];
          Image * image = dynamic_cast<Image *>(featureSubResource.assetPtr);
          auto imageView = dev.createImageView(
            vk::ImageViewCreateInfo {
              vk::ImageViewCreateFlags(), 
              vkImage, 
              vkImageType, 
              image->getFormat(), 
              image->getComponentMapping(), 
              vk::ImageSubresourceRange {
                vk::ImageAspectFlagBits::eColor,
                (uint32_t) 0, 
                (uint32_t) VK_REMAINING_MIP_LEVELS, 
                (uint32_t) i - firstIdx, 
                (uint32_t) 1 } } );

          // make the Subresource object
          registerSubresource(ogResource, imageView);
        }

      }
      else
      {
        // get total memory size of all sub-buffers

        auto vkBuffer = dev.createBuffer( vk::BufferCreateInfo {
          std::get<vk::BufferCreateFlagBits>(featureResource.createFlags), 
          (vk::DeviceSize) featureResource.assetPtr->getDataSize(),
          std::get<vk::BufferUsageFlagBits>(featureResource.usageFlags), 
          vk::SharingMode::eExclusive,
          (uint32_t) featureResource.sortedQueueFamilyIndices.size(),
          (uint32_t const *) featureResource.sortedQueueFamilyIndices.data()
        });

        // get the memory alloc, size, alignment for the image
        auto reqs = dev.getBufferMemoryRequirements(vkBuffer);

        // make the Resource object
        auto & ogResource = allocateResource(vkBuffer, reqs);

        // make the Subresource objects
        size_t offset = 0;
        for (size_t i = firstIdx; i < firstIdx + resourceGroupSize; ++i)
        {
          auto & featureSubResource = featureResources[i];
          Asset * asset = featureSubResource.assetPtr;
          size_t dataSize = asset->getDataSize();
          auto bufferView = dev.createBufferView( vk::BufferViewCreateInfo {
            vk::BufferViewCreateFlags(), vkBuffer, featureSubResource.assetPtr->getFormat(), offset, dataSize
          });

          // make the Subresource object
          registerSubresource(ogResource, bufferView);

          offset += asset->getDataSize();
          offset = padTo(offset, cacheLineSizeConstructive);
        }
      }

      firstIdx += resourceGroupSize;
    }
  }

  /*

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
        // TODO: == or &= ?
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

    // make the images out of the packed assets
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
  */
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


Resource & MemoryPlan::allocateResource(std::variant<vk::Buffer, vk::Image> resourceObject, vk::MemoryRequirements const & reqs)
{
  // get best memoryType
  int32_t memoryType = -1;
  for (size_t i = 0; i < memoryTypes.size(); ++i)
  {
    if ((reqs.memoryTypeBits & (1 << i)))
    {
      // if we have room

      // else if we alloc more

      // else continue to next memory type
    }
  }
}


void MemoryPlan::registerSubresource(Resource & ogResource, std::variant<vk::BufferView, vk::ImageView> subresourceView)
{

}
