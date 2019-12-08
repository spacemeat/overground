#ifndef ASSEMBLYMANAGER_H
#define ASSEMBLYMANAGER_H

#include <string>
#include <array>
#include <vector>
#include <optional>
#include <variant>
#include <thread>
#include <atomic>
#include "utils.h"
#include "fileReference.h"
#include "graphicsUtils.h"
#include "enumParsers.h"
#include "assembly-gen.h"


namespace overground
{
  class AssemblyManager
  {
  public:
    AssemblyManager();
    ~AssemblyManager();

    // Wipes out all objects, sets the dir, loads new assemblyState, records diffs
    void setAssemblyDir(fs::path const & dir);

    void heyCheckFiles();

    void checkForUpdatedFiles();

    void checkForFileChanges();
    void checkForChanges();
  private:
    void buildWorkAssemblyDescs();
    void buildWorkAssemblyObjects();
  public:
    bool didAssemblyFilesChange() const noexcept;
    void forgetAssemblyFilesChanged();
    bool didAssemblyDescsChange() const noexcept;
    void forgetAssemblyDescsChanged();

    inline assembly::assembly_t const & getCurrAssemblyDesc() const noexcept;
    // NOTE: Changes can be made to the returned assembly object, but they won't be integrated without calling latchAssemblyDescChanges().
    inline assembly::assembly_t & getWorkAssemblyDesc() noexcept;

    // NOTE: You can make changes to this object, which will persist until checkForChanges() is called. Changes here will force objects to be updated, even if they're up to date, so it's best to leave it to the doPodsDiffer() implementations.
    inline assembly::assemblyDiffs_t & getWorkAssemblyDescDiffs() noexcept;

    void latchAssembblyDescChanges();
  private:
    void swapAssemblyPtrs() noexcept;
    void updateActiveTableaux(std::vector<std::string> const & tableaux);
    bool loadAssemblySet();
    bool appendAssembly(fs::path const & path, fileTime_t modTime);

    bool dying = false;

    assembly::assembly_t currAssemblyDesc;
    assembly::assembly_t workAssemblyDesc;

    assembly::assemblyDiffs_t workAssemblyDiffs;
    fs::path assemblyDir;
    std::vector<FileRef> loadedAsmPaths;

    std::thread bgThread;
    std::atomic<bool> checkingAssemblyFiles = false;

    std::thread loadAssemblySetThread;
    std::atomic<bool> buildingWorkAssemblySet = false;

    std::atomic<bool> shouldCheckFiles = false;

    std::atomic<bool> assemblyFilesChanged = false;
    
    std::atomic<bool> assemblyDescsChanged = false;
  };


  inline assembly::assembly_t const & AssemblyManager::getCurrentAssemblyDesc() const noexcept
  {
    return currAssemblyDesc;
  }

  inline assembly::assembly_t & AssemblyManager::getWorkingAssemblyDesc() noexcept
  {
    return workAssemblyDesc;
  }

  inline assembly::assemblyDiffs_t & AssemblyManager::getWorkAssemblyDescDiffs() noexcept
  {
    return workAssemblyDiffs;
  }

  inline std::optional<AssemblyManager> assemblyMan;
}


#endif // #ifndef ASSEMBLYMANAGER_H
