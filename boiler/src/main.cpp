#include "utils.h"
#include "boiler.h"

using namespace std;
using namespace humon;
using namespace overground;


Logger * overground::_logger = nullptr;


void overground::initGlobals()
{
  _logger = new Logger();
}


int main(int argc, char* argv[])
{
  initGlobals();
  
  createLogChannel("boiler", logTags::info, logTags::macro, & cout);

  if (argc > 1 && string(argv[1]) == string("assets"))
  {
    if (argc > 3)
    {
      auto a0 = argv[2];
      auto a1 = argv[3];
      return assetsMain(
        fs::current_path().append(a0),
        fs::current_path().append(a1));
    }
    else
    {
      return assetsMain(
        fs::current_path().append(defaultAssetsDefsPath),  
        fs::current_path().append(defaultAssetsOutputDir));
    }
  }

  if (argc > 1 && string(argv[1]) == string("enums"))
  {
    if (argc > 3)
    {
      auto a0 = argv[2];
      auto a1 = argv[3];
      return enumsMain(
        fs::current_path().append(a0),
        fs::current_path().append(a1));
    }
    else
    {
      return enumsMain(
        fs::current_path().append(defaultEnumsHeaderPath), 
        fs::current_path().append(defaultEnumsOutputDir));
    }
  }

  log(0, fmt::format("Invalid command line for {}.", argv[0]));

  return 0;
}
