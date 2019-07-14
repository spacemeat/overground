#include "graphics.h"
#include <iostream>

using namespace std;
using namespace overground;


Graphics::Graphics()
{

}


Graphics::~Graphics()
{
  destroyWindow();
}


void Graphics::reset(ConfigData * config)
{
  logFn();

  this->config = config;
  if (mainWindow == nullptr || 
    (config->getDiffs() & 
      (ConfigData::Deltas::Window | 
       ConfigData::Deltas::WindowExtents)) != 0)
  {
    if (mainWindow == nullptr)
      { createWindow(); }
    else
      { updateWindow(); }
  }
    
  if ((bool) vulkanInstance == false ||
    (config->getDiffs() & 
     ConfigData::Deltas::VulkanInstance) != 0)
    { resetVulkanInstance(); }

  if ((bool) surface == false ||
    (config->getDiffs() & 
      (ConfigData::Deltas::Window |
       ConfigData::Deltas::WindowExtents)) != 0)
    { resetSurface(); }

  if ((bool) physicalDevice == false ||
    (config->getDiffs() & 
     (ConfigData::Deltas::Window |
       ConfigData::Deltas::WindowExtents |
       ConfigData::Deltas::PhysicalDevice)) != 0)
    { resetPhysicalDevice(); }

  if ((bool) vulkanDevice == false ||
    (config->getDiffs() & 
     ConfigData::Deltas::LogicalDevice) != 0)
    { resetLogicalDevice(); }

  if ((bool) swapchain == false ||
    (config->getDiffs() & 
      (ConfigData::Deltas::WindowExtents |
       ConfigData::Deltas::Swapchain)) != 0)
    { resetSwapchain(); }
}


void Graphics::shutDown()
{
  logFn();
  destroyVulkanInstance();
}


void Graphics::presentFrame()
{
  // present frame n-1
}


void Graphics::drawFrame()
{
  if (manageInvalidDevice() == false)
    { return; }

  // draw calls frame n
}


void Graphics::waitForGraphicsOps()
{
  vulkanDevice.waitIdle();
}


bool Graphics::manageInvalidDevice()
{
  if (isLogicalDeviceLost)
  {
//    destroySwapchain();
//    destroyLogicalDevice();
//    createDevice();
  }

  if (isLogicalDeviceLost || isSwapchainStale)
  {
//    createSwapchain();
    if (isLogicalDeviceLost)
    {
//      loadScene(); ??
    }
  }

  isLogicalDeviceLost = false;
  isSwapchainStale = false;

  return true;
}
