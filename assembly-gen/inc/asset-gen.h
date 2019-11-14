#ifndef asset_GEN_H
#define asset_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  namespace asset
  {
    // meshAsset things

    struct meshAsset_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, meshAsset_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, meshAsset_t & dest);

    void exportPod(meshAsset_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      meshAsset_t const & src, std::vector<uint8_t> & dest);

    std::string print(meshAsset_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, meshAsset_t const & src);

    enum class meshAssetMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (meshAsset_t const & lhs, meshAsset_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (meshAsset_t const & lhs, meshAsset_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct meshAssetDiffs_t
    {
      meshAssetMembers_e diffs;
    };

    inline bool doPodsDiffer(
      meshAsset_t const & lhs,
      meshAsset_t const & rhs,
      meshAssetDiffs_t & meshAsset) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { meshAsset.diffs |= meshAssetMembers_e::type; }

      return meshAsset.diffs != meshAssetMembers_e::none;
    };

    // imageAsset things

    struct imageAsset_t
    {
      std::string type;
      vk::Format format;
      std::optional<string> compression;
    };

    void importPod(
      humon::HuNode const & src, imageAsset_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, imageAsset_t & dest);

    void exportPod(imageAsset_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      imageAsset_t const & src, std::vector<uint8_t> & dest);

    std::string print(imageAsset_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, imageAsset_t const & src);

    enum class imageAssetMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      format = 1 << 1,
      compression = 1 << 2,
      all = type | format | compression
    };

    inline bool operator == (imageAsset_t const & lhs, imageAsset_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.format == rhs.format &&
        lhs.compression == rhs.compression;
    };

    inline bool operator != (imageAsset_t const & lhs, imageAsset_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct imageAssetDiffs_t
    {
      imageAssetMembers_e diffs;
    };

    inline bool doPodsDiffer(
      imageAsset_t const & lhs,
      imageAsset_t const & rhs,
      imageAssetDiffs_t & imageAsset) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { imageAsset.diffs |= imageAssetMembers_e::type; }
      // diff member 'format':
      if (lhs.format != rhs.format)
        { imageAsset.diffs |= imageAssetMembers_e::format; }
      // diff member 'compression':
      if (lhs.compression != rhs.compression)
        { imageAsset.diffs |= imageAssetMembers_e::compression; }

      return imageAsset.diffs != imageAssetMembers_e::none;
    };

    // shaderAsset things

    struct shaderAsset_t
    {
      std::string type;
      std::string entryPoint;
    };

    void importPod(
      humon::HuNode const & src, shaderAsset_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, shaderAsset_t & dest);

    void exportPod(shaderAsset_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      shaderAsset_t const & src, std::vector<uint8_t> & dest);

    std::string print(shaderAsset_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, shaderAsset_t const & src);

    enum class shaderAssetMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      entryPoint = 1 << 1,
      all = type | entryPoint
    };

    inline bool operator == (shaderAsset_t const & lhs, shaderAsset_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.entryPoint == rhs.entryPoint;
    };

    inline bool operator != (shaderAsset_t const & lhs, shaderAsset_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct shaderAssetDiffs_t
    {
      shaderAssetMembers_e diffs;
    };

    inline bool doPodsDiffer(
      shaderAsset_t const & lhs,
      shaderAsset_t const & rhs,
      shaderAssetDiffs_t & shaderAsset) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { shaderAsset.diffs |= shaderAssetMembers_e::type; }
      // diff member 'entryPoint':
      if (lhs.entryPoint != rhs.entryPoint)
        { shaderAsset.diffs |= shaderAssetMembers_e::entryPoint; }

      return shaderAsset.diffs != shaderAssetMembers_e::none;
    };

    // asset things

    struct asset_t
    {
      std::string name;
      std::optional<string> srcFile;
      std::string assFile;
      bool monitorFile;
      std::variant<meshAsset_t, imageAsset_t, shaderAsset_t> data;
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
      assFile = 1 << 2,
      monitorFile = 1 << 3,
      data = 1 << 4,
      all = name | srcFile | assFile | monitorFile | data
    };

    inline bool operator == (asset_t const & lhs, asset_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.srcFile == rhs.srcFile &&
        lhs.assFile == rhs.assFile &&
        lhs.monitorFile == rhs.monitorFile &&
        lhs.data == rhs.data;
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
      // diff member 'assFile':
      if (lhs.assFile != rhs.assFile)
        { asset.diffs |= assetMembers_e::assFile; }
      // diff member 'monitorFile':
      if (lhs.monitorFile != rhs.monitorFile)
        { asset.diffs |= assetMembers_e::monitorFile; }
      // diff member 'data':
      if (lhs.data != rhs.data)
        { asset.diffs |= assetMembers_e::data; }

      return asset.diffs != assetMembers_e::none;
    };

  }
}

#endif // #ifndef asset_GEN_H
