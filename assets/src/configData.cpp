#include <cassert>
#include "configData.h"
#include "utils.h"

using namespace std;
using namespace overground;
using namespace humon;


void ConfigData::loadFromHumon(HuNode const & src)
{
  if (src % "general")
  {
    auto & generalSrc = src / "general";
    if (generalSrc % "programName")
    {
      general.programName = string(generalSrc / "programName");
    }

    if (generalSrc % "version")
    {
      auto & ver = generalSrc / "version";
      general.version = { 
        ver / 0,
        ver / 1,
        ver / 2
      };
    }

    if (generalSrc % "numWorkerThreads")
      { general.numWorkerThreads = generalSrc / "numWorkerThreads"; }
  }

  if (src % "graphics")
  {
    graphics.isConfigured = true;

    auto & graphicsSrc = src / "graphics";
    if (graphicsSrc % "headless")
      { graphics.headless = graphicsSrc / "headless"; }

    if (graphicsSrc % "fullScreen")
      { graphics.fullScreen = graphicsSrc / "fullScreen"; }

    if (graphicsSrc % "width")
      { graphics.width = graphicsSrc / "width"; }

    if (graphicsSrc % "height")
      { graphics.height = graphicsSrc / "height"; }
    
    if (graphicsSrc % "vulkanValidationEnabled")
      { graphics.vulkanValidationEnabled = graphicsSrc / "vulkanValidationEnabled"; }

    if (graphicsSrc % "vulkanValidationLayers")
    {
      graphics.vulkanValidationLayers.clear();
      auto & listSrc = graphicsSrc / "vulkanValidationLayers";
      for (size_t i = 0; i < listSrc.size(); ++i)
        { graphics.vulkanValidationLayers.push_back(listSrc / i); }
    }

    if (graphicsSrc % "vulkanValidationReports")
    {
      graphics.vulkanValidationReports.clear();
      auto & listSrc = graphicsSrc / "vulkanValidationReports";
      for (size_t i = 0; i < listSrc.size(); ++i)
        { graphics.vulkanValidationReports.push_back(listSrc / i); }
    }

    if (graphicsSrc % "vulkanExtensions")
    {
      graphics.vulkanExtensions.clear();
      auto & listSrc = graphicsSrc / "vulkanExtensions";
      for (size_t i = 0; i < listSrc.size(); ++i)
        { graphics.vulkanExtensions.push_back(listSrc / i); }
    }

    if (graphicsSrc % "deviceExtensions")
    {
      graphics.deviceExtensions.clear();
      auto & listSrc = graphicsSrc / "deviceExtensions";
      for (size_t i = 0; i < listSrc.size(); ++i)
        { graphics.deviceExtensions.push_back(listSrc / i); }
    }

    if (graphicsSrc % "minGraphicsQueues")
      { graphics.minGraphicsQueues = graphicsSrc / "minGraphicsQueues"; }

    if (graphicsSrc % "desiredGraphicsQueues")
      { graphics.desiredGraphicsQueues = graphicsSrc / 
        "desiredGraphicsQueues"; }

    if (graphicsSrc % "minComputeQueues")
      { graphics.minComputeQueues = graphicsSrc / "minComputeQueues"; }

    if (graphicsSrc % "desiredComputeQueues")
      { graphics.desiredComputeQueues = graphicsSrc / 
        "desiredComputeQueues"; }

    if (graphicsSrc % "minTransferQueues")
      { graphics.minTransferQueues = graphicsSrc / "minTransferQueues"; }

    if (graphicsSrc % "desiredTransferQueues")
      { graphics.desiredTransferQueues = graphicsSrc / 
        "desiredTransferQueues"; }
  
    if (graphicsSrc % "minDeviceFeatures")
    {
      graphics.minDeviceFeatures.clear();
      auto & listSrc = graphicsSrc / "minDeviceFeatures";
      for (size_t i = 0; i < listSrc.size(); ++i)
        { graphics.minDeviceFeatures.push_back(listSrc / i); }
    }

    if (graphicsSrc % "desiredDeviceFeatures")
    {
      graphics.desiredDeviceFeatures.clear();
      auto & listSrc = graphicsSrc / "desiredDeviceFeatures";
      for (size_t i = 0; i < listSrc.size(); ++i)
        { graphics.desiredDeviceFeatures.push_back(listSrc / i); }
    }

    if (graphics.headless == false &&
        graphicsSrc % "swapchain")
    {
      auto & swapchainSrc = graphicsSrc / "swapchain";
      if (swapchainSrc % "formatPriorities")
      {
        graphics.swapchain.formatPriorities.clear();
        auto & src = swapchainSrc / "formatPriorities";
        for (size_t i = 0; i < src.size(); ++i)
        {
          assert((src / i).size() == 2);
          graphics.swapchain.formatPriorities.push_back(make_pair(
            (std::string)(src / i / 0), 
            (std::string)(src / i / 1)));
        }
      }

      if (swapchainSrc % "numViews")
        { graphics.swapchain.numViews = swapchainSrc / "numViews"; }
      
      if (swapchainSrc % "imageUsages")
      {
        graphics.swapchain.imageUsages.clear();
        auto & src = swapchainSrc / "imageUsages";
        for (size_t i = 0; i < src.size(); ++i)
          { graphics.swapchain.imageUsages.push_back(src / i); }
      }

      if (swapchainSrc % "imageSharing")
        { graphics.swapchain.imageSharing = swapchainSrc / "imageSharing"; }

      if (swapchainSrc % "pretransform")
        { graphics.swapchain.pretransform = (std::string)(swapchainSrc / "pretransform"); }

      if (swapchainSrc % "windowAlpha")
        { graphics.swapchain.windowAlpha = (std::string)(swapchainSrc / "windowAlpha"); }
      
      if (swapchainSrc % "presentModePriorities")
      {
        graphics.swapchain.presentModePriorities.clear();
        auto & src = swapchainSrc / "presentModePriorities";
        for (size_t i = 0; i < src.size(); ++i)
        {
          assert((src / i).size() == 2);
          graphics.swapchain.presentModePriorities.push_back(make_pair(
            (std::string)(src / i / 0), 
            (int)(src / i / 1)));
        }
      }

      if (swapchainSrc % "clipped")
        { graphics.swapchain.clipped = swapchainSrc / "clipped"; }
    }
  }
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

  deltas |= set(general.programName, rhs.general.programName, ConfigData::Deltas::Window);

  deltas |= set(general.version, rhs.general.version, ConfigData::Deltas::None);
  
  deltas |= set(general.numWorkerThreads, rhs.general.numWorkerThreads, ConfigData::Deltas::JobManagement);

  deltas |= set(graphics.isConfigured, rhs.graphics.isConfigured, ConfigData::Deltas::VulkanInstance);

  deltas |= set(graphics.headless, rhs.graphics.headless, ConfigData::Deltas::Window | ConfigData::Deltas::VulkanInstance);
  
  deltas |= set(graphics.fullScreen, rhs.graphics.fullScreen, ConfigData::Deltas::Window);
  
  deltas |= set(graphics.width, rhs.graphics.width, ConfigData::Deltas::WindowExtents);
  
  deltas |= set(graphics.height, rhs.graphics.height, ConfigData::Deltas::WindowExtents);

  deltas |= set(graphics.vulkanValidationEnabled, rhs.graphics.vulkanValidationEnabled, ConfigData::Deltas::VulkanInstance);
  
  deltas |= set(graphics.vulkanValidationLayers, rhs.graphics.vulkanValidationLayers, ConfigData::Deltas::VulkanInstance);

  deltas |= set(graphics.vulkanValidationReports, rhs.graphics.vulkanValidationReports, ConfigData::Deltas::VulkanInstance);

  deltas |= set(graphics.vulkanExtensions, rhs.graphics.vulkanExtensions, ConfigData::Deltas::VulkanInstance);

  deltas |= set(graphics.deviceExtensions, rhs.graphics.deviceExtensions, ConfigData::Deltas::VulkanInstance);

  deltas |= set(graphics.minGraphicsQueues, rhs.graphics.minGraphicsQueues, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(graphics.desiredGraphicsQueues, rhs.graphics.desiredGraphicsQueues, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(graphics.minComputeQueues, rhs.graphics.minComputeQueues, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(graphics.desiredComputeQueues, rhs.graphics.desiredComputeQueues, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(graphics.minTransferQueues, rhs.graphics.minTransferQueues, ConfigData::Deltas::PhysicalDevice);
  
  deltas |= set(graphics.desiredTransferQueues, rhs.graphics.desiredTransferQueues, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(graphics.minDeviceFeatures, rhs.graphics.minDeviceFeatures, ConfigData::Deltas::PhysicalDevice);

  deltas |= set(graphics.desiredDeviceFeatures, rhs.graphics.desiredDeviceFeatures, ConfigData::Deltas::LogicalDevice);

  deltas |= set(graphics.swapchain.formatPriorities, rhs.graphics.swapchain.formatPriorities, ConfigData::Deltas::Swapchain);

  deltas |= set(graphics.swapchain.numViews, rhs.graphics.swapchain.numViews, ConfigData::Deltas::Swapchain);

  deltas |= set(graphics.swapchain.imageUsages, rhs.graphics.swapchain.imageUsages, ConfigData::Deltas::Swapchain);
  
  deltas |= set(graphics.swapchain.imageSharing, rhs.graphics.swapchain.imageSharing, ConfigData::Deltas::Swapchain);

  deltas |= set(graphics.swapchain.pretransform, rhs.graphics.swapchain.pretransform, ConfigData::Deltas::Swapchain);
  
  deltas |= set(graphics.swapchain.windowAlpha, rhs.graphics.swapchain.windowAlpha, ConfigData::Deltas::Swapchain);
  
  deltas |= set(graphics.swapchain.presentModePriorities, rhs.graphics.swapchain.presentModePriorities, ConfigData::Deltas::Swapchain);
  
  deltas |= set(graphics.swapchain.clipped, rhs.graphics.swapchain.clipped, ConfigData::Deltas::Swapchain);
  
  lastDiffs = rhs.lastDiffs | deltas;
}


string ConfigData::print() const
{
  stringstream formatPriorities;
  for (auto & ext : graphics.swapchain.formatPriorities)
    { formatPriorities << 
      fmt::format("        [{} {}]\n",
      ext.first, ext.second); }

  stringstream presentModePriorities;
  for (auto & ext : graphics.swapchain.presentModePriorities)
    { presentModePriorities << 
      fmt::format("        [{} {}]\n",
      ext.first, ext.second); }

  return fmt::format(
    "Config:\n"
    "  general:\n"
    "    programName: {}\n"
    "    version: {}\n"
    "    numWorkerThreads: {}\n"
    "  graphics:\n"
    "    isConfigured: {}\n"
    "    headless: {}\n"
    "    fullScreen: {}\n"
    "    width: {}\n"
    "    height: {}\n"
    "    vulkanValidationEnabled: {}\n"
    "    vulkanValidationLayers: {}\n"
    "    vulkanValidationReports: {}\n"
    "    vulkanExtensions: {}\n"
    "    deviceExtensions: {}\n"
    "    minGraphicsQueues: {}\n"
    "    desiredGraphicsQueues: {}\n"
    "    minComputeQueues: {}\n"
    "    desiredCopmuetqueues: {}\n"
    "    minTransferQueues: {}\n"
    "    desiredTransferQueues: {}\n"
    "    minDeviceFeatures:\n"
    "      {}\n"
    "    desiredDeviceFeatures:\n"
    "      {}\n"
    "    swapchain:\n"
    "      formatPriorities:\n"
    "{}"
    "      numViews: {}\n"
    "      imageUsages: {}\n"
    "      imageSharing: {}\n"
    "      pretransform: {}\n"
    "      windowAlpha: {}\n"
    "      presentModePriorities:\n"
    "{}"
    "      clipped: {}",
    general.programName,
    join(general.version, ".", "{:0d}"),
    general.numWorkerThreads,
    graphics.isConfigured ? "yes" : "no",
    graphics.headless ? "yes" : "no",
    graphics.fullScreen ? "yes" : "no",
    graphics.width,
    graphics.height,
    graphics.vulkanValidationEnabled ? "yes" : "no",
    join(graphics.vulkanValidationLayers, ", ", "{}", "(none)"),
    join(graphics.vulkanValidationReports, ", ", "{}", "(none)"),
    join(graphics.vulkanExtensions, ", ", "{}", "(none)"),
    join(graphics.deviceExtensions, ", ", "{}", "(none)"),
    graphics.minGraphicsQueues,
    graphics.desiredGraphicsQueues,
    graphics.minComputeQueues,
    graphics.desiredComputeQueues,
    graphics.minTransferQueues,
    graphics.desiredTransferQueues,
    join(graphics.minDeviceFeatures, "\n      ", "{}", "(none)"),
    join(graphics.desiredDeviceFeatures, "\n      ", "{}", "(none)"),
    formatPriorities.str(),
    graphics.swapchain.numViews,
    join(graphics.swapchain.imageUsages, "\n      ", "{}", "(none)"),
    graphics.swapchain.imageSharing ? "yes" : "no",
    graphics.swapchain.pretransform,
    graphics.swapchain.windowAlpha,
    presentModePriorities.str(),
    graphics.swapchain.clipped ? "yes" : "no"
  );
}


std::ostream & overground::operator << (
  std::ostream & stream, ConfigData const & rhs)
{
  stream << rhs.print();
  return stream;
}
