#include <unordered_set>
#include <stack>
#include <queue>
#include <mutex>
#include <fstream>
#include <tuple>

// For the mmap
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
       
#include "assetManager.h"
#include "assemblyManager.h"
#include "assembly-gen.h"
#include "engine.h"
#include "taskManager.h"


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
  if (adbPath != config.assetDatabase.adbPath)
  {
    adbPath = config.assetDatabase.adbPath;
    adbFileRef = FileRef(adbPath);
    adbFileChanged = true;
  }

  if (cacheDir != config.assetDatabase.cacheDir ||
      cacheFile != config.assetDatabase.cacheFile)
  {
    cacheDir = config.assetDatabase.cacheDir;
    cacheFile = config.assetDatabase.cacheFile;
    cacheFileRef = FileRef(findCacheFile());
    cacheFileChanged = true;
  }

  cacheMapWindowSize = config.assetDatabase.cacheMapWindowSize;
}


path_t AssetManager::findCacheFile() const
{
  // look through the cacheDir for all the files, and find the best number.
  path_t bestPath = fmt::format("{}/{}-00000000.adb", cacheDir, cacheFile);
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
          bestPath = de.path().filename();
        }
      }
    }
  }

  return bestPath;
}


path_t AssetManager::getNextCacheFileName() const
{
  path_t cf = findCacheFile();
  // If no numbered cache file exist, return the 0th one we just named.
  if (fs::is_regular_file(cf) == false)
    { return cf; }

  string fn = cf.filename();
  
  size_t stoulPos = 0;
  size_t vn = stoul(fn.substr(fn.size() - 8), & stoulPos);
  if (stoulPos == 8)
  {
    cf.replace_filename(fmt::format("{}-{:08d}", cacheFile, vn));
    return cf;
  }

  log(thId, logTags::err, "Cache file name is malformed: Need 8-digit counter.");
  return cf;
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
    bool synced = false;

    if (adbFileChanged)
    {
      adbFileChanged = false;
      loadAdbFile();
      synchronizeCacheCv.notify_one();
      synced = true;
    }

    if (cacheFileChanged)
    {
      cacheFileChanged = false;
      if (! synced)
      {
        synchronizeCacheCv.notify_one();
        synced = true;
      }
    }

    if (assetFilesChanged)
    {
      assetFilesChanged = false;
      if (! synced)
      {
        synchronizeCacheCv.notify_one();
        synced = true;
      }
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

      size_t offset = 0;
      size_t dataSize = 0;
      size_t storageSize = 0;
      size_t x = 0, y = 0, z = 0;
      size_t numMipLevels = 0;
      vk::Format format = vk::Format::eUndefined;

      if (assetNode % "offset")
        { offset = assetNode / "offset"; }
      if (assetNode % "dataSize")
        { dataSize = assetNode / "dataSize"; }
      if (assetNode % "storageSize")
        { storageSize = assetNode / "storageSize"; }

      if (assetNode % "dims")
      {
        auto & dimsNode = assetNode / "dims";
        if (dimsNode % 0)
          { x = dimsNode / 0; }
        if (dimsNode % 1)
          { y = dimsNode / 1; }
        if (dimsNode % 2)
          { z = dimsNode / 2; }
      }

      if (assetNode % "numMipLevels")
        { numMipLevels = assetNode / "numMipLevels"; }
      if (assetNode % "format")
        { format = fromString<vk::Format>((string) (assetNode / "format")); }

      if (format == vk::Format::eUndefined)
        { workCacheMap.track(assetName, offset, dataSize, storageSize); }
      else
        { workCacheMap.track(assetName, offset, dataSize, storageSize, {x, y, z}, numMipLevels, format); }
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

  for (auto const & bd : currCacheMap.getAllocDescEntries().vect())
  {
    ofs << fmt::format(
R"(    {assetName}: {{
      offset: {offset}
      dataSize: {dataSize}
      storageSize: {storageSize}
)",
      fmt::arg("offset", bd.offset),
      fmt::arg("dataSize", bd.dataSize),
      fmt::arg("storageSize", bd.storageSize));

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
  //-- workAssetMap.clear();
  workCacheMap.reset(alignmentRule::cacheMap);
//for each asset in assembly:
  // TODO: parallelize this
  size_t totalSize = 0;
  for (auto & assetDesc : workAsm.assets.vect())
  {
    // assemblyDiffs.assetsDiffs contains entries that are either new or deleted or changed
    bool assetDescTouched = (assemblyDiffs.diffs & assembly::assemblyMembers_e::assets) != 0 &&
        assemblyDiffs.assetsDiffs.find(assetDesc.name) != assemblyDiffs.assetsDiffs.end();

    auto const itCurrAsset = currAssetMap.find(assetDesc.name);
    bool assetPreviouslyLoaded = itCurrAsset != currAssetMap.end();
    
    if (assetDescTouched || assetPreviouslyLoaded == false)
    {
  //  create plugin asset type object
      auto assetObj = makeAsset(assetDesc);
  //  compute essentials like compile size and image dims
      assetObj->computeImportData();
  //  track dat ass
      workAssetMap.emplace(pair {assetDesc.name, move(assetObj)});  
      workCacheMap.track(assetObj.get());
    }
    else
    {
      auto currAssetObj = itCurrAsset->second;
      workAssetMap.emplace(pair {assetDesc.name, currAssetObj});
      workCacheMap.track(currAssetObj.get());
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
    
    // Synchronize caches! I think (TODO: verify) we can assume the cache map is fully populated.

    path_t newCachePath = getNextCacheFileName();
    int wFd = ::open(newCachePath.c_str(), O_WRONLY | O_LARGEFILE);
    ftruncate(wFd, workCacheMap.getAllocSize());

    if (cacheFileRef.exists())
    {
      int cFd = ::open(cacheFileRef.path().c_str(), O_RDONLY | O_LARGEFILE);
      fillWorkCache(cFd, wFd);
    }
    else
    {
      rebuildWorkCache(wFd);
    }

    synchronizingCache = false;
  }
}


void AssetManager::fillWorkCache(int cFd, int wFd)
{
  /*
    for each w.window:
      awlist = w.assets in w.window
      clist.clear()
      for each asset a in w.window:
        if a not in c.assets:
          note "a should compile" to clist
        else:
          note "a should copy from cCache" to clist
      cwlist.sort by address
      for each entry e in clist:
        if we need to move c.window, do that
        if compiling:
          compile e.asset to w.window
        else:
          copy e.asset from cCache
  */

  auto const & cDescEntries = currCacheMap.getAllocDescEntries();
  auto const & wDescEntries = workCacheMap.getAllocDescEntries();

  size_t wSize = workCacheMap.getAllocSize();
  size_t wOverage = (wSize % cacheMapWindowSize) > 0 ? 1 : 0;

  byte * wWin = NULL;
  byte * cWin = NULL;

  size_t wEntryIdx = 0;
  // {cOffset, {compile, name, wOffset, size}} pairs.
  // Sorted by cOffset.
  map<size_t, tuple<bool, string, size_t, size_t>> cList; 

  for (size_t wWinIdx = 0; wWinIdx < wSize / cacheMapWindowSize + wOverage; ++wWinIdx)
  {
    cList.clear();

    // Window into the new, initially empty working cache file.
    // TODO: Try with MAP_LOCKED as well? And MAP_HUGETLB?
    wWin = reinterpret_cast<byte *>
      (::mmap(wWin, cacheMapWindowSize, PROT_WRITE, 0, wFd, wWinIdx * cacheMapWindowSize));

    // Scour the current w.window for all the assets it wants. They can be copied, or compiled if there is no copy source. Record the operation in cList.
    do
    {
      auto const & wEntry = wDescEntries.vect()[wEntryIdx];
      if (auto cde = cDescEntries[wEntry.assetName]; 
          cde.has_value())
      {
        // TODO: Putting cde->offset inside the pair def makes an error. Shouldn't!
        size_t offs = cde->offset;
        cList.emplace(pair { offs, tuple 
          { false, wEntry.assetName, wEntry.offset, wEntry.dataSize }});
      }
      else
      {
        // the max index forces all moves first, then all compiles. Likely best use of thread time.
        cList.emplace(pair { numeric_limits<size_t>::max(), tuple 
          { true, wEntry.assetName, wEntry.offset, wEntry.dataSize }});
      }

    } while (wWinIdx < wDescEntries.size() &&
            wDescEntries[wEntryIdx]->offset < 
              (wWinIdx + 1) * cacheMapWindowSize);

    // If there is anything to do in this w.window,
    if (cList.size() > 0)
    {
      // Determine where in cCache we should start mmapping.
      size_t cWinIdx = cList.begin()->first / cacheMapWindowSize;

      // cList is sorted by cCache offset--we always increase cWinIdx as we roll through cCache.
      for (auto const & [cOffset, entry] : cList)
      {
        auto const & [compile, assetName, wOffset, size] = entry;

        // if we should move the c.window,
        if (cOffset >= cWinIdx + cacheMapWindowSize && compile == false)
        {
          // First wait for all the previous copy operations to complete.
          taskMan->joinAllTasks();

          // Find the correct next window.
          cWinIdx = cOffset / cacheMapWindowSize;

          // TODO: Try with MAP_LOCKED as well? And MAP_HUGETLB?
          cWin = reinterpret_cast<byte *>
            (::mmap(cWin, cacheMapWindowSize, PROT_READ, 0, cFd, cWinIdx * cacheMapWindowSize));
        }

        // Now copy or compile to populate w.window multithreadedly.
        auto task = [&, cOffset=cOffset, compile=compile, assetName=string_view(assetName), wOffset=wOffset, size=size]
        {
          // Conveniently (and purely by conincidence I'm sure) asset blocks do not cross mmap boundaries. We can always slam home the whole thing.
          if (compile)
          {
            if (auto asset = getAsset(assetName); asset)
            {
              asset->compileToBuffer(wWin + wOffset);
            }
            else
            {
              // TODO: fill with baadf00d.
              log(thId, logTags::err, fmt::format("Asset '{}' not found.", assetName));
            }
          }
          else
          {
            memcpy(wWin + wOffset, cWin + cOffset, size);
          }
        };

        taskMan->enqueueTask(task);
      }

      taskMan->joinAllTasks();
    }
  }
}



void AssetManager::rebuildWorkCache(int wFd)
{
  auto const & wDescEntries = workCacheMap.getAllocDescEntries();

  size_t wSize = workCacheMap.getAllocSize();
  size_t wOverage = (wSize % cacheMapWindowSize) > 0 ? 1 : 0;

  byte * wWin = NULL;

  size_t wEntryIdx = 0;
  map<size_t, string> wList; // {wOffset, name} pairs.

  for (size_t wWinIdx = 0; wWinIdx < wSize / cacheMapWindowSize + wOverage; ++wWinIdx)
  {
    wList.clear();

    // Window into the new, initially empty working cache file.
    // TODO: Try with MAP_LOCKED as well? And MAP_HUGETLB?
    wWin = reinterpret_cast<byte *>
      (::mmap(wWin, cacheMapWindowSize, PROT_WRITE, 0, wFd, wWinIdx * cacheMapWindowSize));

    // Scour the current w.window for all the assets it wants. They can be copied, or compiled if there is no copy source. Record the operation in cList.
    do
    {
      auto const & wEntry = wDescEntries.vect()[wEntryIdx];
      wList.emplace(pair { 0, wEntry.assetName});

    } while (wWinIdx < wDescEntries.size() &&
            wDescEntries[wEntryIdx]->offset < 
              (wWinIdx + 1) * cacheMapWindowSize);

    // If there is anything to do in this w.window,
    if (wList.size() > 0)
    {
      // wList is sorted by wCache offset.
      for (auto const & [wOffset, assetName] : wList)
      {
        // Now compile to populate w.window multithreadedly.
        auto task = [&, wOffset=wOffset, assetName=string_view(assetName)]
        {
          if (auto asset = getAsset(assetName); asset)
          {
            asset->compileToBuffer(wWin + wOffset);
          }
          else
          {
            // fill with baadf00d.
            log(thId, logTags::err, fmt::format("Asset '{}' not found.", assetName));
          }
        };

        taskMan->enqueueTask(task);
      }

      taskMan->joinAllTasks();
    }
  }
}
