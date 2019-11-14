#ifndef OBJECTTREE_H
#define OBJECTTREE_H

#include <unordered_map>
#include "utils.h"
#include "asset.h"
#include "material.h"
#include "model.h"
#include "feature.h"
#include "renderPlan.h"
#include "object.h"
#include "tableauManager.h"
#include "tableau-gen.h"

namespace overground
{

  class ObjectTree
  {
  public:
    ObjectTree(std::vector<tableau::tableau_t> const & tableaux);

  private:
    // asset name -> path. Multiple assets can point to one path.
    std::unordered_map<std::string, path_t> compiledAssetFiles;

    // tableau gropu name -> asset list
    std::unordered_map<std::string, std::vector<std::string>> bufferLayouts;

    std::vector<std::unique_ptr<Object>> objects_;
    std::vector<std::unique_ptr<RenderPlan>> renderPlans_;
    std::vector<std::unique_ptr<Model>> models_;
    std::vector<std::unique_ptr<Material>> materials_;
    std::vector<std::unique_ptr<Feature>> features_;
    std::vector<std::unique_ptr<Asset>> assets_;
  };
}

#endif // #ifndef OBJECTTREE_H
