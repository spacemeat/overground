#include <iostream>
#include "engine.h"
#include "utils.h"
#include "jobScheduler.h"
#include "assemblyManager.h"
#include "config-gen.h"
#include "objectTree.h"


using namespace std;
using namespace overground;
using namespace assembly;


constexpr auto AssetBaseDir = "res/assets";
constexpr auto AssetDataBaseDir = "res/assetData";
constexpr auto DefaultStartupFile = "startup";
constexpr auto pathSeparator = "/";


Engine::Engine()
{
  thId = createLogChannel(
    "main", logTags::dbg, logTags::macro, & cout, & coutMx);
  
  jobMan->allocateWorkers(JobManager::getNumCores() * 2);
  //jobMan->setFramePlan(& framePlan);
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


void Engine::init(int argc, char ** argv)
{
  logFn();
  
  startTime = chrono::high_resolution_clock::now();
  systemTime = startTime;
  currentTime_us = engineTimePoint {};

//  resMan.gatherAssetsFromFile("config.hu");
//  resMan.addAssetDescFile(DefaultStartupFile);

  // ScheduledEvents::CheckForFileUpdates
  eventPeriods.push_back(chrono::milliseconds{1000});
  lastEventTimes.push_back(currentTime_us);
  // ScheduledEvents::CheckForAssetUpdates
  eventPeriods.push_back(chrono::milliseconds{1000});
  lastEventTimes.push_back(currentTime_us + chrono::milliseconds{500});

//  JobScheduler sched(ScheduleKind::synchronous);
//  checkForFileUpdates(sched);
  // latch the config to engine; creates the window, etc.
//  checkForAssetUpdates(sched);
  // initial config
//  checkForDataUpdates();

}


void Engine::shutDown()
{
  logFn();

  graphics.shutDown();
}


// ------------ process steps


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

    runLoopIteration();
  }

  log(thId, "End of enterEventLoop");

  // shut it down!
  jobMan->stopAndJoin();

  // wait for the GPU to finish everything.
  graphics.waitForGraphicsOps();
}


void Engine::runLoopIteration()
{
  runFrameMaintenance();

}


// Phase job for frameMaintenance phases
void Engine::runFrameMaintenance()
{
  logFn();

  log(thId, logTags::phase, fmt::format("{}FMP{}", ansi::lightRed, ansi::off));

  updateTimer();

  performScheduledEvents();
  // ? checkForAssemblyUpdates(sched);
}


void Engine::updateTimer()
{
  previousSystemTime = systemTime;
  systemTime = chrono::high_resolution_clock::now();

  frameTime_us = systemTime - previousSystemTime;
  currentTime_us += frameTime_us;

  log(thId, logTags::time, fmt::format("\n"
    "systemTime:          {}\n"
    "frameTime_us:        {}\n"
    "currentTime:         {}",
    systemTime.time_since_epoch().count(),
    frameTime_us.count(),
    currentTime_us.time_since_epoch().count()
    ));
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
        case ScheduledEvents::checkForUpdatedFiles:
          checkForUpdatedFiles();
          break;
      }
    }
  }
}


void Engine::checkForUpdatedFiles()
{
  assemblyMan->checkForUpdatedFiles();
}


void Engine::checkForUpdatedAssembly()
{
  auto & currAsm = assemblyMan->getCurrentAssembly();
  auto & workAsm = assemblyMan->getWorkingAssembly();
  auto assemblyDiffs = assemblyMan->checkForUpdatedAssembly();
  if (assemblyDiffs.has_value())
  {
    // If we change which config we're using, we need to modify the configsDiffs to contain the diffs between the current config and the new one. So if user changes both the config blocks and the usingConfig key, we will compare correctly.
    if ((assemblyDiffs->diffs & assemblyMembers_e::usingConfig) != 0)
    {
      auto & currConfig = currAsm.configs[currAsm.usingConfig];
      auto & workConfig = workAsm.configs[workAsm.usingConfig];
      config::configDiffs_t configDiffs;
      if (doPodsDiffer(currConfig, workConfig, configDiffs))
      {
        // Replace the configDiffs_t that matches, or add one if there isn't one. We use workAsm.usingConfig as the name so that when we look it up later, it'll match against workAsm.usingConfig which is all we care about when responding to changes.
        auto it = std::find_if(
          assemblyDiffs->configsDiffs.begin(), 
          assemblyDiffs->configsDiffs.end(), 
          [&](auto & elem) 
            { return elem.first() == workAsm.usingConfig; });
        
        if (it != assemblyDiffs->configsDiffs.end())
        {
          it->second = configDiffs;
        }
        else
        {
          assemblyDiffs->configsDiffs.push_back({workAsm.usingConfig, move(configDiffs)});
        }
      }
    }

    // We can be confident due to the above that assemblyDiffs->configsDiffs[workAsm.usingConfig] is the changeset for the config we're on to the config we're ultimately going to match (workAsm.configs[workAsm.usingConfig]).
    auto it = std::find_if(
      assemblyDiffs->configsDiffs.begin(), 
      assemblyDiffs->configsDiffs.end(), 
      [&](auto & elem) 
        { return elem.first() == workAsm.usingConfig; });
    if (it != assemblyDiffs->configsDiffs.end())
    {
      auto & workConfig = workAsm.configs[workAsm.usingConfig];

      // There are, in fact, config changes to address.
      auto & configDiffs = it->second;

      updateConfig(workConfig, configDiffs);
    }

    // If the tableau group we're using is different, or if any tableau has differences, we create a new tableau graph from the working assembly. It describes the buffer orderings (without sizes) and how the compiled assets are stored to cache files. Later we'll check for asset changes or out-of-date asset files or certain config updates, and recompute the size requirements to get the full buffer size and copy or compile the targets.

    if ((assemblyDiffs->diffs & assemblyMembers_e::usingTableauGroup) != 0 ||
        (assemblyDiffs->diffs & assemblyMembers_e::tableaux) != 0)
    {
      auto tree = ObjectTree { workAsm.tableaux.vect() };


      //  for each asset referenced in tree,
      //    if asset_ts changed or
      //        asset file reports having changed or
      //        certain config has changed,
      //      asset.needsToBeCompiled = true
      //      asset.sz = asset.computeBufferSize()
      //      asset.offset = prevAsset.offset + prevAsset.sz + padding for alignment
      //  newBufferSize = lastAsset.offset + lastAsset.sz

      // NOTE: We shouldn't use a staging buffer if we're in a combined memory system (AGP). Like, say, my dev laptop. Meaning, when we create the sram buffer, we're also making the video buffer in some cases.
      //  if newBufferSize > prevBufferSize
      //    newBufferSize *= 1.25              // hysteresis
      //    make new sram buffer[newBufferSize]
      //    destBuffer = new buffer
      //  else
      //    destBuffer = old buffer
      //  for each asset referenced in tree,
      //    assetDest = destBufer + asset.offset
      //    if asset.needsToBeCompiled,
      //      asset.compile(assetDest)
      //    else if asset.offset chnged or destBuffer != srcBuffer,
      //      copy asset from assetSrc
      //  
      //  if any asset compiled or moved,
      //    if we have a buffer already,
      //      lock buffer
      //      for each asset that is newly compiled or moved,
      //        copy asset data to buffer
      //      unlock buffer
      //      for each asset that is newly compiled or moved,
      //        adjust vulkan resource
      //    else
      //      create new video buffer
      //      for each asset,
      //        copy asset data to buffer
      //        create vulkan resource for it

    }
  }
}


// Here, config must match what configDiffs claims. In general, it's always workAsm.configs[workAsm.usingConfig], and we're just passing it around so we don't have to find it again and again.
void Engine::updateConfig(config::config_t & config, 
  config::configDiffs_t & configDiffs)
{
  logFn();

  auto & workAsm = assemblyMan->getWorkingAssembly();
  auto & config = workAsm.configs[workAsm.usingConfig];

  log(thId, logTags::asset, fmt::format(
    "new config:\n"
    "{}\n", print(workAsm)));

  if ((configDiffs.diffs & config::configMembers_e::general) != 0)
  {
    auto & generalDiffs = configDiffs.general;

    if ((generalDiffs.diffs & config::generalMembers_e::programName) != 0)
    {
      setProgramName(config.general.programName);
    }

    if ((generalDiffs.diffs & config::generalMembers_e::version) != 0)
    {
      setProgramVersion(config.general.version);
    }

    if ((generalDiffs.diffs & config::generalMembers_e::numWorkerThreads) != 0)
    {
      jobMan->setNumEmployedWorkers(config.general.numWorkerThreads);
    }
  }

  if ((configDiffs.diffs & config::configMembers_e::graphics) != 0)
  {
    auto & graphicsDiffs = configDiffs.graphics;

    graphics.updateConfig(graphicsDiffs);
  }
}


void Engine::setProgramName(string_view name)
{
  // TODO: stuff
}

void Engine::setProgramVersion(version_t name)
{
  // TODO: stuff
}
