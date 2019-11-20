#ifndef tableau_GEN_H
#define tableau_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  namespace tableau
  {
    // matrixTransform things

    struct matrixTransform_t
    {
      std::string type;
      std::array<float, 16> transform;
    };

    void importPod(
      humon::HuNode const & src, matrixTransform_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, matrixTransform_t & dest);

    void exportPod(matrixTransform_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      matrixTransform_t const & src, std::vector<uint8_t> & dest);

    std::string print(matrixTransform_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, matrixTransform_t const & src);

    enum class matrixTransformMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      transform = 1 << 1,
      all = type | transform
    };

    inline bool operator == (matrixTransform_t const & lhs, matrixTransform_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.transform == rhs.transform;
    };

    inline bool operator != (matrixTransform_t const & lhs, matrixTransform_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct matrixTransformDiffs_t
    {
      matrixTransformMembers_e diffs;
      std::vector<size_t> transformDiffs;
    };

    inline bool doPodsDiffer(
      matrixTransform_t const & lhs,
      matrixTransform_t const & rhs,
      matrixTransformDiffs_t & matrixTransform) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { matrixTransform.diffs |= matrixTransformMembers_e::type; }
      // diff member 'transform':
      for (size_t i = 0; i < lhs.transform.size(); ++i)
      {
        if (lhs.transform[i] != rhs.transform[i])
        {
          matrixTransform.diffs |= matrixTransformMembers_e::transform;
          matrixTransform.transformDiffs.push_back(i);
        }
      }

      return matrixTransform.diffs != matrixTransformMembers_e::none;
    };

    // srtTransform things

    struct srtTransform_t
    {
      std::string type;
      std::array<float, 3> scale;
      std::array<float, 3> rotation;
      std::array<float, 3> translate;
    };

    void importPod(
      humon::HuNode const & src, srtTransform_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, srtTransform_t & dest);

    void exportPod(srtTransform_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      srtTransform_t const & src, std::vector<uint8_t> & dest);

    std::string print(srtTransform_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, srtTransform_t const & src);

    enum class srtTransformMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      scale = 1 << 1,
      rotation = 1 << 2,
      translate = 1 << 3,
      all = type | scale | rotation | translate
    };

    inline bool operator == (srtTransform_t const & lhs, srtTransform_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.scale == rhs.scale &&
        lhs.rotation == rhs.rotation &&
        lhs.translate == rhs.translate;
    };

    inline bool operator != (srtTransform_t const & lhs, srtTransform_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct srtTransformDiffs_t
    {
      srtTransformMembers_e diffs;
      std::vector<size_t> scaleDiffs;
      std::vector<size_t> rotationDiffs;
      std::vector<size_t> translateDiffs;
    };

    inline bool doPodsDiffer(
      srtTransform_t const & lhs,
      srtTransform_t const & rhs,
      srtTransformDiffs_t & srtTransform) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { srtTransform.diffs |= srtTransformMembers_e::type; }
      // diff member 'scale':
      for (size_t i = 0; i < lhs.scale.size(); ++i)
      {
        if (lhs.scale[i] != rhs.scale[i])
        {
          srtTransform.diffs |= srtTransformMembers_e::scale;
          srtTransform.scaleDiffs.push_back(i);
        }
      }
      // diff member 'rotation':
      for (size_t i = 0; i < lhs.rotation.size(); ++i)
      {
        if (lhs.rotation[i] != rhs.rotation[i])
        {
          srtTransform.diffs |= srtTransformMembers_e::rotation;
          srtTransform.rotationDiffs.push_back(i);
        }
      }
      // diff member 'translate':
      for (size_t i = 0; i < lhs.translate.size(); ++i)
      {
        if (lhs.translate[i] != rhs.translate[i])
        {
          srtTransform.diffs |= srtTransformMembers_e::translate;
          srtTransform.translateDiffs.push_back(i);
        }
      }

      return srtTransform.diffs != srtTransformMembers_e::none;
    };

    // drawableSubmesh things

    struct drawableSubmesh_t
    {
      std::string submesh;
      std::string material;
      std::vector<std::string> tags;
    };

    void importPod(
      humon::HuNode const & src, drawableSubmesh_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, drawableSubmesh_t & dest);

    void exportPod(drawableSubmesh_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      drawableSubmesh_t const & src, std::vector<uint8_t> & dest);

    std::string print(drawableSubmesh_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, drawableSubmesh_t const & src);

    enum class drawableSubmeshMembers_e : int 
    {
      none = 0,
      submesh = 1 << 0,
      material = 1 << 1,
      tags = 1 << 2,
      all = submesh | material | tags
    };

    inline bool operator == (drawableSubmesh_t const & lhs, drawableSubmesh_t const & rhs) noexcept
    {
      return
        lhs.submesh == rhs.submesh &&
        lhs.material == rhs.material &&
        lhs.tags == rhs.tags;
    };

    inline bool operator != (drawableSubmesh_t const & lhs, drawableSubmesh_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct drawableSubmeshDiffs_t
    {
      drawableSubmeshMembers_e diffs;
      std::vector<size_t> tagsDiffs;
    };

    inline bool doPodsDiffer(
      drawableSubmesh_t const & lhs,
      drawableSubmesh_t const & rhs,
      drawableSubmeshDiffs_t & drawableSubmesh) noexcept
    {
      // diff member 'submesh':
      if (lhs.submesh != rhs.submesh)
        { drawableSubmesh.diffs |= drawableSubmeshMembers_e::submesh; }
      // diff member 'material':
      if (lhs.material != rhs.material)
        { drawableSubmesh.diffs |= drawableSubmeshMembers_e::material; }
      // diff member 'tags':
      {
        auto [mn, mx] = std::minmax(lhs.tags.size(), rhs.tags.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.tags[i] != rhs.tags[i])
          {
            drawableSubmesh.diffs |= drawableSubmeshMembers_e::tags;
            drawableSubmesh.tagsDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          drawableSubmesh.tagsDiffs.push_back(i);
        }
      }

      return drawableSubmesh.diffs != drawableSubmeshMembers_e::none;
    };

    // drawableMesh things

    struct drawableMesh_t
    {
      std::string type;
      std::string mesh;
      std::vector<drawableSubmesh_t> subMeshes;
    };

    void importPod(
      humon::HuNode const & src, drawableMesh_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, drawableMesh_t & dest);

    void exportPod(drawableMesh_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      drawableMesh_t const & src, std::vector<uint8_t> & dest);

    std::string print(drawableMesh_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, drawableMesh_t const & src);

    enum class drawableMeshMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      mesh = 1 << 1,
      subMeshes = 1 << 2,
      all = type | mesh | subMeshes
    };

    inline bool operator == (drawableMesh_t const & lhs, drawableMesh_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.mesh == rhs.mesh &&
        lhs.subMeshes == rhs.subMeshes;
    };

    inline bool operator != (drawableMesh_t const & lhs, drawableMesh_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct drawableMeshDiffs_t
    {
      drawableMeshMembers_e diffs;
      std::vector<std::pair<size_t, drawableSubmeshDiffs_t>> subMeshesDiffs;
    };

    inline bool doPodsDiffer(
      drawableMesh_t const & lhs,
      drawableMesh_t const & rhs,
      drawableMeshDiffs_t & drawableMesh) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { drawableMesh.diffs |= drawableMeshMembers_e::type; }
      // diff member 'mesh':
      if (lhs.mesh != rhs.mesh)
        { drawableMesh.diffs |= drawableMeshMembers_e::mesh; }
      // diff member 'subMeshes':
      {
        auto [mn, mx] = std::minmax(lhs.subMeshes.size(), rhs.subMeshes.size());
        for (size_t i = 0; i < mn; ++i)
        {
          drawableSubmeshDiffs_t diffsEntry;
          if (doPodsDiffer(lhs.subMeshes[i], rhs.subMeshes[i], diffsEntry))
          {
            drawableMesh.diffs |= drawableMeshMembers_e::subMeshes;
            drawableMesh.subMeshesDiffs.push_back({i, diffsEntry});
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          drawableSubmeshDiffs_t diffsEntry = { .diffs = drawableSubmeshMembers_e::all };
          drawableMesh.subMeshesDiffs.push_back({i, diffsEntry});
        }
      }

      return drawableMesh.diffs != drawableMeshMembers_e::none;
    };

    // directionalLight things

    struct directionalLight_t
    {
      std::string type;
      std::array<float, 3> color;
    };

    void importPod(
      humon::HuNode const & src, directionalLight_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, directionalLight_t & dest);

    void exportPod(directionalLight_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      directionalLight_t const & src, std::vector<uint8_t> & dest);

    std::string print(directionalLight_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, directionalLight_t const & src);

    enum class directionalLightMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      color = 1 << 1,
      all = type | color
    };

    inline bool operator == (directionalLight_t const & lhs, directionalLight_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.color == rhs.color;
    };

    inline bool operator != (directionalLight_t const & lhs, directionalLight_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct directionalLightDiffs_t
    {
      directionalLightMembers_e diffs;
      std::vector<size_t> colorDiffs;
    };

    inline bool doPodsDiffer(
      directionalLight_t const & lhs,
      directionalLight_t const & rhs,
      directionalLightDiffs_t & directionalLight) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { directionalLight.diffs |= directionalLightMembers_e::type; }
      // diff member 'color':
      for (size_t i = 0; i < lhs.color.size(); ++i)
      {
        if (lhs.color[i] != rhs.color[i])
        {
          directionalLight.diffs |= directionalLightMembers_e::color;
          directionalLight.colorDiffs.push_back(i);
        }
      }

      return directionalLight.diffs != directionalLightMembers_e::none;
    };

    // pointLight things

    struct pointLight_t
    {
      std::string type;
      std::array<float, 3> attenuation;
      std::array<float, 3> color;
    };

    void importPod(
      humon::HuNode const & src, pointLight_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, pointLight_t & dest);

    void exportPod(pointLight_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      pointLight_t const & src, std::vector<uint8_t> & dest);

    std::string print(pointLight_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, pointLight_t const & src);

    enum class pointLightMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      attenuation = 1 << 1,
      color = 1 << 2,
      all = type | attenuation | color
    };

    inline bool operator == (pointLight_t const & lhs, pointLight_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.attenuation == rhs.attenuation &&
        lhs.color == rhs.color;
    };

    inline bool operator != (pointLight_t const & lhs, pointLight_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct pointLightDiffs_t
    {
      pointLightMembers_e diffs;
      std::vector<size_t> attenuationDiffs;
      std::vector<size_t> colorDiffs;
    };

    inline bool doPodsDiffer(
      pointLight_t const & lhs,
      pointLight_t const & rhs,
      pointLightDiffs_t & pointLight) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { pointLight.diffs |= pointLightMembers_e::type; }
      // diff member 'attenuation':
      for (size_t i = 0; i < lhs.attenuation.size(); ++i)
      {
        if (lhs.attenuation[i] != rhs.attenuation[i])
        {
          pointLight.diffs |= pointLightMembers_e::attenuation;
          pointLight.attenuationDiffs.push_back(i);
        }
      }
      // diff member 'color':
      for (size_t i = 0; i < lhs.color.size(); ++i)
      {
        if (lhs.color[i] != rhs.color[i])
        {
          pointLight.diffs |= pointLightMembers_e::color;
          pointLight.colorDiffs.push_back(i);
        }
      }

      return pointLight.diffs != pointLightMembers_e::none;
    };

    // spotLight things

    struct spotLight_t
    {
      std::string type;
      std::array<float, 3> attenuation;
      float hotspot;
      float falloff;
      std::array<float, 3> color;
    };

    void importPod(
      humon::HuNode const & src, spotLight_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, spotLight_t & dest);

    void exportPod(spotLight_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      spotLight_t const & src, std::vector<uint8_t> & dest);

    std::string print(spotLight_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, spotLight_t const & src);

    enum class spotLightMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      attenuation = 1 << 1,
      hotspot = 1 << 2,
      falloff = 1 << 3,
      color = 1 << 4,
      all = type | attenuation | hotspot | falloff | color
    };

    inline bool operator == (spotLight_t const & lhs, spotLight_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.attenuation == rhs.attenuation &&
        lhs.hotspot == rhs.hotspot &&
        lhs.falloff == rhs.falloff &&
        lhs.color == rhs.color;
    };

    inline bool operator != (spotLight_t const & lhs, spotLight_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct spotLightDiffs_t
    {
      spotLightMembers_e diffs;
      std::vector<size_t> attenuationDiffs;
      std::vector<size_t> colorDiffs;
    };

    inline bool doPodsDiffer(
      spotLight_t const & lhs,
      spotLight_t const & rhs,
      spotLightDiffs_t & spotLight) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { spotLight.diffs |= spotLightMembers_e::type; }
      // diff member 'attenuation':
      for (size_t i = 0; i < lhs.attenuation.size(); ++i)
      {
        if (lhs.attenuation[i] != rhs.attenuation[i])
        {
          spotLight.diffs |= spotLightMembers_e::attenuation;
          spotLight.attenuationDiffs.push_back(i);
        }
      }
      // diff member 'hotspot':
      if (lhs.hotspot != rhs.hotspot)
        { spotLight.diffs |= spotLightMembers_e::hotspot; }
      // diff member 'falloff':
      if (lhs.falloff != rhs.falloff)
        { spotLight.diffs |= spotLightMembers_e::falloff; }
      // diff member 'color':
      for (size_t i = 0; i < lhs.color.size(); ++i)
      {
        if (lhs.color[i] != rhs.color[i])
        {
          spotLight.diffs |= spotLightMembers_e::color;
          spotLight.colorDiffs.push_back(i);
        }
      }

      return spotLight.diffs != spotLightMembers_e::none;
    };

    // camera things

    struct camera_t
    {
      std::string type;
      float fovAroundYAxis;
      float minDepth;
      float maxDepth;
      std::string renderPlan;
    };

    void importPod(
      humon::HuNode const & src, camera_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, camera_t & dest);

    void exportPod(camera_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      camera_t const & src, std::vector<uint8_t> & dest);

    std::string print(camera_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, camera_t const & src);

    enum class cameraMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      fovAroundYAxis = 1 << 1,
      minDepth = 1 << 2,
      maxDepth = 1 << 3,
      renderPlan = 1 << 4,
      all = type | fovAroundYAxis | minDepth | maxDepth | renderPlan
    };

    inline bool operator == (camera_t const & lhs, camera_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.fovAroundYAxis == rhs.fovAroundYAxis &&
        lhs.minDepth == rhs.minDepth &&
        lhs.maxDepth == rhs.maxDepth &&
        lhs.renderPlan == rhs.renderPlan;
    };

    inline bool operator != (camera_t const & lhs, camera_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cameraDiffs_t
    {
      cameraMembers_e diffs;
    };

    inline bool doPodsDiffer(
      camera_t const & lhs,
      camera_t const & rhs,
      cameraDiffs_t & camera) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { camera.diffs |= cameraMembers_e::type; }
      // diff member 'fovAroundYAxis':
      if (lhs.fovAroundYAxis != rhs.fovAroundYAxis)
        { camera.diffs |= cameraMembers_e::fovAroundYAxis; }
      // diff member 'minDepth':
      if (lhs.minDepth != rhs.minDepth)
        { camera.diffs |= cameraMembers_e::minDepth; }
      // diff member 'maxDepth':
      if (lhs.maxDepth != rhs.maxDepth)
        { camera.diffs |= cameraMembers_e::maxDepth; }
      // diff member 'renderPlan':
      if (lhs.renderPlan != rhs.renderPlan)
        { camera.diffs |= cameraMembers_e::renderPlan; }

      return camera.diffs != cameraMembers_e::none;
    };

    // feature things

    struct feature_t
    {
      size_t renderPlanRefs;
      size_t modelRefs;
      size_t materialRefs;
      size_t assetRefs;
      std::variant<matrixTransform_t, srtTransform_t, drawableMesh_t, directionalLight_t, pointLight_t, spotLight_t, camera_t> featureData;
    };

    void importPod(
      humon::HuNode const & src, feature_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, feature_t & dest);

    void exportPod(feature_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      feature_t const & src, std::vector<uint8_t> & dest);

    std::string print(feature_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, feature_t const & src);

    enum class featureMembers_e : int 
    {
      none = 0,
      renderPlanRefs = 1 << 0,
      modelRefs = 1 << 1,
      materialRefs = 1 << 2,
      assetRefs = 1 << 3,
      featureData = 1 << 4,
      all = renderPlanRefs | modelRefs | materialRefs | assetRefs | featureData
    };

    inline bool operator == (feature_t const & lhs, feature_t const & rhs) noexcept
    {
      return
        lhs.renderPlanRefs == rhs.renderPlanRefs &&
        lhs.modelRefs == rhs.modelRefs &&
        lhs.materialRefs == rhs.materialRefs &&
        lhs.assetRefs == rhs.assetRefs &&
        lhs.featureData == rhs.featureData;
    };

    inline bool operator != (feature_t const & lhs, feature_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct featureDiffs_t
    {
      featureMembers_e diffs;
    };

    inline bool doPodsDiffer(
      feature_t const & lhs,
      feature_t const & rhs,
      featureDiffs_t & feature) noexcept
    {
      // diff member 'renderPlanRefs':
      if (lhs.renderPlanRefs != rhs.renderPlanRefs)
        { feature.diffs |= featureMembers_e::renderPlanRefs; }
      // diff member 'modelRefs':
      if (lhs.modelRefs != rhs.modelRefs)
        { feature.diffs |= featureMembers_e::modelRefs; }
      // diff member 'materialRefs':
      if (lhs.materialRefs != rhs.materialRefs)
        { feature.diffs |= featureMembers_e::materialRefs; }
      // diff member 'assetRefs':
      if (lhs.assetRefs != rhs.assetRefs)
        { feature.diffs |= featureMembers_e::assetRefs; }
      // diff member 'featureData':
      if (lhs.featureData != rhs.featureData)
        { feature.diffs |= featureMembers_e::featureData; }

      return feature.diffs != featureMembers_e::none;
    };

    // otherKindOfObject things

    struct otherKindOfObject_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, otherKindOfObject_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, otherKindOfObject_t & dest);

    void exportPod(otherKindOfObject_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      otherKindOfObject_t const & src, std::vector<uint8_t> & dest);

    std::string print(otherKindOfObject_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, otherKindOfObject_t const & src);

    enum class otherKindOfObjectMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (otherKindOfObject_t const & lhs, otherKindOfObject_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (otherKindOfObject_t const & lhs, otherKindOfObject_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct otherKindOfObjectDiffs_t
    {
      otherKindOfObjectMembers_e diffs;
    };

    inline bool doPodsDiffer(
      otherKindOfObject_t const & lhs,
      otherKindOfObject_t const & rhs,
      otherKindOfObjectDiffs_t & otherKindOfObject) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { otherKindOfObject.diffs |= otherKindOfObjectMembers_e::type; }

      return otherKindOfObject.diffs != otherKindOfObjectMembers_e::none;
    };

    // object things

    struct object_t
    {
      std::string name;
      std::vector<object_t> children;
      std::vector<feature_t> features;
      std::optional<std::variant<otherKindOfObject_t>> data;
    };

    void importPod(
      humon::HuNode const & src, object_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, object_t & dest);

    void exportPod(object_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      object_t const & src, std::vector<uint8_t> & dest);

    std::string print(object_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, object_t const & src);

    enum class objectMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      children = 1 << 1,
      features = 1 << 2,
      data = 1 << 3,
      all = name | children | features | data
    };

    inline bool operator == (object_t const & lhs, object_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.children == rhs.children &&
        lhs.features == rhs.features &&
        lhs.data == rhs.data;
    };

    inline bool operator != (object_t const & lhs, object_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct objectDiffs_t
    {
      objectMembers_e diffs;
      std::vector<std::pair<size_t, objectDiffs_t>> childrenDiffs;
      std::vector<std::pair<size_t, featureDiffs_t>> featuresDiffs;
    };

    inline bool doPodsDiffer(
      object_t const & lhs,
      object_t const & rhs,
      objectDiffs_t & object) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { object.diffs |= objectMembers_e::name; }
      // diff member 'children':
      {
        auto [mn, mx] = std::minmax(lhs.children.size(), rhs.children.size());
        for (size_t i = 0; i < mn; ++i)
        {
          objectDiffs_t diffsEntry;
          if (doPodsDiffer(lhs.children[i], rhs.children[i], diffsEntry))
          {
            object.diffs |= objectMembers_e::children;
            object.childrenDiffs.push_back({i, diffsEntry});
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          objectDiffs_t diffsEntry = { .diffs = objectMembers_e::all };
          object.childrenDiffs.push_back({i, diffsEntry});
        }
      }
      // diff member 'features':
      {
        auto [mn, mx] = std::minmax(lhs.features.size(), rhs.features.size());
        for (size_t i = 0; i < mn; ++i)
        {
          featureDiffs_t diffsEntry;
          if (doPodsDiffer(lhs.features[i], rhs.features[i], diffsEntry))
          {
            object.diffs |= objectMembers_e::features;
            object.featuresDiffs.push_back({i, diffsEntry});
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          featureDiffs_t diffsEntry = { .diffs = featureMembers_e::all };
          object.featuresDiffs.push_back({i, diffsEntry});
        }
      }
      // diff member 'data':
      if (lhs.data != rhs.data)
        { object.diffs |= objectMembers_e::data; }

      return object.diffs != objectMembers_e::none;
    };

    // tableau things

    struct tableau_t
    {
      std::string name;
      stringDict<object_t> objects;
    };

    void importPod(
      humon::HuNode const & src, tableau_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, tableau_t & dest);

    void exportPod(tableau_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      tableau_t const & src, std::vector<uint8_t> & dest);

    std::string print(tableau_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, tableau_t const & src);

    enum class tableauMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      objects = 1 << 1,
      all = name | objects
    };

    inline bool operator == (tableau_t const & lhs, tableau_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.objects == rhs.objects;
    };

    inline bool operator != (tableau_t const & lhs, tableau_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct tableauDiffs_t
    {
      tableauMembers_e diffs;
      std::vector<std::pair<std::string, objectDiffs_t>> objectsDiffs;
    };

    inline bool doPodsDiffer(
      tableau_t const & lhs,
      tableau_t const & rhs,
      tableauDiffs_t & tableau) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { tableau.diffs |= tableauMembers_e::name; }
      // diff member 'objects':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.objects.keys)
        {
          objectDiffs_t diffsEntry;
          if (auto it = rhs.objects.keys().find(lhsKey); it != rhs.objects.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.objects[lhsIdx], rhs.objects[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          tableau.diffs |= tableauMembers_e::objects;
          tableau.objectsDiffs.push_back({lhsKey, diffsEntry});
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.objects.keys())
        {
          if (auto it = lhs.objects.keys.find(rhsKey); it != lhs.objects.keys.end())
            { continue; }

          objectDiffs_t diffsEntry = { .diffs = objectMembers_e::all };
          tableau.objectsDiffs.push_back({rhsKey, diffsEntry});
        }
      }

      return tableau.diffs != tableauMembers_e::none;
    };

  }
}

#endif // #ifndef tableau_GEN_H
