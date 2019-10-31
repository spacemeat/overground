#include "tableauManager.h"

using namespace std;
using namespace overground;


void TableauManager::installPlugin(std::string_view name, makeTableauFn_t plugin)
{
  plugins_.emplace(name, plugin);
}
