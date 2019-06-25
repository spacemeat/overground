#ifndef FILEREGISTRY_H
#define FILEREGISTRY_H

#include <sys/stat.h>
#include <vector>
#include <string>
#include <experimental/filesystem>
#include "assetPack.h"

namespace overground
{
  class FileReference
  {
  public:
    FileReference(path_t const & path);
    FileReference(FileReference && rhs);

    path_t const & getPath() const { return path; }
    fileTime_t getModTime() const { return modTime; }

    void updateFileModTime();
    void forceUpdate();

    bool doesNeedUpdate();
    void setUpdated();

  private:
    path_t path;
    fileTime_t modTime;
    fileTime_t modTimePrev;
  };
}

#endif // #ifndef FILEREGISTRY_H
