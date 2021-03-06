#include "logger.h"
#include "jobManager.h"
#include "engine.h"
#include "assetManager.h"
#include "assemblyManager.h"
#include "materialManager.h"

using namespace std;
using namespace overground;

/*
Logger * overground::logger = nullptr;
JobManager * overground::jobMan = nullptr;
Engine * overground::engine = nullptr;


void overground::initGlobals()
{
  logger = new Logger();
  jobMan = new JobManager();
  engine = new Engine();
}
*/
void overground::initGlobals()
{
  logger.emplace();
  jobMan.emplace();
  engine.emplace();
  graphics.emplace();
  assetMan.emplace();
  assemblyMan.emplace();
  materialMan.emplace();
}


int main(int argc, char ** argv)
{
  initGlobals();
  
  engine->registerAssetProvider("mesh", makeMeshAsset);
  engine->registerAssetProvider("image", makeImageAsset);
  engine->registerAssetProvider("shader", makeShaderAsset);

  engine->init(argc, argv);

  engine->enterEventLoop();
  engine->shutDown();
}

