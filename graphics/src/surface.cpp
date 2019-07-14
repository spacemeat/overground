#include "graphics.h"

using namespace std;
using namespace overground;


void Graphics::resetSurface()
{
  logFn();

  if (surface)
    { destroySurface(); }

  VkSurfaceKHR surfaceC;

  log(thId, "Graphics::resetSurface(): acually do that");

  if (glfwCreateWindowSurface(vulkanInstance, mainWindow, nullptr, & surfaceC) != VK_SUCCESS)
  { throw std::runtime_error("failed to create window surface."); }

  surface = vk::SurfaceKHR(surfaceC);

  // Some of these are dependent on the surface.
  if (physicalDevice)
  {
    swapchainSurfaceCaps = 
      physicalDevice.getSurfaceCapabilitiesKHR(surface);
    swapchainSurfaceFormats = 
      physicalDevice.getSurfaceFormatsKHR(surface);
    swapchainPresentModes = 
      physicalDevice.getSurfacePresentModesKHR(surface);
  }
}


void Graphics::destroySurface()
{
  logFn();

  destroySwapchain();
  
  log(thId, "Graphics::destroySurface(): actually do that");
  vulkanInstance.destroySurfaceKHR(surface, nullptr);
}
