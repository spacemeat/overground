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


void Graphics::reset(Config * config)
{
  this->config = config;
  if (mainWindow == nullptr || 
    (config->getDiffs() & Config::Deltas::Window) != (Config::Deltas) 0)
  {
    if (mainWindow == nullptr)
      { createWindow(); }
    else
      { updateWindow(); }
    
    if ((bool) vulkanInstance == false ||
    (config->getDiffs() & Config::Deltas::VulkanInstance) != 0)
      { resetVulkanInstance(); }

    if ((bool) physicalDevice == false ||
    (config->getDiffs() & Config::Deltas::PhysicalDevice) != 0)
      { resetPhysicalDevice(); }

    if ((bool) vulkanDevice == false ||
    (config->getDiffs() & Config::Deltas::LogicalDevice) != 0)
      { resetLogicalDevice(); }

    if ((bool) swapchain == false ||
    (config->getDiffs() & Config::Deltas::Swapchain) != 0)
      { resetSwapchain(); }

  }
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
