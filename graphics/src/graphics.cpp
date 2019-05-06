#include "graphics.h"
#include <iostream>

using namespace std;
using namespace overground;


Graphics::Graphics()
{

}


Graphics::~Graphics()
{
  // TODO: big stuff
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
  }
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



void Graphics::createPhysicalDevice()
{

}


void Graphics::destroyPhysicalDevice()
{

}


void Graphics::createLogicalDevice()
{

}


void Graphics::destroyLogicalDevice()
{

}
