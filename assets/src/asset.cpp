#include "asset.h"

using namespace std;
using namespace overground;


Asset::Asset(asset::asset_t const & desc)
: desc(desc)
{
}


Asset::~Asset()
{

}


/*
void Asset::loadAssetInfo()
{
  bool needsSrc = desc.srcFile.has_value();

  // TODO: prepend the paths here with apt directories
  if (needsSrc)
    { srcFile = FileRef(desc.srcFile.value()); }

  bool hasSrc = needsSrc && fs::is_regular_file(srcFile.value().path());
  bool isSrcNewer = hasSrc && srcFile.value().isNewerThan(assFile());

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
*/

std::string Asset::getAssetType() const noexcept
{
  return getAssetType_impl();
}


void Asset::computeImportData()
{
  computeImportData_impl();
}


void Asset::compileToBuffer(std::byte * buffer)
{
  compileToBuffer_impl(buffer);
}


std::string Asset::getAssetType_impl() const noexcept
{
  log(thId, logTags::err, fmt::format("Asset plugin '{}' does not implement required virtual function 'loadAssetInfo_impl'.", desc.name));
}


/*
void Asset::loadAssetInfo_impl(path_t file, bool loadFromSrc)
{
  log(thId, logTags::err, fmt::format("Asset plugin '{}' does not implement required virtual function 'loadAssetInfo_impl'.", desc.name));
}
*/


void Asset::computeImportData_impl()
{
  log(thId, logTags::err, fmt::format("Asset plugin '{}' does not implement required virtual function 'compileToAss_impl'.", desc.name));
}


void Asset::compileToBuffer_impl(std::byte * buffer)
{
  log(thId, logTags::err, fmt::format("Asset plugin '{}' does not implement required virtual function 'compileToBuffer_impl'.", desc.name));
}
