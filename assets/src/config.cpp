#include "config.h"
#include "fileRegistry.h"

using namespace std;
using namespace humon;
using namespace overground;


void Config::setFileInfo(FileReference * newFileInfo)
{
  fileInfo = newFileInfo;
  fileInfo->addRef();
}


void Config::loadFromHumon(HuNode const & src)
{
  if (src % "general")
  {
    auto & generalSrc = src / "general";
    if (generalSrc % "programName")
    {
      general.programName = string(generalSrc / "programName");
    }

    if (generalSrc % "version")
    {
      auto & ver = generalSrc / "version";
      general.version = { 
        ver / 0,
        ver / 1,
        ver / 2
      };
    }

    if (generalSrc % "numWorkerThreads")
      { general.numWorkerThreads = generalSrc / "numWorkerThreads"; }
  }

  if (src % "graphics")
  {
    graphics.isConfigured = true;

    auto & graphicsSrc = src / "graphics";
    if (graphicsSrc % "fullScreen")
      { graphics.fullScreen = graphicsSrc / "fullScreen"; }

    if (graphicsSrc % "width")
      { graphics.width = graphicsSrc / "width"; }

    if (graphicsSrc % "height")
      { graphics.height = graphicsSrc / "height"; }
    
    if (graphicsSrc % "vulkanValidationEnabled")
      { graphics.vulkanValidationEnabled = graphicsSrc / "vulkanValidationEnabled"; }

    if (graphicsSrc % "vulkanValidationLayers")
    {
      auto & listSrc = graphicsSrc / "vulkanValidationLayers";
      for (size_t i = 0; i < listSrc.size(); ++i)
        { graphics.vulkanValidationLayers.push_back(listSrc / i); }
    }

    if (graphicsSrc % "vulkanValidationReports")
    {
      auto & listSrc = graphicsSrc / "vulkanValidationReports";
      for (size_t i = 0; i < listSrc.size(); ++i)
        { graphics.vulkanValidationReports.push_back(listSrc / i); }
    }

    if (graphicsSrc % "vulkanExtensions")
    {
      auto & listSrc = graphicsSrc / "vulkanExtensions";
      for (size_t i = 0; i < listSrc.size(); ++i)
        { graphics.vulkanExtensions.push_back(listSrc / i); }
    }

    if (graphicsSrc % "deviceExtensions")
    {
      auto & listSrc = graphicsSrc / "deviceExtensions";
      for (size_t i = 0; i < listSrc.size(); ++i)
        { graphics.deviceExtensions.push_back(listSrc / i); }
    }

    if (graphicsSrc % "minGraphicsQueues")
      { graphics.minGraphicsQueues = graphicsSrc / "minGraphicsQueues"; }

    if (graphicsSrc % "desiredGraphicsQueues")
      { graphics.desiredGraphicsQueues = graphicsSrc / 
        "desiredGraphicsQueues"; }

    if (graphicsSrc % "minComputeQueues")
      { graphics.minComputeQueues = graphicsSrc / "minComputeQueues"; }

    if (graphicsSrc % "desiredComputeQueues")
      { graphics.desiredComputeQueues = graphicsSrc / 
        "desiredComputeQueues"; }

    if (graphicsSrc % "minTransferQueues")
      { graphics.minTransferQueues = graphicsSrc / "minTransferQueues"; }

    if (graphicsSrc % "desiredTransferQueues")
      { graphics.desiredTransferQueues = graphicsSrc / 
        "desiredTransferQueues"; }
  }
}

template <class T>
Config::Deltas set(T & lhs, T const & rhs, Config::Deltas kind)
{
  if (lhs != rhs)
  {
    lhs = rhs;
    return kind;
  }
  return Config::Deltas::None;
}

void Config::integrate(Config const & rhs)
{
  Config::Deltas deltas = Config::Deltas::None;

  deltas |= set(general.programName, rhs.general.programName, Config::Deltas::Window);
  
  deltas |= set(general.numWorkerThreads, rhs.general.numWorkerThreads, Config::Deltas::JobManagement);

  deltas |= set(graphics.isConfigured, rhs.graphics.isConfigured, Config::Deltas::VulkanInstance);

  deltas |= set(graphics.headless, rhs.graphics.headless, Config::Deltas::Window | Config::Deltas::VulkanInstance);
  
  deltas |= set(graphics.fullScreen, rhs.graphics.fullScreen, Config::Deltas::Window);
  
  deltas |= set(graphics.width, rhs.graphics.width, Config::Deltas::Window);
  
  deltas |= set(graphics.height, rhs.graphics.height, Config::Deltas::Window);

  deltas |= set(graphics.vulkanValidationEnabled, rhs.graphics.vulkanValidationEnabled, Config::Deltas::VulkanInstance);
  
  deltas |= set(graphics.vulkanValidationLayers, rhs.graphics.vulkanValidationLayers, Config::Deltas::VulkanInstance);

  deltas |= set(graphics.vulkanValidationReports, rhs.graphics.vulkanValidationReports, Config::Deltas::VulkanInstance);

  deltas |= set(graphics.vulkanExtensions, rhs.graphics.vulkanExtensions, Config::Deltas::VulkanInstance);

  deltas |= set(graphics.deviceExtensions, rhs.graphics.deviceExtensions, Config::Deltas::VulkanInstance);

  deltas |= set(graphics.minGraphicsQueues, rhs.graphics.minGraphicsQueues, Config::Deltas::PhysicalDevice);

  deltas |= set(graphics.desiredGraphicsQueues, rhs.graphics.desiredGraphicsQueues, Config::Deltas::PhysicalDevice);

  deltas |= set(graphics.minComputeQueues, rhs.graphics.minComputeQueues, Config::Deltas::PhysicalDevice);

  deltas |= set(graphics.desiredComputeQueues, rhs.graphics.desiredComputeQueues, Config::Deltas::PhysicalDevice);

  deltas |= set(graphics.minTransferQueues, rhs.graphics.minTransferQueues, Config::Deltas::PhysicalDevice);
  
  deltas |= set(graphics.desiredTransferQueues, rhs.graphics.desiredTransferQueues, Config::Deltas::PhysicalDevice);

  lastDiffs = rhs.lastDiffs | deltas;
}


void Config::print(std::ostream & sout) const
{
  sout << "Config:" << endl
       << "  general:" << endl
       << "    numWorkerThreads: " << general.numWorkerThreads << endl
       << "  graphics:" << endl
       << "    headless: " << (graphics.headless ? "true" : "false") << endl
       << "    fullScreen: " << (graphics.fullScreen ? "true" : "false") << endl
       << "    width: " << graphics.width << endl
       << "    height " << graphics.height << endl
       << "    vulkanValidationEnabled: " << (graphics.vulkanValidationEnabled ? "true": "false") << endl
       << "    vulkanValidationLayers: ";
  for (auto & ext : graphics.vulkanValidationLayers)
    { sout << " " << ext; }
  sout << endl
       << "    vulkanValidationReports: ";
  for (auto & ext : graphics.vulkanValidationReports)
    { sout << " " << ext; }
  sout << endl
       << "    vulkanExtensions: ";
  for (auto & ext : graphics.vulkanExtensions)
    { sout << " " << ext; }
  sout << endl
       << "    deviceExtensions: ";
  for (auto & ext : graphics.deviceExtensions)
    { sout << " " << ext; }

  sout << "    minGraphicsQueues " << graphics.minGraphicsQueues << endl
       << "    desiredGraphicsQueues " << graphics.desiredGraphicsQueues << endl
       << "    minComputeQueues " << graphics.minComputeQueues << endl
       << "    desiredComputeQueues " << graphics.desiredComputeQueues << endl
       << "    minTransferQueues " << graphics.minTransferQueues << endl
       << "    desiredTransferQueues " << graphics.desiredTransferQueues << endl
       << endl;
}


std::ostream & overground::operator << (std::ostream & stream, Config const & rhs)
{
  rhs.print(stream);
  return stream;
}
