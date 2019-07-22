#include "graphics.h"

using namespace std;
using namespace overground;


void Graphics::createWindow()
{
  logFn();

  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  isFullScreen = config->graphics.fullScreen;
  diWidth = config->graphics.width;
  diHeight = config->graphics.height;

  auto monitor = isFullScreen ? glfwGetPrimaryMonitor() : nullptr;

  mainWindow = glfwCreateWindow(diWidth, diHeight, config->general.programName.c_str(), monitor, nullptr);
}


void Graphics::updateWindow()
{
  logFn();
  
  if (config->graphics.fullScreen != isFullScreen)
  {
    auto monitor = config->graphics.fullScreen ?
      glfwGetPrimaryMonitor() : nullptr;
    glfwSetWindowMonitor(mainWindow, monitor, 0, 0, 
      config->graphics.width, config->graphics.height, 
      GLFW_DONT_CARE);
  }
  else
  {
    if (config->graphics.width != diWidth ||
        config->graphics.height != diHeight)
    {
      glfwSetWindowSize(mainWindow, config->graphics.width, config->graphics.height);
      // The resulting size may be different from the 
      // requested size for any number of reasons. So we
      // store the requested size instead of the actual
      // size, so we don't keep reporting diffs when they 
      // don't change. Know what I mean?
      diWidth = config->graphics.width;
      diHeight = config->graphics.height;
    }
  }

  glfwSetWindowTitle(mainWindow, config->general.programName.c_str());
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
