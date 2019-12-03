#ifndef FEATURES_DRAWABLEMODEL_H
#define FEATURES_DRAWABLEMODEL_H

#include "tableau-gen.h"

namespace overground
{
  class DrawableMesh : public Feature
  {
  public:
    DrawableMesh(tableau::feature_t const & desc);
    virtual ~DrawableMesh();
  };
}

#endif // #ifndef FEATURES_DRAWABLEMODEL_H

