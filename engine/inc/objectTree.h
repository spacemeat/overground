#ifndef OBJECTTREE_H
#define OBJECTTREE_H

#include <unordered_map>
#include "utils.h"
#include "asset.h"
#include "material.h"
#include "feature.h"
#include "renderPlan.h"
#include "object.h"
#include "assembly-gen.h"
#include "allocDesc.h"

namespace overground
{
  class ObjectTree
  {
  public:
    ObjectTree(assembly::assembly_t const & assembly, std::string_view tableauGroup);

    template <typename Fn>
    void forEachFeature(Fn && visitor);
    template <typename Fn>
    void forEachRenderPlan(Fn && visitor);
    template <typename Fn>
    void forEachMaterial(Fn && visitor);
    template <typename Fn>
    void forEachAsset(Fn && visitor);

    AllocDesc const & allocDesc() const noexcept;
  private:
    // asset name -> path. Multiple assets can point to one path.
    std::unordered_map<std::string, path_t> compiledAssetFiles;

    std::vector<std::unique_ptr<Object>> objects_;
    std::vector<std::unique_ptr<RenderPlan>> renderPlans_;
    std::vector<std::unique_ptr<Material>> materials_;
    std::vector<std::unique_ptr<Feature>> features_;

    AllocDesc allocDesc_;
  };
}

#endif // #ifndef OBJECTTREE_H
