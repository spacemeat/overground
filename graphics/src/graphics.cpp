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

  if ((bool) physicalDevice == false ||
    (config->getDiffs() & 
     ConfigData::Deltas::PhysicalDevice) != 0)
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
  //...
  destroySwapchain();
  destroyLogicalDevice();
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


//void Graphics::waitForGraphicsOps()
//{
//  vd.waitIdle();
//}


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
