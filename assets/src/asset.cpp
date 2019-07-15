#include "asset.h"
#include "resourceManager.h"
#include "fileReference.h"
#include "jobScheduler.h"
//#include "engine.h"

using namespace std;
using namespace overground;


Asset::Asset(
  ResourceManager * resMan,
  std::string_view assetName,
  FileReference * assetDescFile, 
  humon::HuNode & descFromFile,
  bool cache, bool compile,
  bool monitor)
: resMan(resMan), assetName(assetName),
  assetDescFile(assetDescFile), 
  desc(descFromFile.clone()), thisIsCached(cache),
  thisIsCompiled(compile), thisIsMonitored(monitor)
{
  if (*desc % "dataFile")
  {
    string filename = (string) (*desc / "dataFile");
    auto adf = resMan->addAssetDataFile(filename, false);
    srcFilePath = adf->getPath();
    adf->setClientAsset(this);

    if (cache)
    {
      path_t compiledPath = srcFilePath;
      compiledPath.extension() = getCompiledExtension();
      auto adfo = resMan->addAssetDataFile(compiledPath.filename().string(), false);
      optFilePath = compiledPath;
      adfo->setClientAsset(this);
    }
  }
}


Asset::~Asset()
{
}


void Asset::setDesc(humon::HuNode const & desc)
{
  this->desc = desc.clone();
  setNeedsUpdateFromSrc();
}


std::string Asset::getCompiledExtension()
{ 
  return "";
}


void Asset::compileSrcAsset(JobScheduler & sched)
{
  if (isCompiled())
  {
    compileSrcAsset_impl(srcFilePath);

    // if asset is cached, save the compiled version to disk in a separate job
    if (isCached())
    {
      auto saveJob = makeFnJob("saveCompiledAsset", [&]
        { saveCompiledAsset(); });
      sched.scheduleJob(saveJob);
    }
  }
}


void Asset::loadCompiledAsset()
{
  auto ifs = compiledAssetLoader_t(
    optFilePath.c_str(), ios::binary);
  loadCompiledAsset_impl(ifs);
}


void Asset::saveCompiledAsset()
{
  auto ofs = compiledAssetLoader_t(
    optFilePath.c_str(), ios::binary | ios::out);
  loadCompiledAsset_impl(ofs);
}


void Asset::compileSrcAsset_impl(path_t const & path)
{
  return;
}


void Asset::loadCompiledAsset_impl(
  compiledAssetLoader_t & file)
{
  return;
}


void Asset::saveCompiledAsset_impl(
  compiledAssetSaver_t & file)
{
  return;
}


uint64_t Asset::getCompiledSize()
{
  return 0LL;
}


void * Asset::getCompiledData()
{
  return nullptr;
}


int Asset::getGraphicsBufferId()
{
  return -1;
}


uint64_t Asset::getGraphicsBufferSize()
{
  return 0;
}


void Asset::applyToBuffer(void * targetBuffer)
{
  applyToBuffer_impl(targetBuffer);;
}


void Asset::applyToEngine()
{
  applyToEngine_impl();
}


void Asset::applyToBuffer_impl(void * targetBuffer)
{
  return;
}


void Asset::applyToEngine_impl()
{
  return;
}
