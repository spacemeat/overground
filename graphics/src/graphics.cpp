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


void Graphics::reset(Config const * config)
{
  this->config = config;
  if (mainWindow == nullptr || 
    (config->lastDiffs & Config::Deltas::Window) != (Config::Deltas) 0)
  {
    if (mainWindow == nullptr)
      { createWindow(); }
    else
      { updateWindow(); }
    
    if ((bool) vulkanInstance == false ||
    (config->lastDiffs & Config::Deltas::VulkanInstance) != 0)
      { resetVulkanInstance(); }

    if ((bool) physicalDevice == false ||
    (config->lastDiffs & Config::Deltas::PhysicalDevice) != 0)
      { resetPhysicalDevice(); }

    if ((bool) vulkanDevice == false ||
    (config->lastDiffs & Config::Deltas::LogicalDevice) != 0)
      { resetLogicalDevice(); }
  }
}


void Graphics::shutDown()
{
  //...
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
  if (isSwapchainStale || isLogicalDeviceLost || isPhysicalDeviceLost)
  {
//    destroySwapchain();
  }

  if (isLogicalDeviceLost || isPhysicalDeviceLost)
  {
//    destroyLogicalDevice();
  }

  if (isPhysicalDeviceLost)
  {
//    destroyPhysicalDevice();
    return false;
  }

  if (isLogicalDeviceLost)
  {
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
