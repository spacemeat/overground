#ifndef ASSET_PACK_H
#define ASSET_PACK_H

#include <vector>
#include <atomic>
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
    AssetPack();
    AssetPack(AssetPack && rhs);

    AssetPack & operator =(AssetPack && rhs);

    bool hasUpdates() { return updated; }

    void markUpdated() {
      updated = true;
    }

    void clearUpdateMark() {
      updated = false;
    }

    void clearContents();

    std::atomic<bool> updated = false;

    std::vector<Config> configs;
    std::vector<Material> materials;
    std::vector<Mesh> meshes;
    std::vector<Model> models;
    std::vector<RenderPass> renderPasses;
    std::vector<Shader> shaders;
  };
}

#endif // #ifnddf ASSET_PACK_H