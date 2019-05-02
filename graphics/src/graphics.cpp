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


void Graphics::reset(Config const & config)
{
  if (mainWindow == nullptr || 
    (config.lastDiffs & Config::Deltas::Window) == Config::Deltas::Window)
  {
    if (mainWindow == nullptr)
      { createWindow(config); }
    else
      { updateWindow(config); }
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


void Graphics::createWindow(Config const & config)
{
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  isFullScreen = config.graphics.fullScreen;
  diWidth = config.graphics.width;
  diHeight = config.graphics.height;

  auto monitor = isFullScreen ? glfwGetPrimaryMonitor() : nullptr;

  mainWindow = glfwCreateWindow(diWidth, diHeight, config.general.programName.c_str(), monitor, nullptr);
}


void Graphics::updateWindow(Config const & config)
{
  cout << "updateWindow" << endl;
  
  if (config.graphics.fullScreen != isFullScreen)
  {
    auto monitor = config.graphics.fullScreen ?
      glfwGetPrimaryMonitor() : nullptr;
    glfwSetWindowMonitor(mainWindow, monitor, 0, 0, 
      config.graphics.width, config.graphics.height, 
      GLFW_DONT_CARE);
  }
  else
  {
    if (config.graphics.width != diWidth ||
        config.graphics.height != diHeight)
    {
      glfwSetWindowSize(mainWindow, config.graphics.width, config.graphics.height);
      // The resulting size may be different from the 
      // requested size for any number of reasons. So we
      // store the requested size instead of the actual
      // size, so we don't keep reporting diffs when they 
      // don't change. Know what I mean?
      diWidth = config.graphics.width;
      diHeight = config.graphics.height;
    }
  }

  glfwSetWindowTitle(mainWindow, config.general.programName.c_str());
}


void Graphics::destroyWindow()
{
  if (mainWindow != nullptr)
  {
    glfwDestroyWindow(mainWindow);
    mainWindow = nullptr;
    glfwTerminate();
  }
}


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
