#include "asset.h"

using namespace std;
using namespace overground;


Asset::Asset(string_view name)
: name_(name)
{
}


Asset::~Asset()
{

}


void Asset::loadAssetInfo(asset::asset_t const & asset)
{
  bool needsSrc = asset.srcFile.has_value();

  // TODO: prepend the paths here with apt directories
  if (needsSrc)
    { srcFile_ = FileRef(asset.srcFile.value()); }
  assFile_ = FileRef(asset.assFile);

  bool hasSrc = needsSrc && fs::is_regular_file(srcFile().value().path());
  bool hasAss = fs::is_regular_file(assFile().path());
  bool isSrcNewer = hasSrc && hasAss && srcFile().value().isNewerThan(assFile());

  bool needsToCompileSrc = (hasSrc && ! hasAss) || isSrcNewer;

  if (! hasSrc && ! hasAss)
  {
    log(thId, logTags::err, fmt::format("Asset '{}' has no source or .ass files.", name()));
  }

  // Load the asset's info. We use the src file if we'll be compiling, as that lets us to only have to parse one file for the info and data. We use the ass file otherwise because it's smaller. (Eventually the .ass files might be consolidated and binarized. It's good to have the separate path for them.)
  if (needsToCompileSrc)
  {
    loadAssetInfo_impl(srcFile_.value().path(), true, asset);
    compileToAss();
  }
  else
  {
    loadAssetInfo_impl(assFile_.path(), false, asset);
  }
}


void Asset::compileToAss()
{
  compileToAss_impl();
}


void Asset::compileToBuffer(std::byte * buffer)
{
  compileToBuffer_impl(buffer);
}


void Asset::loadAssetInfo_impl(path_t file, bool loadFromSrc, asset::asset_t const & asset)
{
  log(thId, logTags::err, fmt::format("Asset plugin '{}' does not implement required virtual function 'loadAssetInfo_impl'.", name_));
}


void Asset::compileToAss_impl()
{
  log(thId, logTags::err, fmt::format("Asset plugin '{}' does not implement required virtual function 'compileToAss_impl'.", name_));
}


void Asset::compileToBuffer_impl(std::byte * buffer)
{
  log(thId, logTags::err, fmt::format("Asset plugin '{}' does not implement required virtual function 'compileToBuffer_impl'.", name_));
}
