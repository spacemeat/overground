#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "graphicsUtils.h"
#include <string>
#include "config.h"

namespace overground
{
  class Graphics
  {
  public:
    Graphics();
    ~Graphics();

    GLFWwindow * getMainWindow() { return mainWindow; }

    void reset(Config const * config);
//    void waitForGraphicsOps();
    void presentFrame();
    void drawFrame();

  private:
    void createWindow();
    void updateWindow();
    void destroyWindow();

    bool manageInvalidDevice();
    
    // instance.cpp
    void createVulkanInstance();
    void destroyVulkanInstance();
    bool checkExtensionSupport();
    bool checkValidationLayerSupport();

    void createPhysicalDevice();
    void destroyPhysicalDevice();

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
    VkDebugReportCallbackEXT debugCallback;
    std::vector<char const *> validationLayers;
    std::vector<char const *> extensions;
    std::vector<char const *> deviceExtensions;
//    VkDebugReportCallbackEXT debugCallback;

//    vk::PhysicalDevice vpd;
//    vk::Device vd;
  };
}

#endif // #ifndef GRAPHICS_H

