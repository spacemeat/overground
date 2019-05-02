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
  
}


void Engine::init(int argc, char ** argv)
{
  sout {} << "Engine::init()" << endl;

  files.addFile("./res", "config.hu", FileType::Humon);

  eventPeriods.push_back(chrono::milliseconds{1000});
  lastEventTimes.push_back(timePoint());

  // load up the config file
  checkForFileUpdates(true);
  // latch the config to engine; creates the window, etc.
  checkForAssetUpdates(true);

  // let's not stand on ceremony. There will be zero workers at the moment, but set it to start once we populate.
  jobManager.startWorkers();
}


// ------------ process steps

void Engine::loadConfig()
{
  /*
  AssetPack ap;
  auto lhfj = loadHumonFileJobs.next();
  lhfj->reset(...);
  lhfj->setPath(workingDir + pathSeparator + configFile);
  lhfj->setAssetPack(& ap);
  lhfj->run();

  Config::Deltas diffs = Config::Deltas::None;
  auto & newConfig = ap.configs.back();

  {
    lock_guard<mutex> lock(mx_config);
    config.integrate(newConfig);  
    diffs |= config.lastDiffs;
    g.reset(config);
  }

  cout << "Config loaded:" << endl << newConfig << endl
      << "Differences required: ";
  if ((diffs & Config::Deltas::JobManagement) == 
      Config::Deltas::JobManagement)
    { cout << " JobManagement"; }
  if ((diffs & Config::Deltas::Window) == 
      Config::Deltas::Window)
    { cout << " Window"; }
  if ((diffs & Config::Deltas::Device) == 
      Config::Deltas::Device)
    { cout << " Device"; }
  cout << endl;
  */
}


void Engine::createGraphics()
{
}


void Engine::loadScene()
{
  
}


void Engine::latchSceneDelta()
{
  
}


void Engine::enterEventLoop()
{
  sout {} << "Engine::enterEventLoop()" << endl;

  auto window = g.getMainWindow();
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
  sout {} << "Engine::iterateGameLoop()" << endl;

  updateTimer();
  g.presentFrame();
  g.drawFrame();  

  performScheduledEvents();
  // animate, do other CPU-intensive stuff here
}


void Engine::updateTimer()
{
  previousTime = currentTime;
  currentTime = chrono::high_resolution_clock::now();
  frameTime_ms = currentTime - previousTime;
}


void Engine::performScheduledEvents()
{
  // perform scheduled actions if any
  for (size_t i = 0; i < eventPeriods.size(); ++i)
  {
    timeDuration since = currentTime - lastEventTimes[i];
    if (since >= eventPeriods[i])
    {
      lastEventTimes[i] += eventPeriods[i];

      if (i == (size_t) ScheduledEvents::CheckForFileUpdates)
        { checkForFileUpdates(false); }
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
    g.reset(config);
  }

  jobManager.setNumWorkers(newConfig.general.numWorkerThreads);

  cout << "Config loaded:" << endl << newConfig << endl
      << "Differences required: ";
  if ((diffs & Config::Deltas::JobManagement) == 
      Config::Deltas::JobManagement)
    { cout << " JobManagement"; }
  if ((diffs & Config::Deltas::Window) == 
      Config::Deltas::Window)
    { cout << " Window"; }
  if ((diffs & Config::Deltas::Device) == 
      Config::Deltas::Device)
    { cout << " Device"; }
  cout << endl;
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
