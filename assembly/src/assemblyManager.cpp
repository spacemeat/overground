#include "assemblyManager.h"
#include <unordered_set>
#include <thread>


using namespace std;
using namespace overground;


void mergeAssemblies(assembly::assembly_t & dest, assembly::assembly_t && src)
{
  dest.configs.merge(move(src.configs));
  dest.renderPlans.merge(move(src.renderPlans));

  dest.assets.merge(move(src.assets));

  dest.materials.merge(move(src.materials));
  dest.tableaux.merge(move(src.tableaux));

  if (dest.usingConfig.size() == 0)
    { dest.usingConfig = move(src.usingConfig); }
  if (dest.usingTableauGroup.size() == 0)
    { dest.usingTableauGroup = move(src.usingTableauGroup); }
}


AssemblyManager::AssemblyManager()
{
  bgThread = thread([this](){ checkForFileChanges(); });
}


AssemblyManager::~AssemblyManager()
{
  if (bgThread.joinable())
    { bgThread.join(); }
}


void AssemblyManager::setAssemblyDir(fs::path const & dir)
{
  assert(fs::is_directory(dir));

  if (assemblyDir != dir)
  {
    assemblyFilesChanged = true;
  }
}


// Call this once every n00 ms.
void AssemblyManager::heyCheckFiles()
{
  shouldCheckFiles = true;
}


void AssemblyManager::checkForFileChanges()
{
  while (dying == false)
  {
    if (shouldCheckFiles)
    {
      shouldCheckFiles = false;
      checkForUpdatedFiles();

      if (assemblyFilesChanged)
      {
        assemblyFilesChanged = false;
        // builds the _t structs (pods)
        buildWorkAssemblyDescs();
      }
    }
  }
}


// Runs in its own thread. Can take its time.
void AssemblyManager::checkForUpdatedFiles()
{
  if (checkingAssemblyFiles)
    { return; }

  checkingAssemblyFiles = true;
  // clear the flag on fn exit
  FlagRaiiser fr(checkingAssemblyFiles, false);

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

  bool filesChanged = false;

  // If any files have been deleted, we need to start from scratch. This is because we don't track which assembly objects or assets came from which files. I'm mildly okay with this, as it's a rare event.
  for (auto & pathRef : loadedAsmPaths)
  {
    // If a file has been deleted, reload.
    if (auto it = extantFiles.find(pathRef.path()); 
        it == extantFiles.end())
    { 
      filesChanged = true;
      break;
    }

    // If a file has been modified, reload.
    if (pathRef.didFileChange())
    {
      pathRef.forgetFileChanged();
      filesChanged = true;
      break;
    }

    // Check off any extant files we know about; the rest have been added.
    extantFiles.erase(pathRef.path());
  }

  // We also need to rebuld if new files have been added.
  assemblyFilesChanged = filesChanged || 
    extantFiles.size() > 0;
}


void AssemblyManager::buildWorkAssemblyDescs()
{
  if (buildingWorkAssemblySet)
    { return; }

  buildingWorkAssemblySet = true;
  // clear the flag on fn exit
  FlagRaiiser fr(buildingWorkAssemblySet, false);

  loadedAsmPaths.clear();

  // Load all assembly files.
  // Not parallelizing since we're a background thread.
  // TODO: parallelize on the up-front load case.
  for (auto & de : fs::directory_iterator(assemblyDir))
  {
    auto s = de.symlink_status();
    if (fs::is_regular_file(s))
    {
      appendAssembly(de.path(), fs::last_write_time(de));
    }
  }

  assemblyDescsChanged = true;
}


bool AssemblyManager::appendAssembly(fs::path const & path, fileTime_t modTime)
{
  loadedAsmPaths.emplace_back(path, modTime);
  auto huNode = loadHumonDataFromFile(path);
  assembly::assembly_t newAssemblyLocal;
  assembly::importPod(*huNode, newAssemblyLocal);
  mergeAssemblies(workAssemblyDesc, move(newAssemblyLocal));
}


bool AssemblyManager::didAssemblyFilesChange() const noexcept
{
  return assemblyFilesChanged;
}


void AssemblyManager::forgetAssemblyFilesChanged()
{
  assemblyFilesChanged = false;
}


bool AssemblyManager::didAssemblyDescsChange() const noexcept
{
  return assemblyDescsChanged;
}


void AssemblyManager::forgetAssemblyDescsChanged()
{
  assemblyDescsChanged = false;
}


void AssemblyManager::latchAssembblyDescChanges()
{
  assemblyDescsChanged = true;
}
