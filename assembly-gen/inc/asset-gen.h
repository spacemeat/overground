#ifndef asset_GEN_H
#define asset_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <unordered_set>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  namespace asset
  {
    // mesh things

    struct mesh_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, mesh_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, mesh_t & dest);

    void exportPod(mesh_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      mesh_t const & src, std::vector<uint8_t> & dest);

    std::string print(mesh_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, mesh_t const & src);

    enum class meshMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (mesh_t const & lhs, mesh_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (mesh_t const & lhs, mesh_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct meshDiffs_t
    {
      meshMembers_e diffs;
    };

    inline bool doPodsDiffer(
      mesh_t const & lhs,
      mesh_t const & rhs,
      meshDiffs_t & mesh) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { mesh.diffs |= meshMembers_e::type; }

      return mesh.diffs != meshMembers_e::none;
    };

    // componentMapping things

    struct componentMapping_t
    {
      vk::ComponentSwizzle r;
      vk::ComponentSwizzle g;
      vk::ComponentSwizzle b;
      vk::ComponentSwizzle a;
    };

    void importPod(
      humon::HuNode const & src, componentMapping_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, componentMapping_t & dest);

    void exportPod(componentMapping_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      componentMapping_t const & src, std::vector<uint8_t> & dest);

    std::string print(componentMapping_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, componentMapping_t const & src);

    enum class componentMappingMembers_e : int 
    {
      none = 0,
      r = 1 << 0,
      g = 1 << 1,
      b = 1 << 2,
      a = 1 << 3,
      all = r | g | b | a
    };

    inline bool operator == (componentMapping_t const & lhs, componentMapping_t const & rhs) noexcept
    {
      return
        lhs.r == rhs.r &&
        lhs.g == rhs.g &&
        lhs.b == rhs.b &&
        lhs.a == rhs.a;
    };

    inline bool operator != (componentMapping_t const & lhs, componentMapping_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct componentMappingDiffs_t
    {
      componentMappingMembers_e diffs;
    };

    inline bool doPodsDiffer(
      componentMapping_t const & lhs,
      componentMapping_t const & rhs,
      componentMappingDiffs_t & componentMapping) noexcept
    {
      // diff member 'r':
      if (lhs.r != rhs.r)
        { componentMapping.diffs |= componentMappingMembers_e::r; }
      // diff member 'g':
      if (lhs.g != rhs.g)
        { componentMapping.diffs |= componentMappingMembers_e::g; }
      // diff member 'b':
      if (lhs.b != rhs.b)
        { componentMapping.diffs |= componentMappingMembers_e::b; }
      // diff member 'a':
      if (lhs.a != rhs.a)
        { componentMapping.diffs |= componentMappingMembers_e::a; }

      return componentMapping.diffs != componentMappingMembers_e::none;
    };

    // image things

    struct image_t
    {
      std::string type;
      vk::ImageType imageType;
      size_t numLayers;
      std::array<size_t, 3> extents;
      size_t numMipLevels;
      std::optional<componentMapping_t> componentMapping;
    };

    void importPod(
      humon::HuNode const & src, image_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, image_t & dest);

    void exportPod(image_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      image_t const & src, std::vector<uint8_t> & dest);

    std::string print(image_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, image_t const & src);

    enum class imageMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      imageType = 1 << 1,
      numLayers = 1 << 2,
      extents = 1 << 3,
      numMipLevels = 1 << 4,
      componentMapping = 1 << 5,
      all = type | imageType | numLayers | extents | numMipLevels | componentMapping
    };

    inline bool operator == (image_t const & lhs, image_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.imageType == rhs.imageType &&
        lhs.numLayers == rhs.numLayers &&
        lhs.extents == rhs.extents &&
        lhs.numMipLevels == rhs.numMipLevels &&
        lhs.componentMapping == rhs.componentMapping;
    };

    inline bool operator != (image_t const & lhs, image_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct imageDiffs_t
    {
      imageMembers_e diffs;
      std::unordered_set<size_t> extentsDiffs;
    };

    inline bool doPodsDiffer(
      image_t const & lhs,
      image_t const & rhs,
      imageDiffs_t & image) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { image.diffs |= imageMembers_e::type; }
      // diff member 'imageType':
      if (lhs.imageType != rhs.imageType)
        { image.diffs |= imageMembers_e::imageType; }
      // diff member 'numLayers':
      if (lhs.numLayers != rhs.numLayers)
        { image.diffs |= imageMembers_e::numLayers; }
      // diff member 'extents':
      for (size_t i = 0; i < lhs.extents.size(); ++i)
      {
        if (lhs.extents[i] != rhs.extents[i])
        {
          image.diffs |= imageMembers_e::extents;
          image.extentsDiffs.insert(i);
        }
      }
      // diff member 'numMipLevels':
      if (lhs.numMipLevels != rhs.numMipLevels)
        { image.diffs |= imageMembers_e::numMipLevels; }
      // diff member 'componentMapping':
      if (lhs.componentMapping != rhs.componentMapping)
        { image.diffs |= imageMembers_e::componentMapping; }

      return image.diffs != imageMembers_e::none;
    };

    // cubeMapImage things

    struct cubeMapImage_t
    {
      std::string type;
      size_t numCubes;
      std::array<size_t, 3> extents;
      size_t numMipLevels;
      std::optional<componentMapping_t> componentMapping;
    };

    void importPod(
      humon::HuNode const & src, cubeMapImage_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cubeMapImage_t & dest);

    void exportPod(cubeMapImage_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cubeMapImage_t const & src, std::vector<uint8_t> & dest);

    std::string print(cubeMapImage_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cubeMapImage_t const & src);

    enum class cubeMapImageMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      numCubes = 1 << 1,
      extents = 1 << 2,
      numMipLevels = 1 << 3,
      componentMapping = 1 << 4,
      all = type | numCubes | extents | numMipLevels | componentMapping
    };

    inline bool operator == (cubeMapImage_t const & lhs, cubeMapImage_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.numCubes == rhs.numCubes &&
        lhs.extents == rhs.extents &&
        lhs.numMipLevels == rhs.numMipLevels &&
        lhs.componentMapping == rhs.componentMapping;
    };

    inline bool operator != (cubeMapImage_t const & lhs, cubeMapImage_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cubeMapImageDiffs_t
    {
      cubeMapImageMembers_e diffs;
      std::unordered_set<size_t> extentsDiffs;
    };

    inline bool doPodsDiffer(
      cubeMapImage_t const & lhs,
      cubeMapImage_t const & rhs,
      cubeMapImageDiffs_t & cubeMapImage) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cubeMapImage.diffs |= cubeMapImageMembers_e::type; }
      // diff member 'numCubes':
      if (lhs.numCubes != rhs.numCubes)
        { cubeMapImage.diffs |= cubeMapImageMembers_e::numCubes; }
      // diff member 'extents':
      for (size_t i = 0; i < lhs.extents.size(); ++i)
      {
        if (lhs.extents[i] != rhs.extents[i])
        {
          cubeMapImage.diffs |= cubeMapImageMembers_e::extents;
          cubeMapImage.extentsDiffs.insert(i);
        }
      }
      // diff member 'numMipLevels':
      if (lhs.numMipLevels != rhs.numMipLevels)
        { cubeMapImage.diffs |= cubeMapImageMembers_e::numMipLevels; }
      // diff member 'componentMapping':
      if (lhs.componentMapping != rhs.componentMapping)
        { cubeMapImage.diffs |= cubeMapImageMembers_e::componentMapping; }

      return cubeMapImage.diffs != cubeMapImageMembers_e::none;
    };

    // shader things

    struct shader_t
    {
      std::string type;
      std::string entryPoint;
    };

    void importPod(
      humon::HuNode const & src, shader_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, shader_t & dest);

    void exportPod(shader_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      shader_t const & src, std::vector<uint8_t> & dest);

    std::string print(shader_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, shader_t const & src);

    enum class shaderMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      entryPoint = 1 << 1,
      all = type | entryPoint
    };

    inline bool operator == (shader_t const & lhs, shader_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.entryPoint == rhs.entryPoint;
    };

    inline bool operator != (shader_t const & lhs, shader_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct shaderDiffs_t
    {
      shaderMembers_e diffs;
    };

    inline bool doPodsDiffer(
      shader_t const & lhs,
      shader_t const & rhs,
      shaderDiffs_t & shader) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { shader.diffs |= shaderMembers_e::type; }
      // diff member 'entryPoint':
      if (lhs.entryPoint != rhs.entryPoint)
        { shader.diffs |= shaderMembers_e::entryPoint; }

      return shader.diffs != shaderMembers_e::none;
    };

    // asset things

    struct asset_t
    {
      std::string name;
      std::vector<std::string> srcFiles;
      bool monitorFile;
      std::variant<mesh_t, image_t, cubeMapImage_t, shader_t> importData;
      std::optional<vk::Format> format;
    };

    void importPod(
      humon::HuNode const & src, asset_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, asset_t & dest);

    void exportPod(asset_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      asset_t const & src, std::vector<uint8_t> & dest);

    std::string print(asset_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, asset_t const & src);

    enum class assetMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      srcFiles = 1 << 1,
      monitorFile = 1 << 2,
      importData = 1 << 3,
      format = 1 << 4,
      all = name | srcFiles | monitorFile | importData | format
    };

    inline bool operator == (asset_t const & lhs, asset_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.srcFiles == rhs.srcFiles &&
        lhs.monitorFile == rhs.monitorFile &&
        lhs.importData == rhs.importData &&
        lhs.format == rhs.format;
    };

    inline bool operator != (asset_t const & lhs, asset_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct assetDiffs_t
    {
      assetMembers_e diffs;
      std::unordered_set<size_t> srcFilesDiffs;
    };

    inline bool doPodsDiffer(
      asset_t const & lhs,
      asset_t const & rhs,
      assetDiffs_t & asset) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { asset.diffs |= assetMembers_e::name; }
      // diff member 'srcFiles':
      {
        auto [mn, mx] = std::minmax(lhs.srcFiles.size(), rhs.srcFiles.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.srcFiles[i] != rhs.srcFiles[i])
          {
            asset.diffs |= assetMembers_e::srcFiles;
            asset.srcFilesDiffs.insert(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          asset.srcFilesDiffs.insert(i);
        }
      }
      // diff member 'monitorFile':
      if (lhs.monitorFile != rhs.monitorFile)
        { asset.diffs |= assetMembers_e::monitorFile; }
      // diff member 'importData':
      if (lhs.importData != rhs.importData)
        { asset.diffs |= assetMembers_e::importData; }
      // diff member 'format':
      if (lhs.format != rhs.format)
        { asset.diffs |= assetMembers_e::format; }

      return asset.diffs != assetMembers_e::none;
    };

  }
}

#endif // #ifndef asset_GEN_H
