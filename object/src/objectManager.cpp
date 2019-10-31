#include "objectManager.h"

using namespace std;
using namespace overground;


void ObjectManager::installPlugin(std::string_view name, makeObjectFn_t plugin)
{
  plugins_.emplace(name, plugin);
}
