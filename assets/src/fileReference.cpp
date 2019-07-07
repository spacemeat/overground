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
  auto mt = decltype(modTime)::clock::to_time_t(modTime);
  sout {} << "modTime:     "
    << std::asctime(std::localtime(& mt));

  modTime = fs::last_write_time(path);

  auto pmt = decltype(modTime)::clock::to_time_t(modTime);
  sout {} << "modTime:     "
    << std::asctime(std::localtime(& pmt))
    << " (same? " << (mt == pmt ? "yes" : "no")
    << endl;
}


void FileReference::forceUpdate()
{
  modTimePrev = decltype(modTimePrev)();
}


bool FileReference::isModified()
{
  return modTime != modTimePrev;
}


void FileReference::clearModified()
{
  modTimePrev = modTime;
}
