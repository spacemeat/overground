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
    "main", logTags::dbg, logTags::micro, & cout, & coutMx);
  
  jobMan->allocateWorkers(JobManager::getNumCores() * 2);
  jobMan->setFramePlan(& framePlan);
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
    // TODO: Check window size updates and inform graphics
  }

  log(thId, "End of enterEventLoop");

  // just straight-up stop working. All workers will finish their jobs though, so this just tells them not to start new ones (and does not block).
//  jobMan->setNumEmployedWorkers(0);
  jobMan->stopAndJoin();

  // wait for the GPU to finish everything.
  graphics.waitForGraphicsOps();
}


// Phase job for frameMaintenance phases
void Engine::runFrameMaintenance()
{
  logFn();

  log(thId, logTags::phase, fmt::format("{}FMP{}", ansi::lightRed, ansi::off));

  updateTimer();

  JobScheduler sched(ScheduleKind::asynchronous);

  performScheduledEvents(sched);
  checkForAssetUpdates(sched);

  if (updatedObjectKinds != DataObjectKindFlags::none)
  { 
    framePlan.postJob("graphicsStructure", 
      makeFnJob("checkForDataUpdates", [&]
        { checkForDataUpdates(); }
      ), false);
  }
}


void Engine::updateTimer()
{
  previousSystemTime = systemTime;
  systemTime = chrono::high_resolution_clock::now();

  frameTime_us = systemTime - previousSystemTime;
  currentTime_us += frameTime_us;

  log(thId, logTags::dbg, fmt::format("\n"
    "systemTime:          {}\n"
    "frameTime_us:        {}\n"
    "currentTime:         {}",
    systemTime.time_since_epoch().count(),
    frameTime_us.count(),
    currentTime_us.time_since_epoch().count()
    ));
}


void Engine::performScheduledEvents(JobScheduler & sched)
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


void Engine::checkForDataUpdates()
{
  if (updatedObjectKinds == DataObjectKindFlags::none)
    { return; }
  
  log(thId, fmt::format("{}Engine::checkForDataUpdates(){} has updates.", ansi::lightGreen, ansi::off));

  checkForConfigUpdates();
  graphics.checkForDataUpdates();
  checkForFramePlanUpdates();

  jobMan->setNumEmployedWorkers(
    config.general.numWorkerThreads);


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
}


void Engine::checkForFramePlanUpdates()
{
  logFn();

  if ((updatedObjectKinds & 
       DataObjectKindFlags::framePlan) == 0)
    { return; }
  
  framePlan.update(framePlanDesc);

  // assign initial jobs to each phase
  framePlan.forEachPhase([&](FramePhase & phase)
  {
    switch(phase.getKind())
    {
    case FramePhaseKinds::frameMaintenance:
      assignSpecialPhaseJobs(phase);
      break;
    case FramePhaseKinds::graphicsStructure:
    case FramePhaseKinds::acquireImage:
    case FramePhaseKinds::beginComputePass:
    case FramePhaseKinds::beginRenderPass:
    case FramePhaseKinds::beginSubpass:
    case FramePhaseKinds::endComputePass:
    case FramePhaseKinds::endRenderPass:
    case FramePhaseKinds::submitCommands:
    case FramePhaseKinds::present:
      graphics.assignSpecialPhaseJobs(phase);
      break;
    case FramePhaseKinds::barrierJobQueue:
    case FramePhaseKinds::nonBarrierJobQueue:
    default:
      break;
    }
  });

  jobMan->setNextPhaseIdx(0);
}


void Engine::assignSpecialPhaseJobs(FramePhase & phase)
{
  switch(phase.getKind())
  {
  case FramePhaseKinds::frameMaintenance:
    phase.setBarrierJob(makeFnJob("frameMaintenancePhase", [this]
      { runFrameMaintenance(); }));
    break;
  default:
    break;
  }
}


void Engine::updateConfig(config_t newConfig)
{
  logFn();

  log(thId, logTags::asset, fmt::format(
    "new config:\n"
    "{}\n", print(newConfig)
  ));

  configDiffs = integrate(config, newConfig);
  config = move(newConfig);
  updatedObjectKinds |= DataObjectKindFlags::config;
}


void Engine::updateFramePlan(framePlan_t newFramePlan)
{
  logFn();

  log(thId, logTags::asset, fmt::format(
    "new framePlan:\n"
    "{}\n", print(newFramePlan)
  ));

  framePlanDesc = move(newFramePlan);
  framePlanUpdated = true;
  updatedObjectKinds |= DataObjectKindFlags::framePlan;
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

