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
          { typeIdx, combinedProps, mt.chunkSize } );
        break;
      }
    }
  }
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

    // compare image view types
    auto ivta = ia->getImageViewType();
    auto ivtb = ib->getImageViewType();

    if (((ivta == vk::ImageViewType::e1D || 
          ivta == vk::ImageViewType::e1DArray) && 
         (ivtb != vk::ImageViewType::e1D && 
          ivtb != vk::ImageViewType::e1DArray)))
      { return true; }

    if (((ivtb == vk::ImageViewType::e1D || 
          ivtb == vk::ImageViewType::e1DArray) && 
         (ivta != vk::ImageViewType::e1D && 
          ivta != vk::ImageViewType::e1DArray)))
      { return false; }

    if (((ivta == vk::ImageViewType::e3D) && 
         (ivtb != vk::ImageViewType::e3D)))
      { return false; }

    if (((ivtb == vk::ImageViewType::e3D) && 
         (ivta != vk::ImageViewType::e3D)))
      { return true; }

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


// This is called by Feature instances passing 'this'.
void MemoryPlan::addResources(Feature * feature, bool priority)
{
  // let's get all the asset objs
  //vector<Asset *> assetPtrs;
  vector<FeatureResource> featureResources;
  feature->forEachGraphicsSubresourceNeeded([&](
    Asset * asset, 
    variant<vk::ImageCreateFlagBits, vk::BufferCreateFlagBits> createFlags, 
    variant<vk::ImageUsageFlagBits, vk::BufferUsageFlagBits> usageFlags,
    vector<int32_t> && sortedQueueFamilyIndices)
  {
    if (auto it = assetAllocMap.find(string(asset->getName()));
        it != assetAllocMap.end())
    {
      AllocAddress & aa = it->second;
      auto subresource = getSubresource(aa);
      if (subresource.has_value())
      {
        subresource->refCount += 1;
        return;
      }
    }

    featureResources.emplace_back(asset, createFlags, usageFlags, move(sortedQueueFamilyIndices) );
  });

  // sort assetPtrs into groupable subresources for vkBuffers or vkImages. Try to combine images into an image array, but note that formats and sizes and such must be compatible.
  std::sort(featureResources.begin(), featureResources.end());

  // Determine the subresource packing. Optimize packing for compatible dims|mipLevels|formats.
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

        vk::ImageType vkImageType;
        switch (firstImage->getImageViewType())
        {
        case vk::ImageViewType::e1D:
        case vk::ImageViewType::e1DArray:
          vkImageType = vk::ImageType::e1D;
          break;
        case vk::ImageViewType::e3D:
          vkImageType = vk::ImageType::e3D;
        default: 
          vkImageType = vk::ImageType::e2D;
        }
        
        auto extents = firstImage->getExtents();

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
        auto ogResource = allocateResource(vkImage, reqs);
        if (ogResource.has_value())
        {
          // make the Subresource objects
          size_t layer = 0;
          for (size_t i = firstIdx; i < firstIdx + resourceGroupSize; ++i)
          {
            auto & featureSubResource = featureResources[i];
            Image * image = dynamic_cast<Image *>(featureSubResource.assetPtr);
            vk::ImageViewType vkImageViewType = image->getImageViewType();
            size_t numLayers = image->getNumLayers();
            
            auto imageView = dev.createImageView(
              vk::ImageViewCreateInfo {
                vk::ImageViewCreateFlags(), 
                vkImage, 
                vkImageViewType, 
                image->getFormat(), 
                image->getComponentMapping(), 
                vk::ImageSubresourceRange {
                  vk::ImageAspectFlagBits::eColor,
                  (uint32_t) 0, 
                  (uint32_t) VK_REMAINING_MIP_LEVELS, 
                  (uint32_t) layer, 
                  (uint32_t) numLayers }}); // TODO: Is this correct vis a vis cubemaps and cubemap arrays?

            // make the Subresource object
            registerSubresource(*ogResource, imageView, image->getName());

            layer += numLayers;
          }
        }
        else
        {
          // Unlikely to ever; unless we run out of host RAM
          log(thId, logTags::err, fmt::format("Could not allocate device memory for {}.", featureResource.assetPtr->getName()));
          dev.destroyImage(vkImage);
          feature->error();
        }
      }
      else
      {
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
        auto ogResource = allocateResource(vkBuffer, reqs);
        if (ogResource.has_value())
        {
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
            registerSubresource(*ogResource, bufferView, asset->getName());

            offset += asset->getDataSize();
            offset = padTo(offset, cacheLineSizeConstructive);
          }
        }
        else
        {
          // Unlikely to ever; unless we run out of host RAM
          log(thId, logTags::err, fmt::format("Could not allocate device memory for {}.", featureResource.assetPtr->getName()));
          dev.destroyBuffer(vkBuffer);
          feature->error();
        }
      }

      firstIdx += resourceGroupSize;
    }
  }
}


void MemoryPlan::reprioritizeResources(Feature * feature, bool priority)
{

}


void MemoryPlan::removeResources(Feature * feature)
{

}


void MemoryPlan::moop()
{

}


optional<Subresource &> MemoryPlan::getSubresource(AllocAddress const & address)
{
  if (address.memoryTypeIdx < memoryTypes.size())
  {
    auto & mt = memoryTypes[address.memoryAllocIdx];
    if (address.memoryAllocIdx < mt.allocs.size())
    {
      auto & alloc = mt.allocs[address.memoryAllocIdx];
      if (address.resourceIdx < alloc.resources.size())
      {
        auto & res = alloc.resources[address.resourceIdx];
        if (address.subresourceIdx < res.subresources.size())
          { return res.subresources[address.subresourceIdx]; }
      }
    }
  }

  return {};
}


void MemoryPlan::allocateStagingMemory()
{
  auto dev = graphics->getDevice();

  for (size_t mtIdx = 0; mtIdx < memoryTypes.size(); ++mtIdx)
  {
    auto & mt = memoryTypes[mtIdx];
    if ((mt.memoryProps & 
        (vk::MemoryPropertyFlagBits::eHostVisible | 
         vk::MemoryPropertyFlagBits::eHostCoherent)) == 
        (vk::MemoryPropertyFlagBits) 0)
      { continue; }

    size_t allocSize = stagingSize;
    for (size_t attemptIdx = 0; attemptIdx < numAllocRetries; ++attemptIdx)
    {
      auto allocResult = graphics->getDevice().allocateMemory(
        vk::MemoryAllocateInfo { mt.allocChunkSize, mtIdx });
      if (! allocResult)
      {
        // Not enough room to allocate a new block. That's okay; move on to the next block size or memory type.
        log(thId, logTags::warn, fmt::format("Failed allocateMemory() size {}, type index {}, attempt {}. Falling back.", allocSize, mtIdx, attemptIdx));
        allocSize /= 2;
      }
      else
      {
        log(thId, logTags::info, fmt::format("allocateMemory() size {}, type index {}, attempt {}.", allocSize, mtIdx, attemptIdx));
        stagingAlloc = allocResult;
        stagingSize = allocSize;

        // Map it and keep it mapped.
        if (dev.mapMemory(allocResult, 0, stagingSize, vk::MemoryMapFlags(), 
          & mappedStagingMemory) != vk::Result::eSuccess)
          { log(thId, logTags::err, "mapMemory() failed to map staging buffer."); }

        return;
      }
    }
  }

  log(thId, logTags::err, "Could not find suitable heap for staging buffer.");
  return;
}


optional<Resource &> MemoryPlan::allocateResource(
  std::variant<vk::Buffer, vk::Image> resourceObject, 
  vk::MemoryRequirements const & reqs)
{
  // get best memoryType
  int32_t memoryTypeIdx = -1;
  for (size_t i = 0; i < memoryTypes.size(); ++i)
  {
    if (reqs.memoryTypeBits & (1 << i))
    {
      auto & memoryType = memoryTypes[i];

      // if we have room in this heap
      auto resource = memoryType.allocateResource(resourceObject, reqs);
      if (resource.has_value())
        { return *resource; }
    }
  }

  return {};
}


void MemoryPlan::registerSubresource(Resource & ogResource, subresourceVariant subresourceView, string_view subresourceName, size_t offset, size_t size)
{
  ogResource.subresources.emplace_back(Subresource {
    subresourceView, string(subresourceName), offset, size });  
}


size_t MemoryAlloc::getNextImageOffset(size_t imageAlignment)
{
  if (resources.size() == 0)
    { return 0; }

  bool prevIsImage = holds_alternative<vk::Image>(
    resources.back().vulkanResource);

  if (prevIsImage == false)
  {
    size_t big = 
      graphics->getPhysicalDeviceLimits().bufferImageGranularity;
    return padTo(usedSize, max(imageAlignment, big));
  }
  else
    { return padTo(usedSize, imageAlignment); }
}


size_t MemoryAlloc::getNextBufferOffset(size_t bufferAlignment)
{
  if (resources.size() == 0)
    { return 0; }

  bool prevIsImage = holds_alternative<vk::Image>(
    resources.back().vulkanResource);

  if (prevIsImage == true)
  {
    size_t big = 
      graphics->getPhysicalDeviceLimits().bufferImageGranularity;
    return padTo(usedSize, max(bufferAlignment, big));
  }
  else
    { return padTo(usedSize, bufferAlignment); }
}


size_t MemoryAlloc::getFreeImageSize(size_t imageAlignment)
{
  return size - getNextBufferOffset(imageAlignment) - 
    graphics->getPhysicalDeviceLimits().bufferImageGranularity;
}


size_t MemoryAlloc::getFreeBufferSize(size_t bufferAlignment)
{
  return size - getNextBufferOffset(bufferAlignment) - 
    graphics->getPhysicalDeviceLimits().bufferImageGranularity;
}


optional<Resource &> MemoryType::allocateResource(std::variant<vk::Buffer, vk::Image> resourceObject, vk::MemoryRequirements const & reqs)
{
  optional<Resource &> res;
  auto const & pdls = graphics->getPhysicalDeviceLimits();

  bool lastTypeIsImage = false;
  bool resourceTypeIsImage = holds_alternative<vk::Image>(resourceObject);

  // Search existing allocs for enough free space. We check for available space including the bufferImageGranularity, in case the adjacent allocation begins with an object of the other kind.
  for (auto it = allocs.rbegin(); it != allocs.rend(); ++it)
  {
    auto alloc = *it;
    if (resourceTypeIsImage)
    {
      if (alloc.getFreeImageSize(reqs.alignment) >= padTo(reqs.size, max(pdls.bufferImageGranularity, reqs.alignment)))
      {
        res.emplace(alloc.resources.emplace_back(Resource {
          resourceObject,
          alloc.getNextImageOffset(reqs.alignment),
          reqs.size, 
          {}, true }));
        break;
      }
    }
    else
    {
      if (alloc.getFreeBufferSize(reqs.alignment) >= padTo(reqs.size, max(pdls.bufferImageGranularity, reqs.alignment)))
      {
        res.emplace(alloc.resources.emplace_back(Resource {
          resourceObject,
          alloc.getNextBufferOffset(reqs.alignment),
          reqs.size, 
          {}, true }));
        break;
      }
    }
  }

  // No current allocs have room. No big surprise. Make a new alloc if we can, trying halves until we succeed or we're less than the resource size + granularity padding.

  auto dev = graphics->getDevice();

  size_t allocSize = allocChunkSize;
  size_t attemptIdx = 0;
  while (res.has_value() == false)
  {
    auto alloc = graphics->getDevice().allocateMemory(
      vk::MemoryAllocateInfo { allocSize, memoryTypeIdx });
    if (! alloc)
    {
      // Not enough room to allocate a new block. That's okay; move on to the next block size.
      log(thId, logTags::warn, fmt::format("Failed allocateMemory() size {}, type index {}, attempt {}. Falling back.", allocSize, memoryTypeIdx, attemptIdx));

      // Halve the value for trying again. If we can't allocate enough for the resource, this heap is full. We'll fall back to a different heap in the caller.
      allocSize /= 2;
      if (allocSize < padTo(reqs.size, max(pdls.bufferImageGranularity, reqs.alignment)))
        { break; }
    }
    else
    {
      log(thId, logTags::info, fmt::format("allocateMemory() size {}, type index {}, attempt {}.", allocSize, memoryTypeIdx, attemptIdx));

      allocs.emplace_back(MemoryAlloc {
        allocSize, reqs.size, alloc, { Resource {
          resourceObject,
          0,
          reqs.size, 
          {}, true
        }}
      });
    }
  }
  
  return res;   // May not have a value, if the heap is full.
}
