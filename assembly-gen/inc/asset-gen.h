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

    // image things

    struct image_t
    {
      std::string type;
      std::array<size_t, 3> dims;
      size_t numMipLevels;
      vk::Format format;
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
      dims = 1 << 1,
      numMipLevels = 1 << 2,
      format = 1 << 3,
      all = type | dims | numMipLevels | format
    };

    inline bool operator == (image_t const & lhs, image_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.dims == rhs.dims &&
        lhs.numMipLevels == rhs.numMipLevels &&
        lhs.format == rhs.format;
    };

    inline bool operator != (image_t const & lhs, image_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct imageDiffs_t
    {
      imageMembers_e diffs;
      std::unordered_set<size_t> dimsDiffs;
    };

    inline bool doPodsDiffer(
      image_t const & lhs,
      image_t const & rhs,
      imageDiffs_t & image) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { image.diffs |= imageMembers_e::type; }
      // diff member 'dims':
      for (size_t i = 0; i < lhs.dims.size(); ++i)
      {
        if (lhs.dims[i] != rhs.dims[i])
        {
          image.diffs |= imageMembers_e::dims;
          image.dimsDiffs.insert(i);
        }
      }
      // diff member 'numMipLevels':
      if (lhs.numMipLevels != rhs.numMipLevels)
        { image.diffs |= imageMembers_e::numMipLevels; }
      // diff member 'format':
      if (lhs.format != rhs.format)
        { image.diffs |= imageMembers_e::format; }

      return image.diffs != imageMembers_e::none;
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
      std::optional<std::string> srcFile;
      bool monitorFile;
      std::variant<mesh_t, image_t, shader_t> importData;
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
      srcFile = 1 << 1,
      monitorFile = 1 << 2,
      importData = 1 << 3,
      all = name | srcFile | monitorFile | importData
    };

    inline bool operator == (asset_t const & lhs, asset_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.srcFile == rhs.srcFile &&
        lhs.monitorFile == rhs.monitorFile &&
        lhs.importData == rhs.importData;
    };

    inline bool operator != (asset_t const & lhs, asset_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct assetDiffs_t
    {
      assetMembers_e diffs;
    };

    inline bool doPodsDiffer(
      asset_t const & lhs,
      asset_t const & rhs,
      assetDiffs_t & asset) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { asset.diffs |= assetMembers_e::name; }
      // diff member 'srcFile':
      if (lhs.srcFile != rhs.srcFile)
        { asset.diffs |= assetMembers_e::srcFile; }
      // diff member 'monitorFile':
      if (lhs.monitorFile != rhs.monitorFile)
        { asset.diffs |= assetMembers_e::monitorFile; }
      // diff member 'importData':
      if (lhs.importData != rhs.importData)
        { asset.diffs |= assetMembers_e::importData; }

      return asset.diffs != assetMembers_e::none;
    };

  }
}

#endif // #ifndef asset_GEN_H
