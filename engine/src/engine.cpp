#include "engine.h"
#include "utils.h"
#include "configAsset.h"
#include "jobScheduler.h"
#include "framePlan.h"

#include <iostream>

using namespace std;
using namespace overground;


constexpr auto AssetBaseDir = "res/assets";
constexpr auto AssetDataBaseDir = "res/assetData";
constexpr auto DefaultStartupFile = "startup";
constexpr auto pathSeparator = "/";


Engine::Engine()
: resMan(AssetBaseDir, AssetDataBaseDir)
{
  thId = createLogChannel(
    "main", logTags::dbg, logTags::dev, & cout, & coutMx);
  
  jobMan->allocateWorkers(JobManager::getNumCores() * 2);
}


Engine::~Engine()
{
  try
  {
    jobMan->stopAndJoin();
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
  checkForDataUpdates();
}


void Engine::shutDown()
{
  logFn();

  graphics.shutDown();
}


void Engine::enqueueJob(Job * job)
{
  jobMan->enqueueJob(job);
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
    iterateLoop();
  }

  log(thId, "End of enterEventLoop");

  graphics.waitForGraphicsOps();
}


void Engine::iterateLoop()
{
  // logFn();

  updateTimer();
  graphics.presentFrame();
  graphics.drawFrame();

  JobScheduler sched(ScheduleKind::asynchronous);
  checkForDataUpdates();
  checkForAssetUpdates(sched);
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
      }
    }
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


void Engine::updateConfig(config_t newConfig)
{
  logFn();

  log(thId, fmt::format(
    "new config::\n"
    "{}\n", print(newConfig)
  ));

  configDiffs = integrate(config, newConfig);
  config = move(newConfig);
  updatedObjectKinds |= DataObjectKindFlags::config;
}


void Engine::updateFramePlan(framePlan_t newFramePlan)
{
  logFn();

  log(thId, fmt::format(
    "new framePlan::\n"
    "{}\n", print(newFramePlan)
  ));

  framePlanDesc = move(newFramePlan);
  framePlanUpdated = true;
  updatedObjectKinds |= DataObjectKindFlags::framePlan;
}


void Engine::checkForDataUpdates()
{
  if (updatedObjectKinds == DataObjectKindFlags::none)
    { return; }
  
  log(thId, fmt::format("{}Engine::checkForDataUpdates(){} has updates.", ansi::lightGreen, ansi::off));

  checkForConfigUpdates();
  graphics.checkForDataUpdates();
  checkForFramePlanUpdates();

  configDiffs = Config::Deltas::None;
  updatedObjectKinds = DataObjectKindFlags::none;
}


void Engine::checkForConfigUpdates()
{
  logFn();

  if ((updatedObjectKinds & 
       DataObjectKindFlags::config) == 0)
    { return; }

  if (configDiffs == Config::Deltas::None)
    { return; }
  
  // TODO: Run this at top of frame. Otherwise we're jamming a bureaucratic fixed value into the subtle play of worker activations and pink slips.
  jobMan->setNumEmployedWorkers(
    config.general.numWorkerThreads);
}


void Engine::checkForFramePlanUpdates()
{
  logFn();

  if ((updatedObjectKinds & 
       DataObjectKindFlags::framePlan) == 0)
    { return; }
  
  framePlan.update(framePlanDesc);
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

