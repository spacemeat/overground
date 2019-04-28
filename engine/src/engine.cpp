#include "engine.h"
#include "loadHumonFileJob.h"
#include "assetPack.h"

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
  loadConfig();
}


// ------------ process steps

void Engine::loadConfig()
{
  AssetPack ap;
  auto lhfj = loadHumonFileJobs.next();
  lhfj->setPath(workingDir + pathSeparator + configFile);
  lhfj->setAssetPack(& ap);
  lhfj->run();

  auto diffs = config.integrate(ap.configs.back());

  cout << "Config loaded:" << endl << config << endl
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

  g.reset(config, diffs);
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
  g.presentFrame();
  g.drawFrame();

  // animate, do other CPU-intensive stuff here
}
