#include "engine.h"
#include "graphics.h"

using namespace std;
using namespace overground;


void Graphics::createWindow()
{
  logFn();

  auto const & config = engine->getConfig();

  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  isFullScreen = config.graphics.fullScreen;
  diWidth = config.graphics.width;
  diHeight = config.graphics.height;

  auto monitor = isFullScreen ? glfwGetPrimaryMonitor() : nullptr;

  mainWindow = glfwCreateWindow(diWidth, diHeight, config.general.programName.c_str(), monitor, nullptr);
}


void Graphics::updateWindow()
{
  logFn();
  
  auto const & config = engine->getConfig();

  if (config.graphics.fullScreen != isFullScreen)
  {
    if (surface)
      { destroySurface(); }

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
      if (surface)
        { destroySurface(); }
        
      log(thId, fmt::format("Graphics::updaetWindow(): setting window size: {} x {}", config.graphics.width, config.graphics.height));
      glfwSetWindowSize(mainWindow, config.graphics.width, config.graphics.height);
    
      this_thread::sleep_for(.1s);
      int w, h;
      glfwGetWindowSize(mainWindow, &w, &h);
      log(thId, fmt::format("Graphics::updaetWindow(): window reports: {} x {}", w, h)); 

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
  logFn();
  
  if (mainWindow != nullptr)
  {
    glfwDestroyWindow(mainWindow);
    mainWindow = nullptr;
    glfwTerminate();
  }
}
