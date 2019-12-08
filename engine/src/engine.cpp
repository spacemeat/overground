#include <iostream>
#include <numeric>
#include <unordered_set>
#include "engine.h"
#include "utils.h"
#include "jobScheduler.h"
#include "assemblyManager.h"
#include "config-gen.h"
#include "objectTree.h"
#include "memoryPlan.h"


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

  graphics->shutDown();
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

  auto window = graphics->getMainWindow();
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
  graphics->waitForGraphicsOps();
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


void Engine::checkForChanges()
{
  if (assemblyMan->didAssemblyDescsChange())
  {
    buildWorkingAssemblyObjects();
  }

  if (assetMan->isCacheUpToDate())
  {
    if (configChanged)
    {
      handleConfigChanges();
    }

    if (materialsChanged)
    {
      materialMan->buildWorkPalette();
    }

    if (adbChanged || memoryPlanChanged || objectTreeChanged || materialsChanged)
    {
      graphics->syncMemory();
    }

    if (...)
    {
    }

    configChanged = false;
    adbChanged = false;
    memoryPlanChanged = false;
    objectTreeChanged = false;
    materialsChanged = false;

    blessWorkingSets();
  }
}


void Engine::buildWorkingAssemblyObjects()
{
  auto & currAsm = assemblyMan->getCurrAssemblyDesc();
  auto & workAsm = assemblyMan->getWorkAssemblyDesc();
  auto & assemblyDiffs = assemblyMan->getWorkAssemblyDescDiffs();
  if ((assemblyDiffs.diffs & assembly::assemblyMembers_e::configs) != 0 ||
      (assemblyDiffs.diffs & assembly::assemblyMembers_e::usingConfig) != 0)
    { computeConfigDiffs(currAsm, workAsm, assemblyDiffs); }

  if ((assemblyDiffs.diffs & assembly::assemblyMembers_e::memoryPlans) != 0 ||
      (assemblyDiffs.diffs & assembly::assemblyMembers_e::usingMemoryPlan) != 0)
    { computeMemoryPlanDiffs(currAsm, workAsm, assemblyDiffs); }

  if ((assemblyDiffs.diffs & assembly::assemblyMembers_e::renderPlans) != 0)
    { computeRenderPlanDiffs(currAsm, workAsm, assemblyDiffs); }

  if ((assemblyDiffs.diffs & assembly::assemblyMembers_e::assets) != 0)
    { computeAssetDiffs(currAsm, workAsm, assemblyDiffs); }

  if ((assemblyDiffs.diffs & assembly::assemblyMembers_e::materials) != 0)
    { computeMaterialDiffs(currAsm, workAsm, assemblyDiffs); }

  if ((assemblyDiffs.diffs & assembly::assemblyMembers_e::usingTableauGroup) != 0 ||
      (assemblyDiffs.diffs & assembly::assemblyMembers_e::tableauGroups) != 0 ||
      (assemblyDiffs.diffs & assembly::assemblyMembers_e::tableaux) != 0)
    { computeTableauDiffs(currAsm, workAsm, assemblyDiffs); }
}


void Engine::computeConfigDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs)
{
  // If we change which config we're using, we need to modify the configsDiffs to contain the diffs between the current config and the new one. So if user changes both the config blocks and the usingConfig key, we will compare correctly.
  if ((assemblyDiffs.diffs & assemblyMembers_e::usingConfig) != 0)
  {
    auto & currConfig = currAsm.configs[currAsm.usingConfig];
    auto & workConfig = workAsm.configs[workAsm.usingConfig];
    config::configDiffs_t configDiffs;
    if (doPodsDiffer(currConfig, workConfig, configDiffs))
    {
      // Replace the configDiffs_t that matches, or add one if there isn't one. We use workAsm.usingConfig as the name so that when we look it up later, it'll match against workAsm.usingConfig which is all we care about when responding to changes.
      assemblyDiffs.configsDiffs.insert_or_assign(workAsm.usingConfig, move(configDiffs));
    }
  }

  // We can be confident due to the above that assemblyDiffs->configsDiffs[workAsm.usingConfig] is the changeset for the config we're on to the config we're ultimately going to match (workAsm.configs[workAsm.usingConfig]).
  if (auto it = assemblyDiffs.configsDiffs.find(workAsm.usingConfig);
      it != assemblyDiffs.configsDiffs.end())
  {
    configChanged = true;
  }
}


void Engine::computeMemoryPlanDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs)
{
  if ((assemblyDiffs.diffs & assemblyMembers_e::usingMemoryPlan) != 0)
  {
    auto & currMemoryPlan = currAsm.memoryPlans[currAsm.usingMemoryPlan];
    auto & workMemoryPlan = workAsm.memoryPlans[workAsm.usingMemoryPlan];
    memoryPlan::memoryPlanDiffs_t memoryPlanDiffs;
    if (doPodsDiffer(currMemoryPlan, workMemoryPlan, memoryPlanDiffs))
    {
      assemblyDiffs.memoryPlansDiffs.insert_or_assign(workAsm.usingMemoryPlan, move(memoryPlanDiffs));
    }
  }

  if (auto it = assemblyDiffs.memoryPlansDiffs.find(workAsm.usingConfig);
      it != assemblyDiffs.memoryPlansDiffs.end())
  {
    graphics->buildWorkMemoryPlan(workAsm.memoryPlans[workAsm.usingMemoryPlan]);

    memoryPlanChanged = true;
  }
}


void Engine::computeRenderPlanDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs)
{
}


void Engine::computeAssetDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs)
{
  assetMan->buildWorkCacheMap(workAsm, assemblyDiffs);
  assetMan->synchronizeCache();
}


void Engine::computeMaterialDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs)
{
}


void Engine::computeTableauDiffs(assembly::assembly_t const & currAsm, assembly::assembly_t const & workAsm, assembly::assemblyDiffs_t & assemblyDiffs)
{
  bool workingObjectTreeWasRebuilt = false;
  // Build tableau groups and compare. Order does not matter so we'll use an unordered_set.
  unordered_set<string> currTableaux;
  unordered_set<string> workTableaux;

  for (auto & tName: currAsm.tableauGroups[currAsm.usingTableauGroup])
    { currTableaux.insert(tName); }

  for (auto & tName: workAsm.tableauGroups[workAsm.usingTableauGroup])
    { workTableaux.insert(tName); }

  bool needToBuild = false;
  if (currTableaux != workTableaux)
    { needToBuild = true; }

  if (needToBuild == false)
  {
    for (auto & tName: workTableaux)
    {
      if (auto it = assemblyDiffs.tableauxDiffs.find(tName);
          it != assemblyDiffs.tableauxDiffs.end())
      {
        needToBuild = true;
        break;
      }
    }
  }

  if (needToBuild)
  {
    // create workObjTree
    assemblyMan->buildWorkObjectTree(workAsm);
    objectTreeChanged = true;
  }
}


void Engine::handleConfigChanges()
{
  auto & asmb = assemblyMan->getWorkAssemblyDesc();
  auto & config = asmb.configs[asmb.usingConfig];


  assetMan->handleConfigChanges(config);
  assemblyMan->handleConfigChanges(config);
  graphics->handleConfigChanges(config);
}


void Engine::blessWorkingSets()
{
  assemblyMan->blessWorkingSets();
  assetMan->blessWorkingSets();
  materialMan->blessWorkingSets();
  graphics->blessWorkingSets();

}

/*
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

    // At this point, device and swap chains are up to date.

    // Any changes to asset_ts must be noted for (re)compilation. Note that even if the asset file itself is not monitored, the asset_t always is, and will invoke recompilations if certain things change.
    for (auto & [assetName, assetsDiff] : assemblyDiffs->assetsDiffs)
    {
      if ((assetsDiff.diffs | asset::assetMembers_e::srcFile) != 0 ||
          (assetsDiff.diffs | asset::assetMembers_e::data) != 0)
      {
        if (auto it = assetMan->assets().find(assetName);
            it != assetMan->assets().end())
        {
          auto & [assetName, asset] = *it;
          asset->setNeedToCompile(true);
        }
      }
    }

    // After this all assets have their sizes computed for the host and device memory alloc and on-disk asset cache. This also creates all the vkBuffer objects, but not the backing memory.
    assetMan->syncBufferAndImageObjects();

    // If any tableau group has changes, we should recompute the vkbuffer layouts. Build an object tree for each tableau group that has changed, and then compare them.
    bool workingObjectTreeWasRebuilt = false;
    if ((assemblyDiffs->diffs & assemblyMembers_e::tableauGroups) != 0 ||
        (assemblyDiffs->diffs & assemblyMembers_e::tableaux) != 0)
    {
      for (auto & [tgName, idx]: workAsm.tableauGroups.keys())
      {
        // We need to create the object tree
        bool need = false;
        // if we don't have one,
        need = need || tableauGroups.find(tgName) == tableauGroups.end();
        // or if the tableau group itself is different,
        need = need || find(assemblyDiffs->tableauGroupsDiffs.begin(), assemblyDiffs->tableauGroupsDiffs.end(), tgName) != assemblyDiffs->tableauGroupsDiffs.end();
        // or if any of the group's tableaux are different.
        if (need == false)
        {
          for (auto tn: workAsm.tableauGroups[tgName])
          {
            need = need || find(assemblyDiffs->tableauxDiffs.begin(), assemblyDiffs->tableauxDiffs.end(), tgName) != assemblyDiffs->tableauxDiffs.end();
            if (need)
              { break; }
          }
        }

        if (need)
        {
          tableauGroups.insert_or_assign(tgName, ObjectTree { workAsm, tgName } );
          if (workAsm.usingTableauGroup == tgName)
            { workingObjectTreeWasRebuilt = true; }
        }
      }
    }

    // At this point, all assets sizes are computed and all object trees are up to date. We can ensure we have a device memory large enough.
    auto maxAllocSize = accumulate(tableauGroups.begin(), tableauGroups.end(), 0, 
      [](auto accum, auto & entry)
    {
      return std::max(accum, entry.getAllocSize());
    });

    ObjectTree & workingTree = tableauGroups.find(workAsm.usingTableauGroup)->second;

    graphics->setNewAllocDesc(workingTree.allocDesc());

    graphics->ensureDeviceAllocSize(maxAllocSize);

    // In a smooth and professional manner, we can blt any assets that have previously been compiled now, and bind their buffers/images. Assets that are compiling or loading from cache will have their day probably in some future frame.
    // Basically, the current tableau group's ObjectTree may need to be (re)created. If so,and an older version is present, we can recreate by allocating a new host-visible (and maybe device-visible on AGPs) segment and blt asset data from the old segment for any assets that haven't changed. The rest are loaded from cache or compiled in-place in a later frame.


    // Now let's sync materials.

    // Now let's sync renderplans.


    if ((assemblyDiffs->diffs & assemblyMembers_e::usingTableauGroup) != 0 ||
        (assemblyDiffs->diffs & assemblyMembers_e::tableauGroups) != 0 ||
        (assemblyDiffs->diffs & assemblyMembers_e::tableaux) != 0)
    {
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
*/

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

    graphics->updateConfig(graphicsDiffs);
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
