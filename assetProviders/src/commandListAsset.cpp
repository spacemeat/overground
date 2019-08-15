#include <memory>
#include "commandListAsset.h"
#include "engine.h"
#include "resourceManager.h"
#include "fileReference.h"
#include "commandList-gen.h"

using namespace std;
using namespace humon;
using namespace overground;


unique_ptr<Asset> overground::makeCommandList(
  string_view assetName,
  FileReference * assetDescFile, 
  HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor)
{
  return make_unique<CommandListAsset>(assetName, 
    assetDescFile, descFromFile, cache, compress, 
    monitor);
}


CommandListAsset::CommandListAsset(
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


void CommandListAsset::compileSrcAsset_impl(path_t const & path)
{
  logFn();

  auto huNode = loadHumonDataFromFile(path);
  importPod(*huNode, data);

  setDidReloadAssetData();
}


void CommandListAsset::applyToEngine_impl()
{
  logFn();

  clearDidReloadAssetData();

  engine->getGraphics().updateCommandList(data);
}
