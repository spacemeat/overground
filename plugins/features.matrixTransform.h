#ifndef FEATURES_MATRIXTRANSFORM_H
#define FEATURES_MATRIXTRANSFORM_H

#include "feature.h"

namespace overground
{
  class MatrixTransform : public Feature
  {
  public:
    MatrixTransform(tableaux::feature_t const & desc);
    virtual ~MatrixTransform();
  };
}

#endif // #ifndef FEATURES_MATRIXTRANSFORM_H

