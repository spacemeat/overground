#include "fileReference.h"
#include <stdexcept>
#include <experimental/filesystem>

using namespace std;
using namespace overground;

FileRef::FileRef(path_t const & path, fileTime_t modTime)
: filePath(path), modTime(modTime)
{
}


bool FileRef::hasBeenModified() const
{
  auto newModTime = fs::last_write_time(filePath);
  if (modTime != newModTime)
  {
    modTime = newModTime;
    return true;
  }

  return false;
}

bool FileRef::isNewerThan(FileRef const & rhs) const
{
  return modTime > rhs.modTime;
}



FileReference::FileReference(
  path_t const & path, fileTime_t modTime)
: path(path), modTime(modTime), modTimePrev(modTime)
{
}


FileReference::FileReference(FileReference && rhs)
{
  path = move(rhs.path);
  modTime = rhs.modTime;
  modTimePrev = rhs.modTimePrev;
}


void FileReference::checkFileModTime()
{
  modTime = fs::last_write_time(path);
}


void FileReference::forceUpdate()
{
  modTimePrev = decltype(modTimePrev)();
}


bool FileReference::isModified()
{
  if (modTime != modTimePrev)
  {
    log(thId, "isModified == true");
  }
  return modTime != modTimePrev;
}


void FileReference::clearModified()
{
  modTimePrev = modTime;
}
