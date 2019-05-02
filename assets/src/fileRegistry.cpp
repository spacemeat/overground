#include "fileRegistry.h"
#include <stdexcept>

using namespace std;
using namespace overground;


FileReference::FileReference(string const & dir, string const & name, FileType type, time_t mTime)
: dir(dir), name(name), type(type), modTime(mTime)
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


FileReference * FileRegistry::addFile(string const & dir, string const & name, FileType type)
{
  struct stat stats;
  string path = dir + "/" + name; // TODO: path separator
  if (stat(path.c_str(), & stats) != 0)
    // TODO: Better codepath on fail
    { throw runtime_error("Could not stat."); }
  
  auto & fref = files.emplace_back(dir, name, type, stats.st_mtime);
  return & fref;
}
