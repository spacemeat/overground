#include <numeric>
#include "objectTree.h"
#include "object.h"
#include "graphics.h"

using namespace std;
using namespace overground;


ObjectTree::ObjectTree(assembly::assembly_t const & assembly, std::string_view tableauGroup)
{
  for (auto & tableauIdx : assembly.tableauGroups[tableauGroup])
  {
    auto & tab = assembly.tableaux[tableauIdx];

    for (auto const & obj : tab.objects.vect())
    {
      auto objC = makeObject(obj);
      objects_.push_back(move(objC));

      Object * objP = objects_.back().get();
      
      for (auto & fea : obj.features)
      {
        auto feaC = make_unique<Feature>(fea);
        features_.push_back(move(feaC));
      }
    }
  }

  allocDesc_.reset(true);

  // compute buffer/image order for device memory
  forEachAsset([&](Asset * asset)
    { allocDesc_.trackAsset(asset->name); });

  allocDesc_.computeMap();
}
