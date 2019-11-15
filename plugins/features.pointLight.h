#ifndef FEATURES_POINTLIGHT_H
#define FEATURES_POINTLIGHT_H

#include "feature.h"

namespace overground
{
  class PointLight : public Feature
  {
  public:
    PointLight(tableaux::feature_t const & desc);
    virtual ~PointLight();
  };
}

#endif // #ifndef FEATURES_POINTLIGHT_H

