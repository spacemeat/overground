#include "engine.h"

using namespace std;
using namespace overground;


Logger * overground::_logger = nullptr;
JobManager * overground::jobMan = nullptr;
Engine * overground::engine = nullptr;


void overground::initGlobals()
{
  _logger = new Logger();
  jobMan = new JobManager();
  engine = new Engine();
}


int main(int argc, char ** argv)
{
  initGlobals();
  
  engine->registerAssetProvider("config", makeConfig);
  engine->registerAssetProvider("renderPass", makeRenderPass);
  engine->registerAssetProvider("framePlan", makeFramePlan);
  engine->registerAssetProvider("commandList", makeCommandList);

  engine->init(argc, argv);

  engine->enterEventLoop();
  engine->shutDown();
}

