#include <fstream>
#include <queue>
#include <string>
#include "utils.h"
#include "logger.h"

using namespace std;
using namespace overground;


path_t overground::findFile(string_view filename, string_view baseDir)
{
  queue<path_t> searchDirs;
  searchDirs.push(path_t(baseDir));
  while (searchDirs.size())
  {
    auto searchDir = searchDirs.front();
    searchDirs.pop();
    for (auto & p : fs::directory_iterator(searchDir))
    {
      if (p.path().filename() == filename)
        { return p; }

      if (fs::is_directory(p))
        { searchDirs.push(p); }
    }
  }

  throw runtime_error("Could not find file.");
}


string overground::loadFileAsString(path_t const & path)
{
  string strContent;
  auto ifs = ifstream(path);
  if (ifs.is_open())
  {
    strContent = string(
      (istreambuf_iterator<char>(ifs)),
      (istreambuf_iterator<char>()));
  }

  return strContent;
}


vector<char> overground::loadFileAsBinary(path_t const & path)
{
  auto ifs = ifstream(path, std::ios::ate | std::ios::binary);
  if (ifs.is_open())
  {
    auto sz = ifs.tellg();
    vector<char> binContent(sz);
    ifs.seekg(0);
    ifs.read(binContent.data(), sz);

    return binContent;
  }

  throw runtime_error("Can't open the file");
}


humon::nodePtr_t overground::loadHumonDataFromFile(path_t const & path)
{
  return humon::fromString(
    loadFileAsString(path)
  );
}
