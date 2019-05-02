#include "fileRegistry.h"
#include <stdexcept>

using namespace std;
using namespace overground;


FileReference::FileReference(string const & dir, string const & name, FileType type)
: dir(dir), name(name), type(type), 
  modTime(0)
{
}


FileReference::FileReference(FileReference && rhs)
{
  dir = move(rhs.dir);
  name = move(rhs.name);
  type = rhs.type;
  modTime = rhs.modTime;
  refs = rhs.refs;
  assets = move(rhs.assets);
}


void FileReference::addRef() 
{
  refs += 1;
}


void FileReference::subRef()
{
  refs -= 1;
}


string FileReference::getPath() const
{
  return dir + "/" + name; // TODO: path separator
}


void FileReference::forceUpdate()
{
  modTime = 0;
}


bool FileReference::doesNeedUpdate()
{
  auto newMtime = getFileModeTime();
  if (newMtime != modTime)
  {
    modTime = newMtime;
    return true;
  }
  return false;
}


time_t FileReference::getFileModeTime() const
{
  struct stat stats;
  string path = dir + "/" + name; // TODO: path separator
  if (stat(path.c_str(), & stats) != 0)
    // TODO: Better codepath on fail
    { throw runtime_error("Could not stat."); }

  return stats.st_mtime;
}


FileReference * FileRegistry::addFile(string const & dir, string const & name, FileType type)
{  
  auto & fref = files.emplace_back(dir, name, type);
  return & fref;
}
