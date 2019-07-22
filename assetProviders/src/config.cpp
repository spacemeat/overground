#include <memory>
#include "config.h"
#include "engine.h"
#include "resourceManager.h"
#include "fileReference.h"
#include "config-gen.h"

using namespace std;
using namespace humon;
using namespace overground;


unique_ptr<Asset> overground::makeConfig(
  ResourceManager * resMan,
  string_view assetName,
  FileReference * assetDescFile, 
  HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor)
{
  return make_unique<Config>(resMan, assetName, 
    assetDescFile, descFromFile, cache, compress, 
    monitor);
}


Config::Config(ResourceManager * resMan,
  std::string_view assetName,
  FileReference * assetDescFile, 
  humon::HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor)
: Asset(resMan, assetName, assetDescFile,
    descFromFile, cache, compress, monitor)
{
  logFn();
}


void Config::compileSrcAsset_impl(path_t const & path)
{
  logFn();

  auto huNode = loadHumonDataFromFile(path);
  importPod(*huNode, data);

  setDidReloadAssetData();
}


void Config::applyToEngine_impl()
{
  logFn();

  clearDidReloadAssetData();

  getResMan()->getEngine()->updateConfig(data);
}


template <class T>
Config::Deltas setIt(T & lhs, T const & rhs, Config::Deltas kind)
{
  if (lhs != rhs)
  {
    lhs = rhs;
    return kind;
  }
  return Config::Deltas::None;
}

Config::Deltas overground::integrate(config_t & lhs, config_t const & rhs)
{
  Config::Deltas deltas = Config::Deltas::None;

  deltas |= setIt(lhs.general.programName, rhs.general.programName, Config::Deltas::Window);

  deltas |= setIt(lhs.general.version, rhs.general.version, Config::Deltas::None);
  
  deltas |= setIt(lhs.general.numWorkerThreads, rhs.general.numWorkerThreads, Config::Deltas::JobManagement);

  deltas |= setIt(lhs.graphics.isConfigured, rhs.graphics.isConfigured, Config::Deltas::VulkanInstance);

  deltas |= setIt(lhs.graphics.headless, rhs.graphics.headless, Config::Deltas::Window | Config::Deltas::VulkanInstance);
  
  deltas |= setIt(lhs.graphics.fullScreen, rhs.graphics.fullScreen, Config::Deltas::Window);
  
  deltas |= setIt(lhs.graphics.width, rhs.graphics.width, Config::Deltas::WindowExtents);
  
  deltas |= setIt(lhs.graphics.height, rhs.graphics.height, Config::Deltas::WindowExtents);

  deltas |= setIt(lhs.graphics.vulkanValidationEnabled, rhs.graphics.vulkanValidationEnabled, Config::Deltas::VulkanInstance);
  
  deltas |= setIt(lhs.graphics.vulkanValidationLayers, rhs.graphics.vulkanValidationLayers, Config::Deltas::VulkanInstance);

  deltas |= setIt(lhs.graphics.vulkanValidationReports, rhs.graphics.vulkanValidationReports, Config::Deltas::VulkanInstance);

  deltas |= setIt(lhs.graphics.vulkanExtensions, rhs.graphics.vulkanExtensions, Config::Deltas::VulkanInstance);

  deltas |= setIt(lhs.graphics.deviceExtensions, rhs.graphics.deviceExtensions, Config::Deltas::VulkanInstance);

  deltas |= setIt(lhs.graphics.minGraphicsQueues, rhs.graphics.minGraphicsQueues, Config::Deltas::PhysicalDevice);

  deltas |= setIt(lhs.graphics.desiredGraphicsQueues, rhs.graphics.desiredGraphicsQueues, Config::Deltas::PhysicalDevice);

  deltas |= setIt(lhs.graphics.minComputeQueues, rhs.graphics.minComputeQueues, Config::Deltas::PhysicalDevice);

  deltas |= setIt(lhs.graphics.desiredComputeQueues, rhs.graphics.desiredComputeQueues, Config::Deltas::PhysicalDevice);

  deltas |= setIt(lhs.graphics.minTransferQueues, rhs.graphics.minTransferQueues, Config::Deltas::PhysicalDevice);
  
  deltas |= setIt(lhs.graphics.desiredTransferQueues, rhs.graphics.desiredTransferQueues, Config::Deltas::PhysicalDevice);

  deltas |= setIt(lhs.graphics.minDeviceFeatures, rhs.graphics.minDeviceFeatures, Config::Deltas::PhysicalDevice);

  deltas |= setIt(lhs.graphics.desiredDeviceFeatures, rhs.graphics.desiredDeviceFeatures, Config::Deltas::LogicalDevice);

  deltas |= setIt(lhs.graphics.swapchain.formatPriorities, rhs.graphics.swapchain.formatPriorities, Config::Deltas::Swapchain);

  deltas |= setIt(lhs.graphics.swapchain.numViews, rhs.graphics.swapchain.numViews, Config::Deltas::Swapchain);

  deltas |= setIt(lhs.graphics.swapchain.imageUsages, rhs.graphics.swapchain.imageUsages, Config::Deltas::Swapchain);
  
  deltas |= setIt(lhs.graphics.swapchain.imageSharing, rhs.graphics.swapchain.imageSharing, Config::Deltas::Swapchain);

  deltas |= setIt(lhs.graphics.swapchain.pretransform, rhs.graphics.swapchain.pretransform, Config::Deltas::Swapchain);
  
  deltas |= setIt(lhs.graphics.swapchain.windowAlpha, rhs.graphics.swapchain.windowAlpha, Config::Deltas::Swapchain);
  
  deltas |= setIt(lhs.graphics.swapchain.presentModePriorities, rhs.graphics.swapchain.presentModePriorities, Config::Deltas::Swapchain);
  
  deltas |= setIt(lhs.graphics.swapchain.clipped, rhs.graphics.swapchain.clipped, Config::Deltas::Swapchain);
  
  deltas |= setIt(lhs.graphics.swapchain.imageView.viewType, rhs.graphics.swapchain.imageView.viewType, Config::Deltas::Swapchain);

  deltas |= setIt(lhs.graphics.swapchain.imageView.components, rhs.graphics.swapchain.imageView.components, Config::Deltas::Swapchain);

  deltas |= setIt(lhs.graphics.swapchain.imageView.aspectMask, rhs.graphics.swapchain.imageView.aspectMask, Config::Deltas::Swapchain);

  deltas |= setIt(lhs.graphics.swapchain.imageView.layerCount, rhs.graphics.swapchain.imageView.layerCount, Config::Deltas::Swapchain);

  return deltas;
}
