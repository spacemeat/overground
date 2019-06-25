#include "fileReference.h"
#include <stdexcept>
#include <experimental/filesystem>

using namespace std;
using namespace overground;


FileReference::FileReference(
  fs::path const & path)
: path(path)
{
}


FileReference::FileReference(FileReference && rhs)
{
  path = move(rhs.path);
  modTime = rhs.modTime;
  modTimePrev = rhs.modTimePrev;
}


void FileReference::updateFileModTime()
{
  modTime = fs::last_write_time(path);
}


void FileReference::forceUpdate()
{
  modTimePrev = decltype(modTimePrev)();
}


bool FileReference::doesNeedUpdate()
{
  return modTimePrev != modTime;
}


void FileReference::setUpdated()
{
  modTime = modTimePrev;
}
