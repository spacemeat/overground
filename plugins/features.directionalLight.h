#ifndef FEATURES_DIRECTIONALLIGHT_H
#define FEATURES_DIRECTIONALLIGHT_H

#include "feature.h"

namespace overground
{
  class DirectionalLight : public Feature
  {
  public:
    DirectionalLight(tableaux::feature_t const & desc);
    virtual ~DirectionalLight();
  };
}

#endif // #ifndef FEATURES_DIRECTIONALLIGHT_H

