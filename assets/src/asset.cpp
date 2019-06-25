#include "asset.h"

using namespace std;
using namespace overground;


Asset::Asset(
  ResourceManager * resMan,
  std::string const & assetName,
  FileReference * assetDescFile, 
  humon::HuNode & descFromFile,
  bool cache, bool compile,
  bool monitor)
: resMan(resMan), assetName(assetName),
  assetDescFile(assetDescFile), 
  desc(descFromFile.clone()), isCached(cache),
  isCompiled(compile), isMonitored(monitor),
  modTime(0), runtimeModTime(0)
{
  if (*desc % "dataFile")
  {
    path_t filename = (string) (*desc / "dataFile");
    auto ad = resMan->addAssetDataFile(filename);

    path_t compiledPath = ad->getSrcFile()->getPath();
    if (cache)
      { compiledPath.extension = getCompiledExtension(); }
    ad->setCompiledPath(compiledPath);
    assetData = ad;
  }
}


void Asset::updateFileModTimes()
{
  assetData->updateFileModTimes();
}


std::string Asset::getCompiledExtension()
{ 
  return "";
}


int Asset::getGraphicsBufferId()
{
  return -1;
}


uint64_t Asset::getGraphicsBufferSize()
{
  return 0;
}


void Asset::loadCompiledAsset(compiledAssetLoader_t & file)
{
  return;
}


void Asset::saveCompiledAsset(compiledAssetSaver_t & file)
{
  return;
}


void Asset::applyToBuffer(void * targetBuffer)
{
  return;
}
