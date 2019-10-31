#include "featureManager.h"

using namespace std;
using namespace overground;


void FeatureManager::installPlugin(std::string_view name, makeFeatureFn_t plugin)
{
  featurePlugins.emplace(name, plugin);
}
