#include "engine.h"
#include "utils.h"
#include "configData.h"
#include "jobScheduler.h"

#include <iostream>

using namespace std;
using namespace overground;


constexpr auto AssetBaseDir = "res/assets";
constexpr auto AssetDataBaseDir = "res/assetData";
constexpr auto DefaultStartupFile = "startup";
constexpr auto pathSeparator = "/";


Engine::Engine()
: resMan(this, AssetBaseDir, AssetDataBaseDir)
{
  thId = createLogChannel(
    "main", logTags::dbg, logTags::dev, & cout, & coutMx);
  
  jobMan.allocateWorkers(JobManager::getNumCores() * 2);
}


Engine::~Engine()
{
  try
  {
    jobMan.stopAndJoin();
  }
  catch(const std::exception& e)
  {
    log(thId, fmt::format("Caught an error in ~Engine(): {}", e.what()));
  }
}


void Engine::registerAssetProvider(
      std::string_view assetKind,
      makeAssetFn_t const & fn)
{
  resMan.registerAssetProvider(assetKind, fn);
}


void Engine::init(int argc, char ** argv)
{
  logFn();
  
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
  JobScheduler sched(ScheduleKind::synchronous);
  checkForFileUpdates(sched);
  // latch the config to engine; creates the window, etc.
  checkForAssetUpdates(sched);

  // initial config
  checkForConfigUpdates();
}


void Engine::shutDown()
{
  logFn();

  graphics.shutDown();
}


void Engine::enqueueJob(Job * job)
{
  jobMan.enqueueJob(job);
}


// ------------ process steps

void Engine::loadScene()
{
  logFn();
  
}


void Engine::latchSceneDelta()
{
  logFn();
  
}


void Engine::enterEventLoop()
{
  logFn();

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
    log(thId, logTags::err, "No window was created. Was graphics.reset() called?");
    return;
  }

  while (! glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    iterateGameLoop();
  }

  log(thId, "End of enterEventLoop");

  graphics.waitForGraphicsOps();
}


void Engine::iterateGameLoop()
{
  // logFn();

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

  log(thId, logTags::verb, fmt::format(
    "previousSystemTime:  {}\n"
    "systemTime:          {}\n"
    "frameTime_us:        {}\n"
    "currentTime:         {}",
    previousSystemTime.time_since_epoch().count(),
    systemTime.time_since_epoch().count(),
    frameTime_us.count(),
    currentTime_us.time_since_epoch().count()
    ));
}


void Engine::performScheduledEvents()
{
  JobScheduler sched(ScheduleKind::asynchronous);

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
          checkForFileUpdates(sched);
          break;
        case ScheduledEvents::CheckForAssetUpdates:
          checkForAssetUpdates(sched);
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
      stringstream ss;
      if ((diffs & ConfigData::Deltas::JobManagement) != 0)
        { ss << " JobManagement"; }
      if ((diffs & ConfigData::Deltas::Window) != 0)
        { ss << " Window"; }
      if ((diffs & ConfigData::Deltas::WindowExtents) != 0)
        { ss << " WindowExtents"; }
      if ((diffs & ConfigData::Deltas::VulkanInstance) != 0)
        { ss << " VulkanInstance"; }
      if ((diffs & ConfigData::Deltas::PhysicalDevice) != 0)
        { ss << " PhysicalDevice"; }
      if ((diffs & ConfigData::Deltas::LogicalDevice) != 0)
        { ss << " LogicalDevice"; }
      if ((diffs & ConfigData::Deltas::Swapchain) != 0)
        { ss << " Swapchain"; }

      log(thId, fmt::format(
        "Config loaded:\n"
        "{}\n"
        "Differences required:\n"
        "{}\n",
        config.print(), ss.str()
      ));
    }

    jobMan.setNumEmployedWorkers(
      config.general.numWorkerThreads);

    graphics.reset(& config);

    config.clearDiffs();
  }
}


void Engine::checkForFileUpdates(JobScheduler & sched)
{
  resMan.checkForAnyFileUpdates(sched);
}


void Engine::checkForAssetUpdates(JobScheduler & sched)
{
  resMan.checkForAssetUpdates(sched);
}


void Engine::updateConfig(ConfigData const & newConfig)
{
  logFn();

  {
    lock_guard<mutex> lock(mx_config);
    config.integrate(newConfig);
  }
}


unique_ptr<Asset> Engine::makeAsset(
  std::string_view assetName,
  FileReference * assetDescFile, 
  humon::HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor
)
{
  return resMan.makeAsset(
    assetName, assetDescFile, descFromFile, cache, compress, monitor);
}
