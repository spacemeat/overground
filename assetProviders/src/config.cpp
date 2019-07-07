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
  sout {} << "Config::Config()" << endl;
}


void Config::compileSrcAsset_impl(path_t const & path)
{
  sout {} << "Config::compileSrcAsset_impl()" << endl;
  auto huNode = loadHumonDataFromFile(path);
  data.loadFromHumon(* huNode);

  setDidReloadAssetData();
}


void Config::applyToEngine_impl()
{
  sout {} << "Config::applyToEngine_impl()" << endl;
  clearDidReloadAssetData();

  getResMan()->getEngine()->updateConfig(data);
}
