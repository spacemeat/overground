#ifndef FILEREFERENCE_H
#define FILEREFERENCE_H

#include <sys/stat.h>
#include <vector>
#include <string>
#include <experimental/filesystem>
#include "utils.h"

namespace overground
{
  class FileRef
  {
  public:
    FileRef(path_t const & path, fileTime_t modTime = fileTime_t::min());
    FileRef() = default;
    FileRef(FileRef const & rhs) = default;
    FileRef(FileRef && rhs) noexcept = default;
    FileRef & operator = (FileRef const & rhs) = default;
    FileRef & operator = (FileRef && rhs) noexcept = default;

    path_t const & path() const { return filePath; }

    bool exists() const;
    bool didFileChange() const;
    bool didFileChange(bool forgetTheChange = false);
    void forgetFileChanged();
    bool isNewerThan(FileRef const & rhs) const;

  private:
    path_t filePath;
    // This is one of those cases where I feel mutable is appropriate. It's under control, folks.
    mutable fileTime_t currModTime;
    mutable fileTime_t workModTime;
  };

  class FileReference
  {
  public:
    FileReference(path_t const & path, fileTime_t modTime = fileTime_t::min());
    FileReference(FileReference && rhs);

    path_t const & getPath() const { return path; }
    fileTime_t getModTime() const { return modTime; }
    fileTime_t getModTimePrev() const { return modTimePrev; }

    void checkFileModTime();
    void forceUpdate();

    bool isModified();
    void clearModified();

  private:
    path_t path;
    fileTime_t modTime;
    fileTime_t modTimePrev;
  };
}

#endif // #ifndef FILEREFERENCE_H
