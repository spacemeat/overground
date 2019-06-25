#include <sys/stat.h>
#include <string>
#include <fstream>
#include <stack>
#include <algorithm>
#include <experimental/filesystem>
#include "utils.h"
#include "asset.h"
#include "resourceManager.h"
#include "engine.h"
#include "humon.h"
#include "config.h"
#include "model.h"
#include "mesh.h"
#include "fileReference.h"
#include "checkForAssetDescFileUpdateJob.h"
#include "updateJobs.h"


using namespace std;
using namespace overground;

namespace fs = std::experimental::filesystem;


ResourceManager::ResourceManager(
  Engine & engine,
  std::string const & baseAssetDir,
  std::string const & baseAssetDataDir)
: engine(engine),
  baseAssetDir(baseAssetDir),
  baseAssetDataDir(baseAssetDataDir)
{
}


AssetFileInfo & ResourceManager::addAssetDescFile(string const & assetFileBaseName)
{
  if (auto it = assetFiles.find(assetFileBaseName);
      it != assetFiles.end())
    { return it->second; }
  
  auto assetFileName = assetFileBaseName + assetFileExtension;

  auto p = findFile(baseAssetDir, assetFileName);

  auto info = AssetFileInfo {
    move(make_unique<FileReference>(p)), 
    std::vector<string>()
  };
  auto kvp = assetFiles.emplace(assetFileBaseName, info);
  return kvp.first->second;
}


void ResourceManager::removeAssetDescFile(AssetFileInfo const & assetDescFileInfo)
{
  // TODO:
  // note all assets from this file
  // remove this file from assetFiles
  // --ref each asset from *assets
}


AssetData * ResourceManager::addAssetDataFile(string const & newAssetDataFile)
{
  if (auto it = assetDataFiles.find(newAssetDataFile);
      it != assetDataFiles.end())
    { return & it->second; }

  auto p = findFile(baseAssetDataDir, newAssetDataFile);

  auto it = assetDataFiles.emplace(newAssetDataFile, 
    AssetData(this, move(make_unique<FileReference>(p))));
  
  return & it.first->second;
}


void ResourceManager::removeAssetDataFile(string const & file)
{
  // TODO
}


void ResourceManager::checkForAnyFileUpdates(bool synchronous)
{
  // Check asset description (.ass) files.
  for (auto & assetFile : assetFiles)
  {
    auto newJob = checkForAssetDescFileUpdateJobs.next();
    newJob->reset(this, assetFile.second.first.get());
    if (synchronous == false)
      { engine.enqueueJob(newJob); }
    else
      { newJob->run(); }
  }

  // Check all assetData files (mesh, texture, etc).
  for (auto & assetKvp : assets)
  {
    auto * asset = assetKvp.second.get();
    if (asset->isMonitored())
    {
      asset->updateFileModTimes();
    }
  }
}


void ResourceManager::checkForAssetDescFileUpdate(FileReference * file)
{
  if (file->doesNeedUpdate())
  {
    file->setUpdated();

    // load humon data from asset file
    auto phu = move(loadHumonDataFromFile(file->getPath()));

    bool globalCache = true;
    bool globalCompress = true;
    bool globalMonitor = true;

    humon::HuNode & n = *phu;
    for (int i = 0; i < n.size(); ++i)
    {
      auto & assetName = n.keyAt(i);
      auto & assetBlock = n / assetName;

      // if no asset by that name, or if the asset definition has changed,
      if (auto it = assets.find(assetName);
          it == assets.end() ||
          assetBlock != (it->second.getDesc()))
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
        auto newAsset = make_unique<Asset>(
            this, assetName, file, assetBlock,
            cache, compress, monitor);
        assets.insert_or_assign(assetName, move(newAsset));

        auto assetData = newAsset->getAssetData();
        assetData->forceUpdate();

        assetsChanged = true;
      }
    }
  }
}


void ResourceManager::checkForAssetUpdates(bool synchronous)
{
  if (assetsChanged == false)
    { return; }

  // we're handling it, y0
  // TODO: Does any of this need mutexing? Should only be one check job running, right..?
  assetsChanged = false;

  stack<Job *> jobGroup;

  auto createBufferJob = createAssetBufferJobs.next();
  createBufferJob->reset(this);
  for (auto & asset : assets)
  {
    auto status = asset.second.getStatus();

    if (status == Asset::Status::srcFileIsNew)
    {
      auto compileJob = compileAssetJobs.next();
      compileJob->reset(this, & asset.second);
      createBufferJob->waitFor(compileJob);
      if (synchronous == false)
        { jobGroup.push(compileJob); }
      else
        { compileJob->run(); }
    }

    else if (status == Asset::Status::compiledFileIsNew)
    {
      auto loadJob = loadCompiledAssetJobs.next();
      loadJob->reset(this, & asset.second);
      createBufferJob->waitFor(loadJob);
      if (synchronous == false)
        { jobGroup.push(loadJob); }
      else
        { loadJob->run(); }
    }
  }

  if (synchronous == false)
  { 
    jobGroup.push(createBufferJob);
    engine.enqueueJobs(jobGroup);
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

  for (auto & asset : assets)
  {
    auto status = asset.second.getStatus();

    if (status == Asset::Status::hostBufferIsNew)
    {
      auto updateJob = updateAssetJobs.next();
      updateJob->reset(this, & asset.second);
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
    engine.enqueueJobs(jobGroup);
  }
  else
  {
    syncJob->run();
    rpJob->run();
  }
}

/*
void ResourceManager::gatherAssetsFromFile(std::string const & assetName)
{
  sout {} << "ResourceManager::gatherAssetsFromFile(" << assetName << ")" << endl;



  string strContent;
  {
    auto ifs = ifstream(file->getPath());
    if (ifs.is_open())
    {
      strContent = string(
        (istreambuf_iterator<char>(ifs)),
        (istreambuf_iterator<char>()));
    }
  }

  fileInfo->getAssets()->clearContents();

  rootNode = humon::fromString(strContent);
  if (rootNode->isDict())
  {
    auto & rootDict = rootNode->asDict();
    if (rootDict.hasKey("config"))
    {
      auto & config = fileInfo->getAssets()->configs.emplace_back();
      config.setFileInfo(fileInfo);
      auto job = initConfigJobs.next();
      job->reset(config, rootDict / "config");

      if (jobManager != nullptr)
        { jobManager->enqueueJob(job); }
      else
        { job->run(); }
    }

    if (rootDict.hasKey("meshes"))
    {
      auto & meshesDict = rootDict / "meshes";
      for (size_t i = 0; i < meshesDict.size(); ++i)
      {
        auto key = meshesDict.keyAt(i);
        auto & mesh = fileInfo->getAssets()->meshes.emplace_back();
        mesh.setFileInfo(fileInfo);
        mesh.setName(key);
        auto job = initMeshJobs.next();
        job->reset(mesh, meshesDict / key);

        if (jobManager != nullptr)
          { jobManager->enqueueJob(job); }
        else
          { job->run(); }
      }
    }

    if (rootDict.hasKey("models"))
    {
      auto & modelsDict = rootDict / "models";
      for (size_t i = 0; i < modelsDict.size(); ++i)
      {
        auto key = modelsDict.keyAt(i);
        auto & model = fileInfo->getAssets()->models.emplace_back();
        model.setFileInfo(fileInfo);
        model.setName(key);
        auto job = initModelJobs.next();
        job->reset(model, modelsDict / key);

        if (jobManager != nullptr)
          { jobManager->enqueueJob(job); }
        else
          { job->run(); }
      }
    }

    // renderPasses materials shaders
  }

}

*/
