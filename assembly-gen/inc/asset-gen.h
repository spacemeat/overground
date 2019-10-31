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
      std::string buffer;
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
      buffer = 1 << 0,
      all = buffer
    };

    inline bool operator == (meshAsset_t const & lhs, meshAsset_t const & rhs) noexcept
    {
      return
        lhs.buffer == rhs.buffer;
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
      // diff member 'buffer':
      if (lhs.buffer != rhs.buffer)
        { meshAsset.diffs |= meshAssetMembers_e::buffer; }

      return meshAsset.diffs != meshAssetMembers_e::none;
    };

    // imageAsset things

    struct imageAsset_t
    {
      vk::Format format;
      std::optional<std::string> compression;
      std::string buffer;
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
      format = 1 << 0,
      compression = 1 << 1,
      buffer = 1 << 2,
      all = format | compression | buffer
    };

    inline bool operator == (imageAsset_t const & lhs, imageAsset_t const & rhs) noexcept
    {
      return
        lhs.format == rhs.format &&
        lhs.compression == rhs.compression &&
        lhs.buffer == rhs.buffer;
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
      // diff member 'format':
      if (lhs.format != rhs.format)
        { imageAsset.diffs |= imageAssetMembers_e::format; }
      // diff member 'compression':
      if (lhs.compression != rhs.compression)
        { imageAsset.diffs |= imageAssetMembers_e::compression; }
      // diff member 'buffer':
      if (lhs.buffer != rhs.buffer)
        { imageAsset.diffs |= imageAssetMembers_e::buffer; }

      return imageAsset.diffs != imageAssetMembers_e::none;
    };

    // shaderAsset things

    struct shaderAsset_t
    {
      std::string entry;
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
      entry = 1 << 0,
      all = entry
    };

    inline bool operator == (shaderAsset_t const & lhs, shaderAsset_t const & rhs) noexcept
    {
      return
        lhs.entry == rhs.entry;
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
      // diff member 'entry':
      if (lhs.entry != rhs.entry)
        { shaderAsset.diffs |= shaderAssetMembers_e::entry; }

      return shaderAsset.diffs != shaderAssetMembers_e::none;
    };

    // asset things

    struct asset_t
    {
      std::string name;
      std::string type;
      std::optional<std::string> srcFile;
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
      type = 1 << 1,
      srcFile = 1 << 2,
      assFile = 1 << 3,
      monitorFile = 1 << 4,
      data = 1 << 5,
      all = name | type | srcFile | assFile | monitorFile | data
    };

    inline bool operator == (asset_t const & lhs, asset_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.type == rhs.type &&
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
      // diff member 'type':
      if (lhs.type != rhs.type)
        { asset.diffs |= assetMembers_e::type; }
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

    // assets things

    struct assets_t
    {
      stringDict<asset_t> assets;
    };

    void importPod(
      humon::HuNode const & src, assets_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, assets_t & dest);

    void exportPod(assets_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      assets_t const & src, std::vector<uint8_t> & dest);

    std::string print(assets_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, assets_t const & src);

    enum class assetsMembers_e : int 
    {
      none = 0,
      assets = 1 << 0,
      all = assets
    };

    inline bool operator == (assets_t const & lhs, assets_t const & rhs) noexcept
    {
      return
        lhs.assets == rhs.assets;
    };

    inline bool operator != (assets_t const & lhs, assets_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct assetsDiffs_t
    {
      assetsMembers_e diffs;
      std::vector<std::pair<std::string, assetDiffs_t>> assetsDiffs;
    };

    inline bool doPodsDiffer(
      assets_t const & lhs,
      assets_t const & rhs,
      assetsDiffs_t & assets) noexcept
    {
      // diff member 'assets':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.assets.keys)
        {
          assetDiffs_t diffsEntry;
          if (auto it = rhs.assets.keys().find(lhsKey); it != rhs.assets.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.assets[lhsIdx], rhs.assets[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          assets.diffs |= assetsMembers_e::assets;
          assets.assetsDiffs.push_back({lhsKey, diffsEntry});
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.assets.keys())
        {
          if (auto it = lhs.assets.keys.find(rhsKey); it != lhs.assets.keys.end())
            { continue; }

          assetDiffs_t diffsEntry = { .diffs = assetMembers_e::all };
          assets.assetsDiffs.push_back({rhsKey, diffsEntry});
        }
      }

      return assets.diffs != assetsMembers_e::none;
    };

  }
}

#endif // #ifndef asset_GEN_H
