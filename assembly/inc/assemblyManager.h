#ifndef ASSEMBLYMANAGER_H
#define ASSEMBLYMANAGER_H

#include <string>
#include <array>
#include <vector>
#include <optional>
#include <variant>
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
    // Wipes out all objects, sets the dir, loads new assemblyState, records diffs
    void setAssemblyDir(fs::path const & dir);
    bool checkForUpdatedFiles() noexcept;
    bool isAssemblyChanged() const noexcept;
    void setIsAssemblyChanged(bool forcedValue) noexcept;
    std::optional<assembly::assemblyDiffs_t> checkForUpdatedAssembly() noexcept;

    // NOTE: This reference is stale once isAssemblyChanged() == true.
    inline assembly::assembly_t const & getCurrentAssembly() const noexcept;
    // NOTE: Changes can be made to the returned assembly object, but they won't be integrated without calling setIsAssemblyChanged(true). If files are changed in the meantime and checkForUpdatedFiles() is called, then pending changes may be overwritten. I'm calling this undefined behavior, so be sure to latch changes with setIsAssemblyChanged(true).
    // NOTE: This reference is stale once isAssemblyChanged() == true.
    inline assembly::assembly_t & getWorkingAssembly() const noexcept;

    // NOTE: You can make changes to this object, which will persist until checkForUpdatedAssembly() is called. Changes here will force objects to be updated, even if they're up to date, so it's best to leave it to the doPodsDiffer() implementations.
    inline assembly::assemblyDiffs_t & getAssemblyDiffs() noexcept;

  private:
    void swapAssemblyPtrs() noexcept;
    void updateActiveTableaux(std::vector<std::string> const & tableaux);
    bool loadAssemblySet();
    bool appendAssembly(fs::path const & path, fileTime_t modTime);

    std::array<assembly::assembly_t, 2> assemblies;
    assembly::assembly_t * oldAssemblyPtr = & assemblies[0];
    assembly::assembly_t * newAssemblyPtr = & assemblies[1];
    assembly::assemblyDiffs_t assemblyDiffs;
    fs::path assemblyDir;
    std::vector<FileRef> assemblyPaths;

    bool assemblyChanged = false;
  };


  inline assembly::assembly_t const & AssemblyManager::getCurrentAssembly() const noexcept
  {
    return * oldAssemblyPtr;
  }

  inline assembly::assembly_t & AssemblyManager::getWorkingAssembly() const noexcept
  {
    return * newAssemblyPtr;
  }

  inline assembly::assemblyDiffs_t & AssemblyManager::getAssemblyDiffs() noexcept
  {
    return assemblyDiffs;
  }

  static inline std::optional<AssemblyManager> assemblyMan;
}


#endif // #ifndef ASSEMBLYMANAGER_H
