#ifndef FEATURES_DRAWABLEMODEL_H
#define FEATURES_DRAWABLEMODEL_H

#include "feature.h"

namespace overground
{
  class DrawableModel : public Feature
  {
  public:
    DrawableModel(tableaux::feature_t const & desc);
    virtual ~DrawableModel();
  };
}

#endif // #ifndef FEATURES_DRAWABLEMODEL_H

