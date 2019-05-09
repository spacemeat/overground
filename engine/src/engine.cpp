#include "engine.h"
#include "checkForFileUpdateJob.h"
#include "assetPack.h"
#include "utils.h"

#include <iostream>

using namespace std;
using namespace overground;


const char DefaultConfigFile[] = "config.hu";
const char pathSeparator[] = "/";


Engine::Engine()
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


void Engine::init(int argc, char ** argv)
{
  sout {} << "Engine::init()" << endl;
  
  startTime = chrono::high_resolution_clock::now();
  systemTime = startTime;
  currentTime_us = engineTimePoint {};
  files.addFile("./res", "config.hu", FileType::Humon);

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

  // let's not stand on ceremony. There will be zero workers at the moment, but set it to start once we populate.
  jobManager.startWorkers();
}


void Engine::shutDown()
{
  graphics.shutDown();
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

  auto window = graphics.getMainWindow();
  if (window == nullptr)
    { return; }

  while( ! glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    iterateGameLoop();
  }

  // g.waitForGraphicsOps();
}


void Engine::iterateGameLoop()
{
  //sout {} << "Engine::iterateGameLoop()" << endl;

  updateTimer();
  graphics.presentFrame();
  graphics.drawFrame();  

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


void Engine::checkForFileUpdates(bool synchronous)
{
  sout {} << "Engine::checkForFileUpdates()" << endl;

  // for each file we have loaded,
  auto & files = this->files.getFiles();
  for (auto & fileInfo : files)
  {
    switch(fileInfo.getType())
    {
    case FileType::Humon:
      {
        auto newJob = checkForFileUpdateJobs.next();
        newJob->reset(& fileInfo);
        if (synchronous == false)
          { jobManager.enqueueJob(newJob); }
        else
          { newJob->run(); }
      }
      break;
    case FileType::Image:
      break;
    case FileType::Shader:
      break;
    }
  }
}


void Engine::checkForAssetUpdates(bool synchronous)
{
  sout {} << "Engine::checkForAssetUpdates()" << endl;

  auto & files = this->files.getFiles();
  for (auto & fileInfo : files)
  {
    auto assets = fileInfo.getAssets();
    if (assets->hasUpdates())
    {
      for (auto & config : assets->configs)
      {
        updateConfig(config);
      }
      /*
      for (auto & material : assets->materials)
      { //...
      }
      for (auto & mesh : assets->meshes)
      { //...
      }
      for (auto & model : assets->models)
      { //...
      }
      for (auto & renderPass : assets->renderPasses)
      { //...
      }
      for (auto & shader : assets->shaders)
      { //...
      }
      */

      assets->clearUpdateMark();
    }
  }
}



void Engine::updateConfig(Config const & newConfig)
{
  sout {} << "Engine::updateConfig()" << endl;

  Config::Deltas diffs = Config::Deltas::None;

  {
    lock_guard<mutex> lock(mx_config);
    config.integrate(newConfig);  
    diffs |= config.lastDiffs;

    {
      sout so {};
      so  << "Config loaded:" << endl << newConfig << endl
          << "Differences required: ";
      if ((diffs & Config::Deltas::JobManagement) == 
          Config::Deltas::JobManagement)
        { so << " JobManagement"; }
      if ((diffs & Config::Deltas::Window) == 
          Config::Deltas::Window)
        { so << " Window"; }
      if ((diffs & Config::Deltas::VulkanInstance) == 
          Config::Deltas::VulkanInstance)
        { so << " VulkanInstance"; }
      if ((diffs & Config::Deltas::PhysicalDevice) == 
          Config::Deltas::PhysicalDevice)
        { so << " PhysicalDevice"; }
      if ((diffs & Config::Deltas::LogicalDevice) == 
          Config::Deltas::LogicalDevice)
        { so << " LogicalDevice"; }
      so << endl;
    }

    graphics.reset(& config);
  }

  jobManager.setNumWorkers(newConfig.general.numWorkerThreads);
}


void Engine::updateModel(Model const & model)
{

}


void Engine::updateMesh(Mesh const & mesh)
{

}


void Engine::updateMaterial(Material const & material)
{

}


void Engine::updateShader(Shader const & shader)
{

}
