#include <unordered_set>
#include <stack>
#include <queue>
#include <mutex>
#include <fstream>
#include "assetManager.h"
#include "assemblyManager.h"
#include "assembly-gen.h"
#include "engine.h"


using namespace std;
using namespace overground;


AssetManager::AssetManager()
{
  checkForFileChangesThread = thread ([this]{ checkForFileChanges(); });
  synchronizeCacheThread = thread ([this]{ synchronizeCache(); });
}


AssetManager::~AssetManager()
{
  dying = true;

  if (checkForFileChangesThread.joinable())
    { checkForFileChangesThread.join(); }
  
  if (synchronizeCacheThread.joinable())
    { synchronizeCacheThread.join(); }
}


void AssetManager::handleConfigChanges(config::config_t const & config)
{
  if (adbDir != config.general.adbDir ||
      adbFile != config.general.adbFile)
  {
    adbDir = config.general.adbDir;
    adbFile = config.general.adbFile;
    adbFileRef = FileRef(adbDir.append(adbFile));
    adbFileChanged = true;
  }

  if (cacheDir != config.general.cacheDir ||
      cacheFile != config.general.cacheFile)
  {
    cacheDir = config.general.cacheDir;
    cacheFile = config.general.cacheFile;
    cacheFileRef = FileRef(findCacheFile());
    cacheFileChanged = true;
  }
}


path_t AssetManager::findCacheFile()
{
  // look through the cacheDir for all the files, and find the best number.
  path_t bestFile = fmt::format("{}-00000000.adb", cacheFile);
  size_t bestFileNum = 0;
  for (auto & de : fs::directory_iterator(cacheDir))
  {
    string const & name = de.path().filename();
    if (de.path().extension() == "adb" &&
        name.size() == cacheFile.size() + 9 &&
        name.rfind(cacheFile, 0) == 0)
    {
      if (name[cacheFile.size()] == '-')
      {
        size_t stoulPos = 0;
        size_t vn = stoul(name.substr(cacheFile.size() + 1), & stoulPos);
        if (stoulPos == 8 && 
            vn >= bestFileNum &&
            de.is_regular_file())
        {
          bestFileNum = vn;
          bestFile = de.path();
        }
      }
    }
  }

  return bestFile;
}


void AssetManager::heyCheckForFileChanges()
{
  if (checkingForFileChanges == false)
  {
    checkingForFileChanges = true;
    checkForFileChangesCv.notify_one();
  }
}


void AssetManager::heySynchronizeCache()
{
  if (synchronizingCache == false)
  {
    synchronizingCache = true;
    synchronizeCacheCv.notify_one();
  }
}


void AssetManager::checkForFileChanges()
{
  while (dying == false)
  {
    {
      unique_lock lock(checkForFileChangesMx);
      // TODO: Am I yeeting this right? Like, using atomics in sane ways at all?
      checkForFileChangesCv.wait(lock, [this]
        { return dying || checkingForFileChanges ? true : false; });
    }

    shouldCheckFiles = false;
    checkForUpdatedFiles();

    if (adbFileChanged)
    {
      adbFileChanged = false;
      loadAdbFile();
      synchronizeCacheCv.notify_one();
    }

    if (cacheFileChanged)
    {
      cacheFileChanged = false;
      synchronizeCacheCv.notify_one();
    }

    if (assetFilesChanged)
    {
      assetFilesChanged = false;
      synchronizeCacheCv.notify_one();
    }

    checkingForFileChanges = false;
  }
}


void AssetManager::checkForUpdatedFiles()
{
  if (checkingAssetFiles)
    { return; }

  checkingAssetFiles = true;
  // clear the flag on fn exit
  FlagRaiiser fr(checkingAssetFiles, false);

  bool filesChanged = false;

  // Just set a flag if any files have changed
  for (auto & [assetName, asset] : currAssetMap)
  {
    if (asset->getSrcFile().has_value() &&
        (asset->getSrcFile()->exists() == false ||
         asset->getSrcFile()->didFileChange()))
    {
      filesChanged = true;
      asset->setNeedToCompile();
    }
  }

  assetFilesChanged = filesChanged;
  adbFileChanged = 
    adbFileRef.exists() == false ||
    adbFileRef.didFileChange();
  cacheFileChanged = 
    cacheFileRef.exists() == false ||
    cacheFileRef.didFileChange();
}


void AssetManager::loadAdbFile()
{
  auto huNode = loadHumonDataFromFile(adbFileRef.path());

  if (huNode->isDict())
  {
    for (size_t idx = 0; idx < huNode->size(); ++idx)
    {
      auto & assetName = huNode->keyAt(idx);
      auto & assetNode = * huNode / idx;

      size_t cacheOffset = 0;
      size_t cacheSize = 0;
      size_t x = 0, y = 0, z = 0;
      size_t numMipLevels = 0;
      vk::Format format = vk::Format::eUndefined;

      if (assetNode % "cacheOffset")
        { cacheOffset = assetNode / "cacheOffset"; }
      if (assetNode % "cacheSize")
        { cacheSize = assetNode / "cacheSize"; }

      if (assetNode % "dims")
      {
        auto & dimsNode = assetNode / "cacheOffset";
        if (dimsNode % 0)
          { x = dimsNode / 0; }
        if (dimsNode % 1)
          { y = dimsNode / 1; }
        if (dimsNode % 2)
          { z = dimsNode / 2; }
      }

      if (assetNode % "numMipLevels")
        { numMipLevels = assetNode / "cacheOffset"; }
      if (assetNode % "format")
        { format = fromString<vk::Format>((string) (assetNode / "format")); }

      if (format == vk::Format::eUndefined)
        { workCacheMap.trackAsset(assetName, cacheOffset, cacheSize); }
      else
        { workCacheMap.trackAsset(assetName, cacheOffset, cacheSize, {x, y, z}, numMipLevels, format); }
    }
  }
}


void AssetManager::storeAdbFile()
{
  ofstream ofs(adbFileRef.path());
  ofs << 
R"({
  assetDb: {
)";

  for (auto bd : currCacheMap.getBufferDesc().vect())
  {
    ofs << fmt::format(
R"(    {assetName}: {{
      cacheOffset: {cacheOffset}
      cacheSize: {cacheSize}
)",
      fmt::arg("cacheOffset", bd.offset),
      fmt::arg("cacheSize", bd.size));

    if (bd.imageData.has_value())
    {
      AllocDescImageData const & bdid = bd.imageData.value();
      ofs << fmt::format(
R"(      dims: [{dims.x} {dims.y} {dims.z}]
      numMipLevels: {numMipLevels}
      format: {format}
)", 
        fmt::arg("dims.x", bdid.dims[0]),
        fmt::arg("dims.y", bdid.dims[1]),
        fmt::arg("dims.z", bdid.dims[2]),
        fmt::arg("numMipLevels", bdid.numMipLevels),
        fmt::arg("format", to_string(bdid.format)));
    }    

    ofs << 
R"(    }
)";
  }

  ofs << 
R"(
  }
}
)";

  // let's not reload it.
  adbFileRef.didFileChange(true);
}


void AssetManager::buildWorkCacheMap(
  assembly::assembly_t const & workAsm, 
  assembly::assemblyDiffs_t & assemblyDiffs)
{
  // I could be working off the diffs, but really it's probably as fast to recreate them all. That's my excuse.
  workAssetMap.clear();
  workCacheMap.reset(false);
//for each asset in assembly:
  // TODO: parallelize this
  size_t totalSize = 0;
  for (auto & assetDesc : workAsm.assets.vect())
  {
    // assemblyDiffs.assetsDiffs contains entries that are either new or deleted or changed
    bool assetDescTouched = (assemblyDiffs.diffs & assembly::assemblyMembers_e::assets) != 0 &&
        assemblyDiffs.assetsDiffs.find(assetDesc.name) != assemblyDiffs.assetsDiffs.end();

    auto itCurrAsset = currAssetMap.find(assetDesc.name);
    bool assetPreviouslyLoaded = (itCurrAsset != currAssetMap.end());
    
    if (assetDescTouched || assetPreviouslyLoaded == false)
    {
  //  create plugin asset type object
      auto assetObj = makeAsset(assetDesc);
  //  compute essentials like compile size and image dims
      assetObj->computeImportData();
  //  track dat ass
      workAssetMap.emplace(pair {assetDesc.name, move(assetObj)});
      totalSize += assetObj->getCacheSize();
      assetObj->setCacheOffset(totalSize);
  
      workCacheMap.trackAsset(assetObj.get());
    }
    else
    {
      auto currAssetObj = itCurrAsset->second;
      workAssetMap.emplace(pair {assetDesc.name, currAssetObj});
      totalSize += currAssetObj->getCacheSize();
      currAssetObj->setCacheOffset(totalSize);

      workCacheMap.trackAsset(currAssetObj.get());
    }
  }

  storeAdbFile();
}


void AssetManager::synchronizeCache()
{
  while (dying == false)
  {
    unique_lock lock(synchronizeCacheMx);
    // TODO: Am I yeeting this right? Like, using atomics in sane ways at all?
    synchronizeCacheCv.wait(lock, [this]
      { return dying || synchronizingCache ? true : false; });
    
    // TODO NEXT: Synchronize caches!

  //  if cache file exists:
  //    for each asset file in assembly and on disk:
  //      stat cache file against asset file
  //      
  //      if cache file is up to date:
  //      open cache file

    synchronizingCache = false;
  }
}


void fillWorkCache()
{
  /*
    for each w.window:
      awlist = w.assets in w.window
      cwlist.clear()
      for each a in aslist:
        if a not in c.assets:
          compile a
        else:
          add c.assets.a.address to cwlist
      cwlist.sort by address
      for each e in cwlist:
        move c.window to e.address if needed
        copy e.a
  */
}
