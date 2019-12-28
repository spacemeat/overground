#ifndef PLUGINS_GEN_H
#define PLUGINS_GEN_H


#include <string_view>
#include "assets.mesh.h"
#include "assets.image.h"
#include "assets.cubeMapImage.h"
#include "assets.shader.h"
#include "features.matrixTransform.h"
#include "features.srtTransform.h"
#include "features.drawableMesh.h"
#include "features.directionalLight.h"
#include "features.pointLight.h"
#include "features.spotLight.h"
#include "features.camera.h"
#include "objects.otherKindOfObject.h"

namespace overground
{
  enum class assetsPluginTypes_e
  {
    mesh,
    image,
    cubeMapImage,
    shader,
  };

  constexpr std::string_view assetsPluginTypes[] = 
  {
    "mesh"sv,
    "image"sv,
    "cubeMapImage"sv,
    "shader"sv,
  };

  enum class featuresPluginTypes_e
  {
    matrixTransform,
    srtTransform,
    drawableMesh,
    directionalLight,
    pointLight,
    spotLight,
    camera,
  };

  constexpr std::string_view featuresPluginTypes[] = 
  {
    "matrixTransform"sv,
    "srtTransform"sv,
    "drawableMesh"sv,
    "directionalLight"sv,
    "pointLight"sv,
    "spotLight"sv,
    "camera"sv,
  };

  enum class objectsPluginTypes_e
  {
    otherKindOfObject,
  };

  constexpr std::string_view objectsPluginTypes[] = 
  {
    "otherKindOfObject"sv,
  };

}

#endif // #ifndef PLUGINS_GEN_H
