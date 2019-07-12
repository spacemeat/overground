#include "fileReference.h"
#include <stdexcept>
#include <experimental/filesystem>

using namespace std;
using namespace overground;


FileReference::FileReference(
  path_t const & path)
: path(path)
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
