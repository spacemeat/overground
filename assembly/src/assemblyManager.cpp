#include "assemblyManager.h"
#include <unordered_set>


using namespace std;
using namespace overground;


void mergeAssemblies(assembly::assembly_t & dest, assembly::assembly_t && src)
{
  dest.configs.merge(move(src.configs));
  dest.renderPlans.merge(move(src.renderPlans));

  dest.assets.merge(move(src.assets));

  dest.materials.merge(move(src.materials));
  dest.models.merge(move(src.models));
  dest.tableaux.merge(move(src.tableaux));

  if (dest.usingConfig.size() == 0)
    { dest.usingConfig = move(src.usingConfig); }
  if (dest.usingTableauGroup.size() == 0)
    { dest.usingTableauGroup = move(src.usingTableauGroup); }
}


void AssemblyManager::setAssemblyDir(fs::path const & dir)
{
  assert(fs::is_directory(dir));

  if (assemblyDir != dir)
  {
    loadAssemblySet();
  }
}


bool AssemblyManager::checkForUpdatedFiles() noexcept
{
  // get existing assembly file set
  std::unordered_map<string, fileTime_t> extantFiles;
  for (auto & de : fs::directory_iterator(assemblyDir))
  {
    if (fs::is_regular_file(de.path()))
    { 
      extantFiles.insert(
        { de.path(), fs::last_write_time(de.path()) });
    }
  }

  bool shouldLoad = false;

  // If any files have been deleted, we need to start from scratch. This is because we don't track which assembly objects or assets came from which files. I'm frankly okay with this, as it's a rare event.
  for (auto & pathRef : assemblyPaths)
  {
    // If a file has been deleted, reload.
    if (auto it = extantFiles.find(pathRef.path()); 
        it == extantFiles.end())
    { 
      shouldLoad = true;
      break;
    }

    // If a file has been modified, reload.
    if (pathRef.hasBeenModified())
    {
      shouldLoad = true;
      break;
    }

    // Check off any extant files we know about; the rest have been added.
    extantFiles.erase(pathRef.path());
  }

  // For modifications or deletions, we reload.
  if (shouldLoad)
  {
    loadAssemblySet();
    return true;
  }

  // For only additions, we append.
  else
  {
    // TODO: parallelize.
    for (auto & [path, modTime] : extantFiles)
    {
      appendAssembly(path, modTime);
    }

    return extantFiles.size() > 0;
  }
}


bool AssemblyManager::isAssemblyChanged() const noexcept
{
  return assemblyChanged;
}


void AssemblyManager::setIsAssemblyChanged(bool forcedValue) noexcept
{
  assemblyChanged = forcedValue;
}


optional<assembly::assemblyDiffs_t> AssemblyManager::checkForUpdatedAssembly() noexcept
{
  if (assemblyChanged)
  {
    assemblyChanged = false;

    assembly::assemblyDiffs_t assemblyDiffs {};
    if (doPodsDiffer(*oldAssemblyPtr, *newAssemblyPtr, assemblyDiffs))
    {
      // assembblyDiffs now contains all the info about what has changed.
      return { assemblyDiffs };
    }
  }

  return {};
}


bool AssemblyManager::loadAssemblySet()
{
  * newAssemblyPtr = { };
  assemblyPaths.clear();

  // Load all assembly files.
  // TODO: parallelize.
  for (auto & de : fs::directory_iterator(assemblyDir))
  {
    auto s = de.symlink_status();
    if (fs::is_regular_file(s))
    {
      appendAssembly(de.path(), fs::last_write_time(de));
    }
  }
}


bool AssemblyManager::appendAssembly(fs::path const & path, fileTime_t modTime)
{
  assemblyPaths.emplace_back(path, modTime);
  auto huNode = loadHumonDataFromFile(path);
  assembly::assembly_t newAssemblyLocal;
  assembly::importPod(*huNode, newAssemblyLocal);
  mergeAssemblies(*newAssemblyPtr, move(newAssemblyLocal));

  // Notify checkForUpdatedAssembly(), which runs every frame, that assembly or assets need to be updated.
  assemblyChanged = true;
}
