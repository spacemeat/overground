#include "graphics.h"
#include "config.h"
#include "engine.h"
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


void Graphics::reset()
{
  logFn();

  checkForDataUpdates();
}


void Graphics::checkForDataUpdates()
{
  logFn();

  auto & updatedObjectKinds = engine->getUpdatedObjectKinds();

  if (updatedObjectKinds == DataObjectKindFlags::none)
    { return; }

  if ((updatedObjectKinds & 
      DataObjectKindFlags::config) != 0)
    { checkForConfigUpdates(); }

  if ((updatedObjectKinds &
      DataObjectKindFlags::renderPass) != 0)
    { checkForRenderPassUpdates(); }
}


void Graphics::checkForConfigUpdates()
{
  logFn();

  auto & diffs = engine->getConfigDiffs();
  
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
    (diffs & Config::Deltas::VulkanInstance) != 0)
    { resetVulkanInstance(); }

  if ((bool) surface == false)
    { resetSurface(); }

  if ((bool) physicalDevice == false ||
    (diffs & Config::Deltas::PhysicalDevice) != 0)
    { resetPhysicalDevice(); }

  if ((bool) vulkanDevice == false ||
    (diffs & Config::Deltas::LogicalDevice) != 0)
    { resetLogicalDevice(); }

  if ((bool) swapchain == false ||
    (diffs & Config::Deltas::Swapchain) != 0)
    { resetSwapchain(); }
}


void Graphics::checkForRenderPassUpdates()
{
  logFn();
  
  for (auto & [_, rpt] : renderPassThings)
  {
    for (auto & st : swapchainThings)
    {
      if (st.renderPasses.size() <= rpt.idx)
        { st.renderPasses.resize(
          rpt.idx + 1, nullptr); }
    }

    resetRenderPass(rpt);

    for (auto & st : swapchainThings)
    {
      if (st.framebuffers.size() <= rpt.idx)
        { st.framebuffers.resize(
          rpt.idx + 1, nullptr); }
    }

    resetFramebuffer(rpt);

    rpt.updated = false;
  }
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
