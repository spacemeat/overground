#ifndef FEATURES_CAMERA_H
#define FEATURES_CAMERA_H

#include "feature.h"

namespace overground
{
  class Camera : public Feature
  {
  public:
    Camera(tableaux::feature_t const & desc);
    virtual ~Camera();
  };
}

#endif // #ifndef FEATURES_CAMERA_H

