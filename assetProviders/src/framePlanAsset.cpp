#include <memory>
#include "framePlanAsset.h"
#include "engine.h"
#include "resourceManager.h"
#include "fileReference.h"
#include "framePlan-gen.h"

using namespace std;
using namespace humon;
using namespace overground;


unique_ptr<Asset> overground::makeFramePlan(
  string_view assetName,
  FileReference * assetDescFile, 
  HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor)
{
  return make_unique<FramePlanAsset>(assetName, 
    assetDescFile, descFromFile, cache, compress, 
    monitor);
}


FramePlanAsset::FramePlanAsset(
  std::string_view assetName,
  FileReference * assetDescFile, 
  humon::HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor)
: Asset(assetName, assetDescFile,
    descFromFile, cache, compress, monitor)
{
  logFn();
}


void FramePlanAsset::compileSrcAsset_impl(path_t const & path)
{
  logFn();

  auto huNode = loadHumonDataFromFile(path);
  importPod(*huNode, data);

  setDidReloadAssetData();
}


void FramePlanAsset::applyToEngine_impl()
{
  logFn();

  clearDidReloadAssetData();

  engine->updateFramePlan(data);
}
