#include <cassert>
#include "configData.h"
#include "utils.h"
#include "config-gen.h"

using namespace std;
using namespace overground;
using namespace humon;


void ConfigData::loadFromHumon(HuNode const & src)
{
  logFn();

  importPod(src, config);
}

template <class T>
ConfigData::Deltas set(T & lhs, T const & rhs, ConfigData::Deltas kind)
{
  if (lhs != rhs)
  {
    lhs = rhs;
    return kind;
  }
  return ConfigData::Deltas::None;
}

void ConfigData::integrate(ConfigData const & rhs)
{
  ConfigData::Deltas deltas = ConfigData::Deltas::None;

  deltas |= set(config.general.programName, rhs.config.general.programName, ConfigData::Deltas::Window);

  deltas |= set(config.general.version, rhs.config.general.version, ConfigData::Deltas::None);
  
  deltas |= set(config.general.numWorkerThreads, rhs.config.general.numWorkerThreads, ConfigData::Deltas::JobManagement);

  deltas |= set(config.graphics.isConfigured, rhs.config.graphics.isConfigured, ConfigData::Deltas::VulkanInstance);

  deltas |= set(config.graphics.headless, rhs.config.graphics.headless, ConfigData::Deltas::Window | ConfigData::Deltas::VulkanInstance);
  
  deltas |= set(config.graphics.fullScreen, rhs.config.graphics.fullScreen, ConfigData::Deltas::Window);
  
  deltas |= set(config.graphics.width, rhs.config.graphics.width, ConfigData::Deltas::WindowExtents);
  
  deltas |= set(config.graphics.height, rhs.config.graphics.height, ConfigData::Deltas::WindowExtents);

  deltas |= set(config.graphics.vulkanValidationEnabled, rhs.config.graphics.vulkanValidationEnabled, ConfigData::Deltas::VulkanInstance);
  
  deltas |= set(config.graphics.vulkanValidationLayers, rhs.config.graphics.vulkanValidationLayers, ConfigData::Deltas::VulkanInstance);

  deltas |= set(config.graphics.vulkanValidationReports, rhs.config.graphics.vulkanValidationReports, ConfigData::Deltas::VulkanInstance);

  deltas |= set(config.graphics.vulkanExtensions, rhs.config.graphics.vulkanExtensions, ConfigData::Deltas::VulkanInstance);

  deltas |= set(config.graphics.deviceExtensions, rhs.config.graphics.deviceExtensions, ConfigData::Deltas::VulkanInstance);

  deltas |= set(config.graphics.minGraphicsQueues, rhs.config.graphics.minGraphicsQueues, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(config.graphics.desiredGraphicsQueues, rhs.config.graphics.desiredGraphicsQueues, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(config.graphics.minComputeQueues, rhs.config.graphics.minComputeQueues, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(config.graphics.desiredComputeQueues, rhs.config.graphics.desiredComputeQueues, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(config.graphics.minTransferQueues, rhs.config.graphics.minTransferQueues, ConfigData::Deltas::PhysicalDevice);
  
  deltas |= set(config.graphics.desiredTransferQueues, rhs.config.graphics.desiredTransferQueues, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(config.graphics.minDeviceFeatures, rhs.config.graphics.minDeviceFeatures, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(config.graphics.desiredDeviceFeatures, rhs.config.graphics.desiredDeviceFeatures, ConfigData::Deltas::LogicalDevice);

  deltas |= set(config.graphics.swapchain.formatPriorities, rhs.config.graphics.swapchain.formatPriorities, ConfigData::Deltas::Swapchain);

  deltas |= set(config.graphics.swapchain.numViews, rhs.config.graphics.swapchain.numViews, ConfigData::Deltas::Swapchain);

  deltas |= set(config.graphics.swapchain.imageUsages, rhs.config.graphics.swapchain.imageUsages, ConfigData::Deltas::Swapchain);
  
  deltas |= set(config.graphics.swapchain.imageSharing, rhs.config.graphics.swapchain.imageSharing, ConfigData::Deltas::Swapchain);

  deltas |= set(config.graphics.swapchain.pretransform, rhs.config.graphics.swapchain.pretransform, ConfigData::Deltas::Swapchain);
  
  deltas |= set(config.graphics.swapchain.windowAlpha, rhs.config.graphics.swapchain.windowAlpha, ConfigData::Deltas::Swapchain);
  
  deltas |= set(config.graphics.swapchain.presentModePriorities, rhs.config.graphics.swapchain.presentModePriorities, ConfigData::Deltas::Swapchain);
  
  deltas |= set(config.graphics.swapchain.clipped, rhs.config.graphics.swapchain.clipped, ConfigData::Deltas::Swapchain);
  
  deltas |= set(config.graphics.swapchain.imageView.viewType, rhs.config.graphics.swapchain.imageView.viewType, ConfigData::Deltas::Swapchain);

  deltas |= set(config.graphics.swapchain.imageView.components, rhs.config.graphics.swapchain.imageView.components, ConfigData::Deltas::Swapchain);

  deltas |= set(config.graphics.swapchain.imageView.aspectMask, rhs.config.graphics.swapchain.imageView.aspectMask, ConfigData::Deltas::Swapchain);

  deltas |= set(config.graphics.swapchain.imageView.layerCount, rhs.config.graphics.swapchain.imageView.layerCount, ConfigData::Deltas::Swapchain);

  lastDiffs = rhs.lastDiffs | deltas;
}


string ConfigData::print() const
{
  return overground::print(config);
}


std::ostream & overground::operator << (
  std::ostream & stream, ConfigData const & rhs)
{
  stream << rhs.print();
  return stream;
}
