#ifndef ASSET_PACK_H
#define ASSET_PACK_H

#include <vector>
#include "config.h"
#include "material.h"
#include "mesh.h"
#include "model.h"
#include "renderPass.h"
#include "shader.h"

namespace overground
{
  class AssetPack
  {
  public:
    std::vector<Config> configs;
    std::vector<Material> materials;
    std::vector<Mesh> meshes;
    std::vector<Model> models;
    std::vector<RenderPass> renderPasses;
    std::vector<Shader> shaders;
  };
}

#endif // #ifnddf ASSET_PACK_H