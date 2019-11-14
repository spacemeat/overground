#ifndef config_GEN_H
#define config_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  namespace config
  {
    // general things

    struct general_t
    {
      std::string programName;
      std::array<int, 3> version;
      int numWorkerThreads;
    };

    void importPod(
      humon::HuNode const & src, general_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, general_t & dest);

    void exportPod(general_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      general_t const & src, std::vector<uint8_t> & dest);

    std::string print(general_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, general_t const & src);

    enum class generalMembers_e : int 
    {
      none = 0,
      programName = 1 << 0,
      version = 1 << 1,
      numWorkerThreads = 1 << 2,
      all = programName | version | numWorkerThreads
    };

    inline bool operator == (general_t const & lhs, general_t const & rhs) noexcept
    {
      return
        lhs.programName == rhs.programName &&
        lhs.version == rhs.version &&
        lhs.numWorkerThreads == rhs.numWorkerThreads;
    };

    inline bool operator != (general_t const & lhs, general_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct generalDiffs_t
    {
      generalMembers_e diffs;
      std::vector<size_t> versionDiffs;
    };

    inline bool doPodsDiffer(
      general_t const & lhs,
      general_t const & rhs,
      generalDiffs_t & general) noexcept
    {
      // diff member 'programName':
      if (lhs.programName != rhs.programName)
        { general.diffs |= generalMembers_e::programName; }
      // diff member 'version':
      for (size_t i = 0; i < lhs.version.size(); ++i)
      {
        if (lhs.version[i] != rhs.version[i])
        {
          general.diffs |= generalMembers_e::version;
          general.versionDiffs.push_back(i);
        }
      }
      // diff member 'numWorkerThreads':
      if (lhs.numWorkerThreads != rhs.numWorkerThreads)
        { general.diffs |= generalMembers_e::numWorkerThreads; }

      return general.diffs != generalMembers_e::none;
    };

    // swapchainImageView things

    struct swapchainImageView_t
    {
      vk::ImageViewType viewType;
      std::array<vk::ComponentSwizzle, 4> components;
      vk::ImageAspectFlagBits aspectMask;
    };

    void importPod(
      humon::HuNode const & src, swapchainImageView_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, swapchainImageView_t & dest);

    void exportPod(swapchainImageView_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      swapchainImageView_t const & src, std::vector<uint8_t> & dest);

    std::string print(swapchainImageView_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, swapchainImageView_t const & src);

    enum class swapchainImageViewMembers_e : int 
    {
      none = 0,
      viewType = 1 << 0,
      components = 1 << 1,
      aspectMask = 1 << 2,
      all = viewType | components | aspectMask
    };

    inline bool operator == (swapchainImageView_t const & lhs, swapchainImageView_t const & rhs) noexcept
    {
      return
        lhs.viewType == rhs.viewType &&
        lhs.components == rhs.components &&
        lhs.aspectMask == rhs.aspectMask;
    };

    inline bool operator != (swapchainImageView_t const & lhs, swapchainImageView_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct swapchainImageViewDiffs_t
    {
      swapchainImageViewMembers_e diffs;
      std::vector<size_t> componentsDiffs;
    };

    inline bool doPodsDiffer(
      swapchainImageView_t const & lhs,
      swapchainImageView_t const & rhs,
      swapchainImageViewDiffs_t & swapchainImageView) noexcept
    {
      // diff member 'viewType':
      if (lhs.viewType != rhs.viewType)
        { swapchainImageView.diffs |= swapchainImageViewMembers_e::viewType; }
      // diff member 'components':
      for (size_t i = 0; i < lhs.components.size(); ++i)
      {
        if (lhs.components[i] != rhs.components[i])
        {
          swapchainImageView.diffs |= swapchainImageViewMembers_e::components;
          swapchainImageView.componentsDiffs.push_back(i);
        }
      }
      // diff member 'aspectMask':
      if (lhs.aspectMask != rhs.aspectMask)
        { swapchainImageView.diffs |= swapchainImageViewMembers_e::aspectMask; }

      return swapchainImageView.diffs != swapchainImageViewMembers_e::none;
    };

    // swapchain things

    struct swapchain_t
    {
      std::vector<std::pair<vk::Format, vk::ColorSpaceKHR>> formatPriorities;
      unsigned int numViews;
      std::vector<string> imageUsages;
      bool imageSharing;
      vk::SurfaceTransformFlagBitsKHR pretransform;
      vk::CompositeAlphaFlagBitsKHR windowAlpha;
      std::vector<std::pair<vk::PresentModeKHR, std::uint32_t>> presentModePriorities;
      bool clipped;
      swapchainImageView_t imageView;
    };

    void importPod(
      humon::HuNode const & src, swapchain_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, swapchain_t & dest);

    void exportPod(swapchain_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      swapchain_t const & src, std::vector<uint8_t> & dest);

    std::string print(swapchain_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, swapchain_t const & src);

    enum class swapchainMembers_e : int 
    {
      none = 0,
      formatPriorities = 1 << 0,
      numViews = 1 << 1,
      imageUsages = 1 << 2,
      imageSharing = 1 << 3,
      pretransform = 1 << 4,
      windowAlpha = 1 << 5,
      presentModePriorities = 1 << 6,
      clipped = 1 << 7,
      imageView = 1 << 8,
      all = formatPriorities | numViews | imageUsages | imageSharing | pretransform | windowAlpha | presentModePriorities | clipped | imageView
    };

    inline bool operator == (swapchain_t const & lhs, swapchain_t const & rhs) noexcept
    {
      return
        lhs.formatPriorities == rhs.formatPriorities &&
        lhs.numViews == rhs.numViews &&
        lhs.imageUsages == rhs.imageUsages &&
        lhs.imageSharing == rhs.imageSharing &&
        lhs.pretransform == rhs.pretransform &&
        lhs.windowAlpha == rhs.windowAlpha &&
        lhs.presentModePriorities == rhs.presentModePriorities &&
        lhs.clipped == rhs.clipped &&
        lhs.imageView == rhs.imageView;
    };

    inline bool operator != (swapchain_t const & lhs, swapchain_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct swapchainDiffs_t
    {
      swapchainMembers_e diffs;
      std::vector<size_t> formatPrioritiesDiffs;
      std::vector<size_t> imageUsagesDiffs;
      std::vector<size_t> presentModePrioritiesDiffs;
      swapchainImageViewDiffs_t imageView;
    };

    inline bool doPodsDiffer(
      swapchain_t const & lhs,
      swapchain_t const & rhs,
      swapchainDiffs_t & swapchain) noexcept
    {
      // diff member 'formatPriorities':
      {
        auto [mn, mx] = std::minmax(lhs.formatPriorities.size(), rhs.formatPriorities.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.formatPriorities[i] != rhs.formatPriorities[i])
          {
            swapchain.diffs |= swapchainMembers_e::formatPriorities;
            swapchain.formatPrioritiesDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          swapchain.formatPrioritiesDiffs.push_back(i);
        }
      }
      // diff member 'numViews':
      if (lhs.numViews != rhs.numViews)
        { swapchain.diffs |= swapchainMembers_e::numViews; }
      // diff member 'imageUsages':
      {
        auto [mn, mx] = std::minmax(lhs.imageUsages.size(), rhs.imageUsages.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.imageUsages[i] != rhs.imageUsages[i])
          {
            swapchain.diffs |= swapchainMembers_e::imageUsages;
            swapchain.imageUsagesDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          swapchain.imageUsagesDiffs.push_back(i);
        }
      }
      // diff member 'imageSharing':
      if (lhs.imageSharing != rhs.imageSharing)
        { swapchain.diffs |= swapchainMembers_e::imageSharing; }
      // diff member 'pretransform':
      if (lhs.pretransform != rhs.pretransform)
        { swapchain.diffs |= swapchainMembers_e::pretransform; }
      // diff member 'windowAlpha':
      if (lhs.windowAlpha != rhs.windowAlpha)
        { swapchain.diffs |= swapchainMembers_e::windowAlpha; }
      // diff member 'presentModePriorities':
      {
        auto [mn, mx] = std::minmax(lhs.presentModePriorities.size(), rhs.presentModePriorities.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.presentModePriorities[i] != rhs.presentModePriorities[i])
          {
            swapchain.diffs |= swapchainMembers_e::presentModePriorities;
            swapchain.presentModePrioritiesDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          swapchain.presentModePrioritiesDiffs.push_back(i);
        }
      }
      // diff member 'clipped':
      if (lhs.clipped != rhs.clipped)
        { swapchain.diffs |= swapchainMembers_e::clipped; }
      // diff member 'imageView':
      if (doPodsDiffer(lhs.imageView, rhs.imageView, swapchain.imageView))
        { swapchain.diffs |= swapchainMembers_e::imageView; }

      return swapchain.diffs != swapchainMembers_e::none;
    };

    // graphics things

    struct graphics_t
    {
      bool isConfigured = (bool)false;
      bool headless;
      bool fullScreen;
      unsigned int width;
      unsigned int height;
      bool vulkanValidationEnabled;
      std::vector<string> vulkanValidationLayers;
      std::vector<string> vulkanValidationReports;
      std::vector<string> vulkanExtensions;
      std::vector<string> deviceExtensions;
      unsigned int minGraphicsQueues;
      unsigned int desiredGraphicsQueues;
      unsigned int minComputeQueues;
      unsigned int desiredComputeQueues;
      unsigned int minTransferQueues;
      unsigned int desiredTransferQueues;
      std::vector<string> minDeviceFeatures;
      std::vector<string> desiredDeviceFeatures;
      swapchain_t swapchain;
      BufferStrategy bufferStrategy;
    };

    void importPod(
      humon::HuNode const & src, graphics_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, graphics_t & dest);

    void exportPod(graphics_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      graphics_t const & src, std::vector<uint8_t> & dest);

    std::string print(graphics_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, graphics_t const & src);

    enum class graphicsMembers_e : int 
    {
      none = 0,
      isConfigured = 1 << 0,
      headless = 1 << 1,
      fullScreen = 1 << 2,
      width = 1 << 3,
      height = 1 << 4,
      vulkanValidationEnabled = 1 << 5,
      vulkanValidationLayers = 1 << 6,
      vulkanValidationReports = 1 << 7,
      vulkanExtensions = 1 << 8,
      deviceExtensions = 1 << 9,
      minGraphicsQueues = 1 << 10,
      desiredGraphicsQueues = 1 << 11,
      minComputeQueues = 1 << 12,
      desiredComputeQueues = 1 << 13,
      minTransferQueues = 1 << 14,
      desiredTransferQueues = 1 << 15,
      minDeviceFeatures = 1 << 16,
      desiredDeviceFeatures = 1 << 17,
      swapchain = 1 << 18,
      bufferStrategy = 1 << 19,
      all = isConfigured | headless | fullScreen | width | height | vulkanValidationEnabled | vulkanValidationLayers | vulkanValidationReports | vulkanExtensions | deviceExtensions | minGraphicsQueues | desiredGraphicsQueues | minComputeQueues | desiredComputeQueues | minTransferQueues | desiredTransferQueues | minDeviceFeatures | desiredDeviceFeatures | swapchain | bufferStrategy
    };

    inline bool operator == (graphics_t const & lhs, graphics_t const & rhs) noexcept
    {
      return
        lhs.isConfigured == rhs.isConfigured &&
        lhs.headless == rhs.headless &&
        lhs.fullScreen == rhs.fullScreen &&
        lhs.width == rhs.width &&
        lhs.height == rhs.height &&
        lhs.vulkanValidationEnabled == rhs.vulkanValidationEnabled &&
        lhs.vulkanValidationLayers == rhs.vulkanValidationLayers &&
        lhs.vulkanValidationReports == rhs.vulkanValidationReports &&
        lhs.vulkanExtensions == rhs.vulkanExtensions &&
        lhs.deviceExtensions == rhs.deviceExtensions &&
        lhs.minGraphicsQueues == rhs.minGraphicsQueues &&
        lhs.desiredGraphicsQueues == rhs.desiredGraphicsQueues &&
        lhs.minComputeQueues == rhs.minComputeQueues &&
        lhs.desiredComputeQueues == rhs.desiredComputeQueues &&
        lhs.minTransferQueues == rhs.minTransferQueues &&
        lhs.desiredTransferQueues == rhs.desiredTransferQueues &&
        lhs.minDeviceFeatures == rhs.minDeviceFeatures &&
        lhs.desiredDeviceFeatures == rhs.desiredDeviceFeatures &&
        lhs.swapchain == rhs.swapchain &&
        lhs.bufferStrategy == rhs.bufferStrategy;
    };

    inline bool operator != (graphics_t const & lhs, graphics_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct graphicsDiffs_t
    {
      graphicsMembers_e diffs;
      std::vector<size_t> vulkanValidationLayersDiffs;
      std::vector<size_t> vulkanValidationReportsDiffs;
      std::vector<size_t> vulkanExtensionsDiffs;
      std::vector<size_t> deviceExtensionsDiffs;
      std::vector<size_t> minDeviceFeaturesDiffs;
      std::vector<size_t> desiredDeviceFeaturesDiffs;
      swapchainDiffs_t swapchain;
    };

    inline bool doPodsDiffer(
      graphics_t const & lhs,
      graphics_t const & rhs,
      graphicsDiffs_t & graphics) noexcept
    {
      // diff member 'isConfigured':
      if (lhs.isConfigured != rhs.isConfigured)
        { graphics.diffs |= graphicsMembers_e::isConfigured; }
      // diff member 'headless':
      if (lhs.headless != rhs.headless)
        { graphics.diffs |= graphicsMembers_e::headless; }
      // diff member 'fullScreen':
      if (lhs.fullScreen != rhs.fullScreen)
        { graphics.diffs |= graphicsMembers_e::fullScreen; }
      // diff member 'width':
      if (lhs.width != rhs.width)
        { graphics.diffs |= graphicsMembers_e::width; }
      // diff member 'height':
      if (lhs.height != rhs.height)
        { graphics.diffs |= graphicsMembers_e::height; }
      // diff member 'vulkanValidationEnabled':
      if (lhs.vulkanValidationEnabled != rhs.vulkanValidationEnabled)
        { graphics.diffs |= graphicsMembers_e::vulkanValidationEnabled; }
      // diff member 'vulkanValidationLayers':
      {
        auto [mn, mx] = std::minmax(lhs.vulkanValidationLayers.size(), rhs.vulkanValidationLayers.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.vulkanValidationLayers[i] != rhs.vulkanValidationLayers[i])
          {
            graphics.diffs |= graphicsMembers_e::vulkanValidationLayers;
            graphics.vulkanValidationLayersDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          graphics.vulkanValidationLayersDiffs.push_back(i);
        }
      }
      // diff member 'vulkanValidationReports':
      {
        auto [mn, mx] = std::minmax(lhs.vulkanValidationReports.size(), rhs.vulkanValidationReports.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.vulkanValidationReports[i] != rhs.vulkanValidationReports[i])
          {
            graphics.diffs |= graphicsMembers_e::vulkanValidationReports;
            graphics.vulkanValidationReportsDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          graphics.vulkanValidationReportsDiffs.push_back(i);
        }
      }
      // diff member 'vulkanExtensions':
      {
        auto [mn, mx] = std::minmax(lhs.vulkanExtensions.size(), rhs.vulkanExtensions.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.vulkanExtensions[i] != rhs.vulkanExtensions[i])
          {
            graphics.diffs |= graphicsMembers_e::vulkanExtensions;
            graphics.vulkanExtensionsDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          graphics.vulkanExtensionsDiffs.push_back(i);
        }
      }
      // diff member 'deviceExtensions':
      {
        auto [mn, mx] = std::minmax(lhs.deviceExtensions.size(), rhs.deviceExtensions.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.deviceExtensions[i] != rhs.deviceExtensions[i])
          {
            graphics.diffs |= graphicsMembers_e::deviceExtensions;
            graphics.deviceExtensionsDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          graphics.deviceExtensionsDiffs.push_back(i);
        }
      }
      // diff member 'minGraphicsQueues':
      if (lhs.minGraphicsQueues != rhs.minGraphicsQueues)
        { graphics.diffs |= graphicsMembers_e::minGraphicsQueues; }
      // diff member 'desiredGraphicsQueues':
      if (lhs.desiredGraphicsQueues != rhs.desiredGraphicsQueues)
        { graphics.diffs |= graphicsMembers_e::desiredGraphicsQueues; }
      // diff member 'minComputeQueues':
      if (lhs.minComputeQueues != rhs.minComputeQueues)
        { graphics.diffs |= graphicsMembers_e::minComputeQueues; }
      // diff member 'desiredComputeQueues':
      if (lhs.desiredComputeQueues != rhs.desiredComputeQueues)
        { graphics.diffs |= graphicsMembers_e::desiredComputeQueues; }
      // diff member 'minTransferQueues':
      if (lhs.minTransferQueues != rhs.minTransferQueues)
        { graphics.diffs |= graphicsMembers_e::minTransferQueues; }
      // diff member 'desiredTransferQueues':
      if (lhs.desiredTransferQueues != rhs.desiredTransferQueues)
        { graphics.diffs |= graphicsMembers_e::desiredTransferQueues; }
      // diff member 'minDeviceFeatures':
      {
        auto [mn, mx] = std::minmax(lhs.minDeviceFeatures.size(), rhs.minDeviceFeatures.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.minDeviceFeatures[i] != rhs.minDeviceFeatures[i])
          {
            graphics.diffs |= graphicsMembers_e::minDeviceFeatures;
            graphics.minDeviceFeaturesDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          graphics.minDeviceFeaturesDiffs.push_back(i);
        }
      }
      // diff member 'desiredDeviceFeatures':
      {
        auto [mn, mx] = std::minmax(lhs.desiredDeviceFeatures.size(), rhs.desiredDeviceFeatures.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.desiredDeviceFeatures[i] != rhs.desiredDeviceFeatures[i])
          {
            graphics.diffs |= graphicsMembers_e::desiredDeviceFeatures;
            graphics.desiredDeviceFeaturesDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          graphics.desiredDeviceFeaturesDiffs.push_back(i);
        }
      }
      // diff member 'swapchain':
      if (doPodsDiffer(lhs.swapchain, rhs.swapchain, graphics.swapchain))
        { graphics.diffs |= graphicsMembers_e::swapchain; }
      // diff member 'bufferStrategy':
      if (lhs.bufferStrategy != rhs.bufferStrategy)
        { graphics.diffs |= graphicsMembers_e::bufferStrategy; }

      return graphics.diffs != graphicsMembers_e::none;
    };

    // config things

    struct config_t
    {
      general_t general;
      graphics_t graphics;
    };

    void importPod(
      humon::HuNode const & src, config_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, config_t & dest);

    void exportPod(config_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      config_t const & src, std::vector<uint8_t> & dest);

    std::string print(config_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, config_t const & src);

    enum class configMembers_e : int 
    {
      none = 0,
      general = 1 << 0,
      graphics = 1 << 1,
      all = general | graphics
    };

    inline bool operator == (config_t const & lhs, config_t const & rhs) noexcept
    {
      return
        lhs.general == rhs.general &&
        lhs.graphics == rhs.graphics;
    };

    inline bool operator != (config_t const & lhs, config_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct configDiffs_t
    {
      configMembers_e diffs;
      generalDiffs_t general;
      graphicsDiffs_t graphics;
    };

    inline bool doPodsDiffer(
      config_t const & lhs,
      config_t const & rhs,
      configDiffs_t & config) noexcept
    {
      // diff member 'general':
      if (doPodsDiffer(lhs.general, rhs.general, config.general))
        { config.diffs |= configMembers_e::general; }
      // diff member 'graphics':
      if (doPodsDiffer(lhs.graphics, rhs.graphics, config.graphics))
        { config.diffs |= configMembers_e::graphics; }

      return config.diffs != configMembers_e::none;
    };

  }
}

#endif // #ifndef config_GEN_H
