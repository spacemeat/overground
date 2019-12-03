#include <unordered_set>
#include <stack>
#include <queue>
#include "assetManager.h"
#include "assemblyManager.h"
#include "assembly-gen.h"


using namespace std;
using namespace overground;


// Called when cache is initialized and ready to use for data sourcing. Implicitly, 
void AssetManager::initializeAssetDatabase(path_t const & assemblyDir, path_t const & cacheDir, string_view assFile)
{
  workAssetMap.clear();
  workCacheMap.reset(false);

  bool assNeedsToStore = false;
  path_t assPath = fmt::format("{}\\{}", cacheDir, assFile);
//if ass file exists:
  if (fs::is_regular_file(assPath))
  {
//  load the ass file contents
    loadAssFileContents(assPath);
    auto assMtime = fs::last_write_time(assPath);
//  for each asset in assembly:
    for (auto & assetDesc : assemblyMan->getWorkingAssembly().assets.vect())
    {
//    if asset's file is_regular_file:
      path_t assetPath = fmt::format("{}\\assets\\{}", assemblyDir, assetDesc.srcFile);
      if (fs::is_regular_file(assetPath))
      {
//      stat ass file against asset file
        auto assetMtime = fs::last_write_time(assetPath);
//      if ass file is not up to date:
        if (assMtime < assetMtime)
        {
//        create plugin asset type object
          auto newAssetObj = makeAsset(assetDesc);
//        track dat ass
          workAssetMap.emplace(pair {assetDesc.name, move(newAssetObj)});
//        compute essentials like compile size and image dims
          newAssetObj->computeImportData();
          assNeedsToStore = true;
        }
//      mark asset as "ass up to date"
      }
//    else:
      else
      {      
//      mark asset as "erroneous"
        
      }
    }
  }
//  else:
  else
  {
//    for each asset file in assembly and on disk:
//      load precompile data from asset into asset database
  }

  if (assNeedsToStore)
  {
    // now shit out your ass
    storeAssFileContents(assPath);
  }
  
  // At this point the working asset database is up to date, and we are clear to create vkImage and vkBuffer objects, and begin syncing the cache file. When cache file segments are compiled or transferred, they are checked for need to be loaded and maybe a transfer gets scheduled.

  // This spawns an async thread and returns.
  synchronizeCache();
}


void AssetManager::synchronizeCache()
{
  //  if cache file exists:
  //    for each asset file in assembly and on disk:
  //      stat cache file against asset file
  //      
  //      if cache file is up to date:
  //      open cache file
  //    
}

/*
void AssetManager::trackAsset(string_view assetName, string_view tableauName, fs::path const & srcPath, fs::path const & assPath)
{
  // If we have previously started tracking this asset,
  if (auto mit = assetMap.find(string {assetName}); 
      mit != assetMap.end())
  {
    Asset & ass = * mit->second;
    auto & referencingTableaux = ass.referencingTableaux();
    // If the tableau name is not part of the tracking,
    if (auto vit = find(referencingTableaux.begin(), 
        referencingTableaux.end(), tableauName); 
        vit == referencingTableaux.end())
    {
      referencingTableaux.push_back(string {tableauName});
    }
  }

  else
  {
    // Get the appropriate plugin class for the asset type.
    if (auto it = assetPlugins.find(string(assetName));
        it != assetPlugins.end())
    {
      // Create the asset object through its plugin.
      auto asset = it->second(assetName);
      asset->referencingTableaux().push_back(string(tableauName));
      // Add asset to tracking.
      assetMap.insert({string {assetName}, move(asset)});
    }
  }  
}


void AssetManager::untrackAsset(string_view assetName, string_view tableauName)
{
  if (auto mit = assetMap.find(string {assetName}); 
      mit != assetMap.end())
  {
    Asset & ass = * mit->second;
    auto & referencingTableaux = ass.referencingTableaux();

    // If the tableau name is not part of the tracking,
    if (auto vit = find(referencingTableaux.begin(), 
        referencingTableaux.end(), tableauName); 
        vit != referencingTableaux.end())
    {
      referencingTableaux.erase(remove(referencingTableaux.begin(), referencingTableaux.end(), tableauName), referencingTableaux.end());
    }

    // If no other tableaux are using the asset, dump it.
    if (referencingTableaux.size() == 0)
    {
      assetMap.erase(string {assetName});
    }
  }
}


void AssetManager::untrackTableau(string_view tableauName)
{
  vector<string> dumps;
  for (auto mit = assetMap.begin(); mit != assetMap.end(); ++ mit)
  {
    Asset & ass = * mit->second;
    auto & referencingTableaux = ass.referencingTableaux();
    // If the tableau name is not part of the tracking,
    if (auto vit = find(referencingTableaux.begin(), 
        referencingTableaux.end(), tableauName); 
        vit != referencingTableaux.end())
    {
      ass.removeReferencingTableau(tableauName);
    }

    // If no other tableaux are using the asset, dump it.
    if (referencingTableaux.size() == 0)
      { dumps.push_back(mit->first); }
  }

  for (auto & dump : dumps)
    { assetMap.erase(dump); }
}
*/

void AssetManager::checkForUpdatedFiles() noexcept
{
  vector<string> assetsToCompile;
  vector<string> assetsToLoad;

  for (auto & [assetName, asset] : assetMap)
  {
    auto & assFile = asset->assFile();
    
    bool needsSrc = asset->srcFile().has_value;
    bool hasSrc = needsSrc && 
      fs::is_regular_file(asset->srcFile().value.path());
    bool hasAss = 
      fs::is_regular_file(assFile.path());

    // Ensure the ass is still shakin'.
    if (! hasAss && ! hasSrc)
    {
      log(thId, logTags::err, fmt::format("Asset '{}': assFile  {} was not found.", assetName, assFile));
      asset->erroneous() = true;
      continue;
    }

    if (needsSrc && hasSrc)
    {
      auto & srcFile = asset->srcFile().value();
      if (hasSrc == false)
      {
        log(thId, logTags::err, fmt::format("Asset '{}': srcFile '{}' was not found.", assetName, asset->srcFile().value()));
        asset->erroneous() = true;
        continue;
      }

      if (srcFile.hasBeenModified() ||
          hasAss == false ||
          srcFile.isNewerThan(assFile))
        { assetsToCompile.push_back(assetName); }
    }
  }

  compileAssets(assetsToCompile);
}


struct AssetDesc
{
  size_t offset;
  size_t size;
};

struct BufferDesc
{
  stringDict<AssetDesc> assets;
};

auto packingDesc = stringDict<BufferDesc> {};


void AssetManager::compileAssets(vector<string> const & assets)
{
  /*  Compute all the sizes for each asset:
        determine packing (how to back buffers) according to tableaux and config
        for each asset,
          compute the size
          add to appropriate pack
      Compare old packing to new packing:
        for each buffer we need to make,
          if buffer needs to grow,
            make a new buffer
        copy all assets that don't have to compile
        compile assets that need it
  */
  
  assembly::assembly_t const & assembly = engine->getNewAssembly();
  auto const & config = assembly.configs[assembly.usingConfig];
  auto const & tableauGroup = assembly.tableauGroups[assembly.usingTableauGroup];

  if (config.graphics.bufferStrategy == BufferStrategy::randomTableaux)
  {
    for (int i = 0; i < tableauGroup.size(); ++i)
    {
      // Run through the object tree breadth-firsrt. Any features we encounter will reference assets by name; that is an asset that needs to be loaded into the appropriate buffer.
      auto const & tableau = assembly.tableaux[tableauGroup[i]];
      queue<tableau::object_t const *> objs;
      for (auto const & obj : tableau.objects)
        { objs.push(& obj); }

      while (objs.size())
      {
        auto pobj = objs.front();
        objs.pop();

        for (auto const & kid : pobj->children)
          { objs.push(& kid); }

        for (auto const & feature : pobj->features)
        {
          // TODO: Features! Where are they stored, and how are they accessed and indexed?
        }
      }
    }
  }
}
