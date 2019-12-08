#include "fileReference.h"
#include <stdexcept>
#include <experimental/filesystem>

using namespace std;
using namespace overground;

FileRef::FileRef(path_t const & path, fileTime_t modTime)
: filePath(path), currModTime(modTime)
{
}


bool FileRef::exists() const
{
  return fs::is_regular_file(filePath);  
}


bool FileRef::didFileChange() const
{
  workModTime = fs::last_write_time(filePath);
  if (currModTime != workModTime)
  {
    return true;
  }

  return false;
}


bool FileRef::didFileChange(bool forgetTheChange)
{
  workModTime = fs::last_write_time(filePath);
  if (currModTime != workModTime)
  {
    if (forgetTheChange)
      { forgetFileChanged(); }

    return true;
  }

  return false;
}


void FileRef::forgetFileChanged()
{
  currModTime = workModTime;
}


bool FileRef::isNewerThan(FileRef const & rhs) const
{
  return currModTime > rhs.currModTime;
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
