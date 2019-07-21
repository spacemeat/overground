#ifndef config_GEN_H
#define config_GEN_H

#include <string>
#include <vector>
#include "utils.h"
#include "graphicsUtils.h"

namespace overground
{
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


  struct swapchainImageView_t
  {
    vk::ImageViewType viewType;
    std::array<vk::ComponentSwizzle, 4> components;
    vk::ImageAspectFlags aspectMask;
    unsigned int layerCount;
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


  struct swapchain_t
  {
    std::vector<std::pair<vk::Format, vk::ColorSpaceKHR>> formatPriorities;
    unsigned int numViews;
    std::vector<std::string> imageUsages;
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


  struct graphics_t
  {
    bool isConfigured = false;
    bool headless;
    bool fullScreen;
    unsigned int width;
    unsigned int height;
    bool vulkanValidationEnabled;
    std::vector<std::string> vulkanValidationLayers;
    std::vector<std::string> vulkanValidationReports;
    std::vector<std::string> vulkanExtensions;
    std::vector<std::string> deviceExtensions;
    unsigned int minGraphicsQueues;
    unsigned int desiredGraphicsQueues;
    unsigned int minComputeQueues;
    unsigned int desiredComputeQueues;
    unsigned int minTransferQueues;
    unsigned int desiredTransferQueues;
    std::vector<std::string> minDeviceFeatures;
    std::vector<std::string> desiredDeviceFeatures;
    swapchain_t swapchain;
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


}

#endif // #ifndef config_GEN_H
