#include <memory>
#include "renderPassAsset.h"
#include "engine.h"
#include "resourceManager.h"
#include "fileReference.h"
#include "renderPass-gen.h"

using namespace std;
using namespace humon;
using namespace overground;


unique_ptr<Asset> overground::makeRenderPass(
  string_view assetName,
  FileReference * assetDescFile, 
  HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor)
{
  return make_unique<RenderPass>(assetName, 
    assetDescFile, descFromFile, cache, compress, 
    monitor);
}


RenderPass::RenderPass(
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


void RenderPass::compileSrcAsset_impl(path_t const & path)
{
  logFn();

  auto huNode = loadHumonDataFromFile(path);
  importPod(*huNode, data);

  setDidReloadAssetData();
}


void RenderPass::applyToEngine_impl()
{
  logFn();

  clearDidReloadAssetData();

  engine->getGraphics().updateRenderPass(data);
}
