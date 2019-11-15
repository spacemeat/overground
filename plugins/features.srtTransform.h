#ifndef FEATURES_SRTTRANSFORM_H
#define FEATURES_SRTTRANSFORM_H

#include "feature.h"

namespace overground
{
  class SrtTransform : public Feature
  {
  public:
    SrtTransform(tableaux::feature_t const & desc);
    virtual ~SrtTransform();
  };
}

#endif // #ifndef FEATURES_SRTTRANSFORM_H

