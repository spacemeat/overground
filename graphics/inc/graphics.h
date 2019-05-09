#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "graphicsUtils.h"
#include <string>
#include "config.h"

namespace overground
{
  class Graphics
  {
    struct fitness_t { int g = 0; int c = 0; int t = 0; int p = 0; };

  public:
    Graphics();
    ~Graphics();

    GLFWwindow * getMainWindow() { return mainWindow; }

    void reset(Config const * config);
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
    void reportPhysicalDevice(vk::PhysicalDevice const & physDev, std::vector<fitness_t> const & queueFamFitnesses, fitness_t const & deviceFitness, int featureScore, int deviceScore, std::ostream & out);

    void createLogicalDevice();
    void destroyLogicalDevice();
    
  private:
    Config const * config;
    GLFWwindow * mainWindow = nullptr;
    uint32_t diWidth = 0;   // device-indep. units
    uint32_t diHeight = 0;  // device-indep. units
    bool isFullScreen = false;

    bool isPhysicalDeviceLost = false;
    bool isLogicalDeviceLost = false;
    bool isSwapchainStale = false;

    vk::Instance vulkanInstance;
    std::vector<char const *> validationLayers;
    std::vector<char const *> extensions;
    std::vector<char const *> deviceExtensions;
    VkDebugReportCallbackEXT debugCallback = nullptr;
    vk::SurfaceKHR surface;

    vk::PhysicalDevice physicalDevice;
    int graphicsQueueFamilyIndex = -1;
    int computeQueueFamilyIndex = -1;
    int transferQueueFamilyIndex = -1;
    int presentationQueueFamilyIndex = -1;

    vk::SurfaceCapabilitiesKHR swapChainSurfaceCaps;
    std::vector<vk::SurfaceFormatKHR> swapChainSurfaceFormats;
    std::vector<vk::PresentModeKHR> swapChainPresentModes;

//    vk::Device vd;
  };
}

#endif // #ifndef GRAPHICS_H

