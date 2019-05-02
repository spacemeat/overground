#include "assetPack.h"
#include <utility>

using namespace std;
using namespace overground;


AssetPack::AssetPack()
{
}


AssetPack::AssetPack(AssetPack && rhs)
: configs(move(rhs.configs)),
  materials(move(rhs.materials)),
  meshes(move(rhs.meshes)),
  models(move(rhs.models)),
  renderPasses(move(rhs.renderPasses)),
  shaders(move(rhs.shaders))
{
}


AssetPack & AssetPack::operator =(AssetPack && rhs)
{
  swap(*this, rhs);
  return *this;
}


void AssetPack::clearContents()
{
  configs.clear();
  materials.clear();
  meshes.clear();
  models.clear();
  renderPasses.clear();
  shaders.clear();
}