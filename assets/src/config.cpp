#include <memory>
#include "config.h"
#include "engine.h"
#include "resourceManager.h"
#include "fileReference.h"

using namespace std;
using namespace humon;
using namespace overground;


unique_ptr<Asset> overground::makeConfig(
  ResourceManager * resMan,
  string const & assetName,
  FileReference * assetDescFile, 
  HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor)
{
  return make_unique<Config>(resMan, assetName, 
    assetDescFile, descFromFile, cache, compress, 
    monitor);
}


Config::Config(ResourceManager * resMan,
  std::string const & assetName,
  FileReference * assetDescFile, 
  humon::HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor)
: Asset(resMan, assetName, assetDescFile,
    descFromFile, cache, compress, monitor)
{
}


void Config::compileSrcAsset(path_t const & srcPath)
{
  auto huNode = loadHumonDataFromFile(srcPath);
  data.loadFromHumon(* huNode);
}


void Config::applyToEngine()
{
  getResMan()->getEngine()->updateConfig(data);
}


