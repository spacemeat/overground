#ifndef FEATURES_DRAWABLEMESH_H
#define FEATURES_DRAWABLEMESH_H

#include "materialManager.h"
#include "material.h"
#include "feature.h"

namespace overground
{
  class DrawableMesh : public Feature
  {
  public:
    DrawableMesh(tableau::feature_t const & desc);
    virtual ~DrawableMesh();

    virtual void forEachGraphicsSubresourceNeeded(
      reportGraphicsSubresourceFn_t reportFn) override;

  private:
    std::string mesh;                   // stored by name for now
    std::vector<std::string> materials; // stored by name for now
  };


  void DrawableMesh::forEachGraphicsSubresourceNeeded(
    Feature::reportGraphicsSubresourceFn_t reportFn)
  {
    for (auto & matName : materials)
    {
      auto material = materialMan->getMaterial(matName);
      if (material.has_value() == false)
        { continue; }

      auto & descriptors = material->getRequiredResources();
      for (auto & [_, desc] : descriptors)
      {
        if (desc.)
        reportFn()
      }
    }
  }
}

#endif // #ifndef FEATURES_DRAWABLEMESH_H

