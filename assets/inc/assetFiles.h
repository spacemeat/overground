#ifndef ASSETDESCFILE_H
#define ASSETDESCFILE_H

#include <vector>
#include <string>
#include <algorithm>

#include "fileReference.h"

namespace overground
{
  class Asset;

  class AssetDescFile : public FileReference
  {
  public:
    AssetDescFile(path_t const & path)
      : FileReference(path) { }
  };

  class AssetDataFile : public FileReference
  {
  public:
    AssetDataFile(path_t const & path, bool asCompiledFile)
      : FileReference(path), isCompiled(asCompiledFile) { }
    
    void setClientAsset(Asset * asset)
      { assets.push_back(asset); }

    void unsetClientAsset(Asset * asset)
      { assets.erase(
        std::remove(
          assets.begin(), assets.end(), asset), 
        assets.end()); }
    
    std::vector<Asset *> const & getClientAssets() const
      { return assets; }
  
  private:
    std::vector<Asset *> assets;
    bool isCompiled;
  };
}

#endif // #ifndef ASSETDESCFILE_H
