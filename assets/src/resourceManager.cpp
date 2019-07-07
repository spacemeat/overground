#include <sys/stat.h>
#include <string>
#include <fstream>
#include <stack>
#include <algorithm>
#include <experimental/filesystem>
#include "utils.h"
#include "asset.h"
#include "resourceManager.h"
#include "humon.h"
#include "fileReference.h"
#include "assetFiles.h"
#include "updateJobs.h"


using namespace std;
using namespace overground;

namespace fs = std::experimental::filesystem;


ResourceManager::ResourceManager(
  Engine * engine,
  JobManager * jobManager,
  path_t const & baseAssetDescDir,
  path_t const & baseAssetDataDir)
: engine(engine),
  jobManager(jobManager),
  baseAssetDescDir(baseAssetDescDir),
  baseAssetDataDir(baseAssetDataDir)
{
}


void ResourceManager::registerAssetProvider(
      std::string const & assetKind,
      makeAssetFn_t const & fn)
{
  assetProviders.insert_or_assign(assetKind, fn);
}


unique_ptr<Asset> ResourceManager::makeAsset(
  std::string const & assetName,
  FileReference * assetDescFile, 
  humon::HuNode & descFromFile,
  bool cache, bool compress,
  bool monitor
)
{
  if (descFromFile % "kind")
  {
    auto kind = (string) (descFromFile / "kind");
    if (auto it = assetProviders.find(kind); 
      it != assetProviders.end())
    {
      return move(it->second)(this, assetName, assetDescFile, descFromFile, cache, compress, monitor);
    }
    else
    {
      sout {} << "Missing kind \"" << kind << "\"" << endl;
    }
    
  }

  throw runtime_error("Asset kind missing or malformed, or provider not set for the asset.");
}


AssetDescFile * ResourceManager::addAssetDescFile(string const & assetFileBaseName)
{
  if (auto it = assetDescFiles.find(assetFileBaseName);
      it != assetDescFiles.end())
    { return & it->second; }
  
  auto assetFileName = assetFileBaseName + assetFileExtension;
  auto p = findFile(assetFileName, baseAssetDescDir);
  auto kvp = assetDescFiles.try_emplace(assetFileBaseName, p);
  return & kvp.first->second;
}


void ResourceManager::removeAssetDescFile(AssetFileInfo const & assetDescFileInfo)
{
  // TODO:
  // note all assets from this file
  // remove this file from assetFiles
  // --ref each asset from *assets
}


AssetDataFile * ResourceManager::addAssetDataFile(string const & newAssetDataFile, bool asCompiledFile)
{
  if (auto it = assetSrcFiles.find(newAssetDataFile);
      it != assetSrcFiles.end())
    { return & it->second; }

  auto p = findFile(newAssetDataFile, baseAssetDataDir);
  auto kvp = assetSrcFiles.try_emplace(newAssetDataFile, p, asCompiledFile);
  return & kvp.first->second;
}


void ResourceManager::removeAssetDataFile(string const & file, bool asCompiledFile)
{
  // TODO
}


AssetDataFile * ResourceManager::addAssetSrcFile(string const & newAssetDataFile)
{
  return addAssetDataFile(newAssetDataFile, false);
}


void ResourceManager::removeAssetSrcFile(string const & file)
{
  removeAssetDataFile(file, false);
}


AssetDataFile * ResourceManager::addAssetOptFile(string const & newAssetDataFile)
{
  return addAssetDataFile(newAssetDataFile, true);
}


void ResourceManager::removeAssetOptFile(string const & file)
{
  removeAssetDataFile(file, true);
}


void ResourceManager::checkForAnyFileUpdates(bool synchronous)
{
  // Check asset description (.ass) files.
  for (auto & [_, assetFile] : assetDescFiles)
  {
    auto newJob = checkForAssetDescFileUpdateJobs.next();
    newJob->reset(this, & assetFile);
    if (synchronous == false)
      { jobManager->enqueueJob(newJob); }
    else
      { newJob->run(); }
  }

  // Check all assetDataFiles (mesh, texture, etc).
  for (auto & [_, assetDataFile] : assetOptFiles)
  {
    assetDataFile.checkFileModTime();
    if (assetDataFile.isModified())
    {
      sout {} << "opt file modified." << endl;
      for (auto asset : assetDataFile.getClientAssets())
      {
        if (asset->isMonitored())
          { asset->setNeedsUpdateFromOpt(); }
      }
    }
  }

  for (auto & [_, assetDataFile] : assetSrcFiles)
  {
    assetDataFile.checkFileModTime();
    if (assetDataFile.isModified())
    {
      sout {} << "src file modified." << endl;
      for (auto asset : assetDataFile.getClientAssets())
      {
        if (asset->isMonitored())
          { asset->setNeedsUpdateFromSrc(); }
      }
    }
  }
}


void ResourceManager::checkForAssetDescFileUpdate(FileReference * file)
{
//  sout {} << "ResourceManager::checkForAssetDescFileUpdate()" << endl;

  file->checkFileModTime();
  if (file->isModified())
  {
    file->clearModified();

    // load humon data from asset file
    auto phu = move(loadHumonDataFromFile(file->getPath()));

    bool globalCache = *phu / "cache";
    bool globalCompress = *phu / "compress";
    bool globalMonitor = *phu / "monitor";

    humon::HuNode & n = *phu / "assets";
    for (size_t i = 0; i < n.size(); ++i)
    {
      auto & assetName = n.keyAt(i);
      auto & assetBlock = n / assetName;

      // if no asset by that name, or if the asset definition has changed,
      if (auto it = assets.find(assetName);
          it == assets.end() ||
          assetBlock != (it->second->getDesc()))
      {
        string assetDataFile;
        bool cache = globalCache;
        bool compress = globalCompress;
        bool monitor = globalMonitor;

        if (assetBlock % "dataFile")
          { assetDataFile = (string) (assetBlock / "dataFile"); }
        if (assetBlock % "cache")
          { cache = assetBlock / "cache"; }
        if (assetBlock % "compile")
          { compress = assetBlock / "compile"; }
        if (assetBlock % "monitor")
          { monitor = assetBlock / "monitor"; }

        // make a new asset
        auto newAsset = makeAsset(
            assetName, file, assetBlock,
            cache, compress, monitor);
        assets.insert_or_assign(assetName, move(newAsset));

        assetsChanged = true;
      }
    }
  }
}


void ResourceManager::checkForAssetUpdates(bool synchronous)
{
//  sout {} << "ResourceManager::checkForAssetUpdates()" << endl;

  if (assetsChanged == false)
    { return; }

  sout {} << "  assetcChanged == true" << endl;

  // we're handling it, y0
  // TODO: Does any of this need mutexing? Should only be one check job running, right..?
  assetsChanged = false;

  stack<Job *> jobGroup;

  auto createBufferJob = createAssetBufferJobs.next();
  createBufferJob->reset(this);
  for (auto & [_, asset] : assets)
  {
    bool loadSrc = asset->doesNeedUpdateFromSrc();
    bool loadOpt = asset->doesNeedUpdateFromOpt();

    if (loadOpt && ! loadSrc)
    {
      asset->clearNeedUpdateFromOpt();
      auto loadJob = loadCompiledAssetJobs.next();
      loadJob->reset(this, asset.get());
      createBufferJob->waitFor(loadJob);
      if (synchronous == false)
        { jobGroup.push(loadJob); }
      else
        { loadJob->run(); }
    }
    else if (loadSrc)
    {
      asset->clearNeedUpdateFromSrc();
      asset->clearNeedUpdateFromOpt();
      auto compileJob = compileAssetJobs.next();
      compileJob->reset(this, asset.get());
      createBufferJob->waitFor(compileJob);
      if (synchronous == false)
        { jobGroup.push(compileJob); }
      else
        { compileJob->run(); }
    }
  }

  if (synchronous == false)
  { 
    jobGroup.push(createBufferJob);
    jobManager->enqueueJobs(jobGroup);
  }
  else
    { createBufferJob->run(); }
}


// NOTE: called from createBufferJob
void ResourceManager::updateFromFreshAssets(bool synchronous)
{
  stack<Job *> jobGroup;

  auto syncJob = syncAssetBufferJobs.next();  
  syncJob->reset(this);

  auto rpJob = syncAssetRenderPipelineJobs.next();
  rpJob->reset(this);

  for (auto & [_, asset] : assets)
  {
    if (asset->didReloadAssetData())
    {
      asset->clearDidReloadAssetData();
      auto updateJob = updateAssetJobs.next();
      updateJob->reset(this, asset.get());
      syncJob->waitFor(updateJob);
      rpJob->waitFor(updateJob);
      if (synchronous == false)
        { jobGroup.push(updateJob); }
      else
        { updateJob->run(); }
    }
  }

  if (synchronous == false)
  {
    jobGroup.push(syncJob);
    jobGroup.push(rpJob);
    jobManager->enqueueJobs(jobGroup);
  }
  else
  {
    syncJob->run();
    rpJob->run();
  }
}
