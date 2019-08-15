#include "utils.h"
#include "engine.h"
#include "graphics.h"
#include "commandList-gen.h"


using namespace std;
using namespace overground;


void Graphics::updateCommandList(commandList_t newCommandList)
{
  logFn();

  log(thId, logTags::asset, fmt::format(
    "new commandList:\n"
    "{}\n", print(newCommandList)));

}
