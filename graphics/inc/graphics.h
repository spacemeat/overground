#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "graphicsUtils.h"
#include <string>
#include <set>
#include "config.h"

namespace overground
{
  class Graphics
  {
    struct fitness_t
    { 
      int g = 0; int c = 0;
      int t = 0; int p = 0;
    };

    struct deviceFitness_t
    {
      std::vector<fitness_t> queueFamilyFitness;
      std::vector<fitness_t> queueCountsAllowed;
      fitness_t deviceQueueFitness;
      fitness_t bestQueueIndices = { -1, -1, -1, -1};
      fitness_t queueCounts;
      int featureScore = 1;
      int finalDeviceScore = 0;
      std::vector<std::string> unsupportedMinFeatures;
      std::vector<std::string>
      unsupportedDesiredFeatures;
    };

  public:
    Graphics();
    ~Graphics();

    GLFWwindow * getMainWindow() { return mainWindow; }

    void reset(ConfigData * config);
//    void waitForGraphicsOps();
    void shutDown();

    void presentFrame();
    void drawFrame();

  private:
    bool manageInvalidDevice();
    
    // window.cpp
    void createWindow();
    void updateWindow();
    void destroyWindow();

    // instance.cpp
    void resetVulkanInstance();
    void destroyVulkanInstance();
    void resetVulkanDebugReporter();
    void destroyVulkanDebugReporter();
    bool checkVulkanExtensionSupport();
    bool checkVulkanValidationLayerSupport();
    void resetSurface();
    void destroySurface();

    // physDev.cpp
    void resetPhysicalDevice();
    void reportPhysicalDevice(vk::PhysicalDevice device, deviceFitness_t const & fitness, std::ostream & out);
    bool computePhysicalDeviceFeatures(vk::PhysicalDevice device, deviceFitness_t & pdf);

    // device.cpp
    void resetLogicalDevice();
    void destroyLogicalDevice();
    void prepareQueues();

    // swapChain.cpp
    void resetSwapchain();
    void destroySwapchain();
    void chooseSurfaceFormat();
    void choosePresentMode();
    void getExtent();
    void createSwapChainImageViews();
    void destroySwapChainImageViews();
    
  private:
    ConfigData * config;
    GLFWwindow * mainWindow = nullptr;
    uint32_t diWidth = 0;   // device-indep. units
    uint32_t diHeight = 0;  // device-indep. units
    bool isFullScreen = false;

    bool isLogicalDeviceLost = false;
    bool isSwapchainStale = false;

    vk::Instance vulkanInstance;
    std::vector<std::string> validationLayers;
    std::vector<std::string> extensions;
    std::set<std::string> deviceExtensions;
    VkDebugReportCallbackEXT debugCallback = nullptr;
    vk::SurfaceKHR surface;

    std::vector<deviceFitness_t> physicalDeviceFitness;
    int physicalDeviceIndex = -1;
    vk::PhysicalDevice physicalDevice;
    int graphicsQueueFamilyIndex = -1;
    int computeQueueFamilyIndex = -1;
    int transferQueueFamilyIndex = -1;
    int presentationQueueFamilyIndex = -1;

    vk::SurfaceCapabilitiesKHR swapchainSurfaceCaps;
    std::vector<vk::SurfaceFormatKHR> swapchainSurfaceFormats;
    std::vector<vk::PresentModeKHR> swapchainPresentModes;

    vk::PhysicalDeviceFeatures usedFeatures;
    std::set<uint32_t> uniqueFamilyIndices;
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;

    vk::Device vulkanDevice;

    std::vector<std::vector<vk::Queue>> queues;
    std::vector<vk::Queue *> gQueues;
    std::vector<vk::Queue *> cQueues;
    vk::Queue * tQueue;
    vk::Queue * pQueue;

    vk::SurfaceFormatKHR swapchainSurfaceFormat;
    vk::PresentModeKHR swapchainPresentMode;
    int swapchainImageCount;
    vk::Extent2D swapchainExtent;

    vk::SwapchainKHR swapchain;
    std::vector<vk::Image> swapchainImages;
    std::vector<vk::ImageView> swapchainImageViews;
  };
}

#endif // #ifndef GRAPHICS_H

