#include "engine.h"
#include "config.h"

using namespace std;
using namespace overground;


int main(int argc, char ** argv)
{
  Engine engine;

  engine.registerAssetProvider("config", makeConfig);

  engine.init(argc, argv);

  engine.enterEventLoop();
  engine.shutDown();
}

