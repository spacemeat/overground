#include "engine.h"
#include "updateJobs.h"
#include "utils.h"
#include "configData.h"

#include <iostream>

using namespace std;
using namespace overground;


constexpr auto AssetBaseDir = "res/assets";
constexpr auto AssetDataBaseDir = "res/assetData";
constexpr auto DefaultStartupFile = "startup";
constexpr auto pathSeparator = "/";


Engine::Engine()
: resMan(this, & jobManager, AssetBaseDir, AssetDataBaseDir)
{  
}


Engine::~Engine()
{
  try
  {
    jobManager.stopAndJoin();
  }
  catch(const std::exception& e)
  {
    sout {} << "~Engine() threw: " << e.what() << endl;
  }
}


void Engine::registerAssetProvider(
      std::string const & assetKind,
      makeAssetFn_t const & fn)
{
  resMan.registerAssetProvider(assetKind, fn);
}


void Engine::init(int argc, char ** argv)
{
  sout {} << "Engine::init()" << endl;
  
  startTime = chrono::high_resolution_clock::now();
  systemTime = startTime;
  currentTime_us = engineTimePoint {};

//  resMan.gatherAssetsFromFile("config.hu");
  resMan.addAssetDescFile(DefaultStartupFile);

  // ScheduledEvents::CheckForFileUpdates
  eventPeriods.push_back(chrono::milliseconds{1000});
  lastEventTimes.push_back(currentTime_us);
  // ScheduledEvents::CheckForAssetUpdates
  eventPeriods.push_back(chrono::milliseconds{1000});
  lastEventTimes.push_back(currentTime_us + chrono::milliseconds{500});

  // load up the config file
  checkForFileUpdates(true);
  // latch the config to engine; creates the window, etc.
  checkForAssetUpdates(true);

  // initial config
  checkForConfigUpdates();


  // let's not stand on ceremony. There will be zero workers at the moment, but set it to start once we populate.
  jobManager.startWorkers();
}


void Engine::shutDown()
{
  graphics.shutDown();
}


void Engine::enqueueJob(Job * job)
{
  jobManager.enqueueJob(job);
}


// ------------ process steps

void Engine::loadScene()
{
  
}


void Engine::latchSceneDelta()
{
  
}


void Engine::enterEventLoop()
{
  sout {} << "Engine::enterEventLoop()" << endl;

  // TODO: temperorariry. kills the works after a bit. Trying to manage a runaway process. Might need to get more aggressive.
  /* 
  limiter = new thread([this]
  {
    this_thread::sleep_for(3000ms);
    glfwSetWindowShouldClose(graphics.getMainWindow(), true);
  });*/

  auto window = graphics.getMainWindow();
  if (window == nullptr)
  {
    sout {} << "No window was created. Was graphics.reset() called?" << endl;
    return;
  }

  while( ! glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    iterateGameLoop();
  }

  sout {} << "End of enterEventLoop" << endl;

  // g.waitForGraphicsOps();
}


void Engine::iterateGameLoop()
{
  //sout {} << "Engine::iterateGameLoop()" << endl;

  updateTimer();
  graphics.presentFrame();
  graphics.drawFrame();  

  checkForConfigUpdates();
  performScheduledEvents();
  // animate, do other CPU-intensive stuff here
}


void Engine::updateTimer()
{
  previousSystemTime = systemTime;
  systemTime = chrono::high_resolution_clock::now();

  frameTime_us = systemTime - previousSystemTime;
  currentTime_us += frameTime_us;

  /*
  sout {} << "previousSystemTime: " << previousSystemTime.time_since_epoch().count() << endl
          << "systemTime:         " << systemTime.time_since_epoch().count() << endl
          << "frameTime_us:       " << frameTime_us.count() << endl
          << "currentTime:        " << currentTime_us.time_since_epoch().count() << endl;
  */
}


void Engine::performScheduledEvents()
{
  // perform scheduled actions if any
  for (size_t i = 0; i < eventPeriods.size(); ++i)
  {
    engineTimeDuration since = currentTime_us - lastEventTimes[i];
    if (since >= eventPeriods[i])
    {
      lastEventTimes[i] += eventPeriods[i];

      switch ((ScheduledEvents) i)
      {
        case ScheduledEvents::CheckForFileUpdates:
          checkForFileUpdates(false);
          break;
        case ScheduledEvents::CheckForAssetUpdates:
          checkForAssetUpdates(false);
          break;
      }
    }
  }
}


void Engine::checkForConfigUpdates()
{
  ConfigData::Deltas diffs = config.getDiffs();

  if (diffs != ConfigData::Deltas::None)
  {
    lock_guard<mutex> lock(mx_config);

    {
      sout so {};
      so  << "Config loaded:" << endl << config << endl
          << "Differences required: ";
      if ((diffs & ConfigData::Deltas::JobManagement) == 
          ConfigData::Deltas::JobManagement)
        { so << " JobManagement"; }
      if ((diffs & ConfigData::Deltas::Window) == 
          ConfigData::Deltas::Window)
        { so << " Window"; }
      if ((diffs & ConfigData::Deltas::VulkanInstance) == 
          ConfigData::Deltas::VulkanInstance)
        { so << " VulkanInstance"; }
      if ((diffs & ConfigData::Deltas::PhysicalDevice) == 
          ConfigData::Deltas::PhysicalDevice)
        { so << " PhysicalDevice"; }
      if ((diffs & ConfigData::Deltas::LogicalDevice) == 
          ConfigData::Deltas::LogicalDevice)
        { so << " LogicalDevice"; }
      so << endl;
    }

    graphics.reset(& config);

    config.clearDiffs();
  }

  jobManager.setNumWorkers(config.general.numWorkerThreads);
}


void Engine::checkForFileUpdates(bool synchronous)
{
  //sout {} << "Engine::checkForFileUpdates()" << endl;

  resMan.checkForAnyFileUpdates(synchronous);
}


void Engine::checkForAssetUpdates(bool synchronous)
{
  //sout {} << "Engine::checkForAssetUpdates()" << endl;

  resMan.checkForAssetUpdates(synchronous);
}


void Engine::updateConfig(ConfigData const & newConfig)
{
  sout {} << "Engine::updateConfig()" << endl;

  {
    lock_guard<mutex> lock(mx_config);
    config.integrate(newConfig);
  }
}


unique_ptr<Asset> Engine::makeAsset(
  std::string const & assetName,
  FileReference * assetDescFile, 
  humon::HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor
)
{
  return resMan.makeAsset(
    assetName, assetDescFile, descFromFile, cache, compress, monitor);
}



