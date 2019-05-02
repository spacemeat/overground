#ifndef GRAPHICS_H
#define GRAPHICS_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

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

    void reset(Config const & config);
//    void waitForGraphicsOps();
    void presentFrame();
    void drawFrame();

  private:
    void createWindow(Config const & config);
    void updateWindow(Config const & config);
    void destroyWindow();

    bool manageInvalidDevice();
    
  private:
    GLFWwindow * mainWindow = nullptr;
    uint32_t diWidth = 0;   // device-indep. units
    uint32_t diHeight = 0;  // device-indep. units
    bool isFullScreen = false;

    bool isPhysicalDeviceLost = false;
    bool isLogicalDeviceLost = false;
    bool isSwapchainStale = false;

//    vk::Instance vulkanInstance;
//    VkDebugReportCallbackEXT debugCallback;

//    vk::PhysicalDevice vpd;
//    vk::Device vd;
  };
}

#endif // #ifndef GRAPHICS_H

