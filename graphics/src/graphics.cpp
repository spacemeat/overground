#include "graphics.h"
#include "config.h"
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


void Graphics::reset(config_t * config, Config::Deltas & diffs)
{
  logFn();

  this->config = config;
  if (mainWindow == nullptr || 
    (diffs & 
      (Config::Deltas::Window | 
       Config::Deltas::WindowExtents)) != 0)
  {
    if (mainWindow == nullptr)
      { createWindow(); }
    else
      { updateWindow(); }
  }
    
  if ((bool) vulkanInstance == false ||
    (diffs & 
     Config::Deltas::VulkanInstance) != 0)
    { resetVulkanInstance(diffs); }

  if ((bool) surface == false ||
    (diffs & 
      (Config::Deltas::Window |
       Config::Deltas::WindowExtents)) != 0)
    { resetSurface(diffs); }

  if ((bool) physicalDevice == false ||
    (diffs & 
     (Config::Deltas::Window |
       Config::Deltas::WindowExtents |
       Config::Deltas::PhysicalDevice)) != 0)
    { resetPhysicalDevice(diffs); }

  if ((bool) vulkanDevice == false ||
    (diffs & 
     Config::Deltas::LogicalDevice) != 0)
    { resetLogicalDevice(diffs); }

  if ((bool) swapchain == false ||
    (diffs & 
      (Config::Deltas::WindowExtents |
       Config::Deltas::Swapchain)) != 0)
    { resetSwapchain(diffs); }
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
