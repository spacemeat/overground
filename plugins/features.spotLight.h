#ifndef FEATURES_SPOTLIGHT_H
#define FEATURES_SPOTLIGHT_H

#include "feature.h"

namespace overground
{
  class SpotLight : public Feature
  {
  public:
    SpotLight(tableaux::feature_t const & desc);
    virtual ~SpotLight();
  };
}

#endif // #ifndef FEATURES_SPOTLIGHT_H

