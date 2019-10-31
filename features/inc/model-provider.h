#ifndef MODEL_PROVIDER_H
#define MODEL_PROVIDER_H

#include "featureManager.h"

namespace overground
{
  class ModelFeature : public PluginFeatureBase
  {
    ModelFeature(tableau::feature_t const & desc);
    virtual ~ModelFeature();
  };


  ModelFeature::ModelFeature(tableau::feature_t const & desc)
  : PluginFeatureBase(desc)
  {
    auto & model = get<tableau::drawableModel_t>(desc.data);

    trackAsset(model.mesh);
    for (auto & sub : model.subModels)
    {
      if (sub.material.has_value())
        { trackFeature(sub.material.value); }
    }
  }


  ModelFeature::~ModelFeature()
  {

  }
}

#endif // ifndef MODEL_PROVIDER_H
