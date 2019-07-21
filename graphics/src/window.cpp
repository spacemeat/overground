#include "graphics.h"

using namespace std;
using namespace overground;


void Graphics::createWindow()
{
  logFn();

  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  isFullScreen = config->config.graphics.fullScreen;
  diWidth = config->config.graphics.width;
  diHeight = config->config.graphics.height;

  auto monitor = isFullScreen ? glfwGetPrimaryMonitor() : nullptr;

  mainWindow = glfwCreateWindow(diWidth, diHeight, config->config.general.programName.c_str(), monitor, nullptr);
}


void Graphics::updateWindow()
{
  logFn();
  
  if (config->config.graphics.fullScreen != isFullScreen)
  {
    auto monitor = config->config.graphics.fullScreen ?
      glfwGetPrimaryMonitor() : nullptr;
    glfwSetWindowMonitor(mainWindow, monitor, 0, 0, 
      config->config.graphics.width, config->config.graphics.height, 
      GLFW_DONT_CARE);
  }
  else
  {
    if (config->config.graphics.width != diWidth ||
        config->config.graphics.height != diHeight)
    {
      glfwSetWindowSize(mainWindow, config->config.graphics.width, config->config.graphics.height);
      // The resulting size may be different from the 
      // requested size for any number of reasons. So we
      // store the requested size instead of the actual
      // size, so we don't keep reporting diffs when they 
      // don't change. Know what I mean?
      diWidth = config->config.graphics.width;
      diHeight = config->config.graphics.height;
    }
  }

  glfwSetWindowTitle(mainWindow, config->config.general.programName.c_str());
}


void Graphics::destroyWindow()
{
  logFn();
  
  if (mainWindow != nullptr)
  {
    glfwDestroyWindow(mainWindow);
    mainWindow = nullptr;
    glfwTerminate();
  }
}
