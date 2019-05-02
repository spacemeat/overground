#ifndef FILEREGISTRY_H
#define FILEREGISTRY_H

#include <sys/stat.h>
#include <vector>
#include <string>
#include "assetPack.h"

namespace overground
{
  enum class FileType
  {
    Humon = 0,
    Shader,
    Image
  };

  class FileReference
  {
  public:
    FileReference(std::string const & dir, std::string const & name, FileType type);
    FileReference(FileReference && rhs);

    void addRef();
    void subRef();

    std::string const & getDir() const { return dir; }
    std::string const & getName() const { return name; }
    std::string getPath() const;
    FileType getType() const { return type; }
    time_t getModTime() const { return modTime; }
    int getRefCount() const { return refs; }
    AssetPack * getAssets() { return & assets; }

    void forceUpdate();
    bool doesNeedUpdate();

  private:
    time_t getFileModeTime() const;

    std::string dir;
    std::string name;
    FileType type;
    time_t modTime;
    int refs = 0;
    AssetPack assets;
  };


  class FileRegistry
  {
  public:
    FileRegistry() { }

    FileReference * addFile(std::string const & dir, std::string const & name, FileType type);

    std::vector<FileReference> const & getFiles() const
      { return files; }

    std::vector<FileReference> & getFiles()
      { return files; }

  private:
    std::vector<FileReference> files;
  };
}

#endif // #ifndef FILEREGISTRY_H
