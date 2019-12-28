#ifndef material_GEN_H
#define material_GEN_H

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
  namespace material
  {
    // descriptor things

    struct descriptor_t
    {
      stringDict<vk::DescriptorType> descType;
      std::optional<std::string> asset;
    };

    void importPod(
      humon::HuNode const & src, descriptor_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, descriptor_t & dest);

    void exportPod(descriptor_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      descriptor_t const & src, std::vector<uint8_t> & dest);

    std::string print(descriptor_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, descriptor_t const & src);

    enum class descriptorMembers_e : int 
    {
      none = 0,
      descType = 1 << 0,
      asset = 1 << 1,
      all = descType | asset
    };

    inline bool operator == (descriptor_t const & lhs, descriptor_t const & rhs) noexcept
    {
      return
        lhs.descType == rhs.descType &&
        lhs.asset == rhs.asset;
    };

    inline bool operator != (descriptor_t const & lhs, descriptor_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct descriptorDiffs_t
    {
      descriptorMembers_e diffs;
      std::unordered_set<std::string> descTypeDiffs;
    };

    inline bool doPodsDiffer(
      descriptor_t const & lhs,
      descriptor_t const & rhs,
      descriptorDiffs_t & descriptor) noexcept
    {
      // diff member 'descType':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.descType.keys)
        {
          if (auto it = rhs.descType.keys().find(lhsKey); it != rhs.descType.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                lhs.descType[lhsIdx] == rhs.descType[rhsIdx])
              { continue; }
          }
          descriptor.diffs |= descriptorMembers_e::descType;
          descriptor.descTypeDiffs.insert(lhsKey);
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.descType.keys())
        {
          if (auto it = lhs.descType.keys.find(rhsKey); it != lhs.descType.keys.end())
            { continue; }
          descriptor.descTypeDiffs.insert(rhsKey);
        }
      }
      // diff member 'asset':
      if (lhs.asset != rhs.asset)
        { descriptor.diffs |= descriptorMembers_e::asset; }

      return descriptor.diffs != descriptorMembers_e::none;
    };

    // shaderModule things

    struct shaderModule_t
    {
      std::string name;
      std::string shaderName;
    };

    void importPod(
      humon::HuNode const & src, shaderModule_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, shaderModule_t & dest);

    void exportPod(shaderModule_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      shaderModule_t const & src, std::vector<uint8_t> & dest);

    std::string print(shaderModule_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, shaderModule_t const & src);

    enum class shaderModuleMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      shaderName = 1 << 1,
      all = name | shaderName
    };

    inline bool operator == (shaderModule_t const & lhs, shaderModule_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.shaderName == rhs.shaderName;
    };

    inline bool operator != (shaderModule_t const & lhs, shaderModule_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct shaderModuleDiffs_t
    {
      shaderModuleMembers_e diffs;
    };

    inline bool doPodsDiffer(
      shaderModule_t const & lhs,
      shaderModule_t const & rhs,
      shaderModuleDiffs_t & shaderModule) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { shaderModule.diffs |= shaderModuleMembers_e::name; }
      // diff member 'shaderName':
      if (lhs.shaderName != rhs.shaderName)
        { shaderModule.diffs |= shaderModuleMembers_e::shaderName; }

      return shaderModule.diffs != shaderModuleMembers_e::none;
    };

    // stage things

    struct stage_t
    {
      std::string shaderAsset;
      std::string entry;
    };

    void importPod(
      humon::HuNode const & src, stage_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, stage_t & dest);

    void exportPod(stage_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      stage_t const & src, std::vector<uint8_t> & dest);

    std::string print(stage_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, stage_t const & src);

    enum class stageMembers_e : int 
    {
      none = 0,
      shaderAsset = 1 << 0,
      entry = 1 << 1,
      all = shaderAsset | entry
    };

    inline bool operator == (stage_t const & lhs, stage_t const & rhs) noexcept
    {
      return
        lhs.shaderAsset == rhs.shaderAsset &&
        lhs.entry == rhs.entry;
    };

    inline bool operator != (stage_t const & lhs, stage_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct stageDiffs_t
    {
      stageMembers_e diffs;
    };

    inline bool doPodsDiffer(
      stage_t const & lhs,
      stage_t const & rhs,
      stageDiffs_t & stage) noexcept
    {
      // diff member 'shaderAsset':
      if (lhs.shaderAsset != rhs.shaderAsset)
        { stage.diffs |= stageMembers_e::shaderAsset; }
      // diff member 'entry':
      if (lhs.entry != rhs.entry)
        { stage.diffs |= stageMembers_e::entry; }

      return stage.diffs != stageMembers_e::none;
    };

    // rasterizationState things

    struct rasterizationState_t
    {
      bool depthClampEnable;
      bool rasterizerDiscardEnable;
      vk::FillMode polygonFillMode;
      vk::CullMode cullMode;
      vk::FaceOrientation frontFace;
      bool depthBiasEnable;
      float lineWidth;
    };

    void importPod(
      humon::HuNode const & src, rasterizationState_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, rasterizationState_t & dest);

    void exportPod(rasterizationState_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      rasterizationState_t const & src, std::vector<uint8_t> & dest);

    std::string print(rasterizationState_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, rasterizationState_t const & src);

    enum class rasterizationStateMembers_e : int 
    {
      none = 0,
      depthClampEnable = 1 << 0,
      rasterizerDiscardEnable = 1 << 1,
      polygonFillMode = 1 << 2,
      cullMode = 1 << 3,
      frontFace = 1 << 4,
      depthBiasEnable = 1 << 5,
      lineWidth = 1 << 6,
      all = depthClampEnable | rasterizerDiscardEnable | polygonFillMode | cullMode | frontFace | depthBiasEnable | lineWidth
    };

    inline bool operator == (rasterizationState_t const & lhs, rasterizationState_t const & rhs) noexcept
    {
      return
        lhs.depthClampEnable == rhs.depthClampEnable &&
        lhs.rasterizerDiscardEnable == rhs.rasterizerDiscardEnable &&
        lhs.polygonFillMode == rhs.polygonFillMode &&
        lhs.cullMode == rhs.cullMode &&
        lhs.frontFace == rhs.frontFace &&
        lhs.depthBiasEnable == rhs.depthBiasEnable &&
        lhs.lineWidth == rhs.lineWidth;
    };

    inline bool operator != (rasterizationState_t const & lhs, rasterizationState_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct rasterizationStateDiffs_t
    {
      rasterizationStateMembers_e diffs;
    };

    inline bool doPodsDiffer(
      rasterizationState_t const & lhs,
      rasterizationState_t const & rhs,
      rasterizationStateDiffs_t & rasterizationState) noexcept
    {
      // diff member 'depthClampEnable':
      if (lhs.depthClampEnable != rhs.depthClampEnable)
        { rasterizationState.diffs |= rasterizationStateMembers_e::depthClampEnable; }
      // diff member 'rasterizerDiscardEnable':
      if (lhs.rasterizerDiscardEnable != rhs.rasterizerDiscardEnable)
        { rasterizationState.diffs |= rasterizationStateMembers_e::rasterizerDiscardEnable; }
      // diff member 'polygonFillMode':
      if (lhs.polygonFillMode != rhs.polygonFillMode)
        { rasterizationState.diffs |= rasterizationStateMembers_e::polygonFillMode; }
      // diff member 'cullMode':
      if (lhs.cullMode != rhs.cullMode)
        { rasterizationState.diffs |= rasterizationStateMembers_e::cullMode; }
      // diff member 'frontFace':
      if (lhs.frontFace != rhs.frontFace)
        { rasterizationState.diffs |= rasterizationStateMembers_e::frontFace; }
      // diff member 'depthBiasEnable':
      if (lhs.depthBiasEnable != rhs.depthBiasEnable)
        { rasterizationState.diffs |= rasterizationStateMembers_e::depthBiasEnable; }
      // diff member 'lineWidth':
      if (lhs.lineWidth != rhs.lineWidth)
        { rasterizationState.diffs |= rasterizationStateMembers_e::lineWidth; }

      return rasterizationState.diffs != rasterizationStateMembers_e::none;
    };

    // multisampleState things

    struct multisampleState_t
    {
      int rasterizationSamples;
      bool sampleShadingEnable;
      vk::SampleMask sampleMask;
      bool alphaToCoverageEnable;
      bool alphaToOneEnable;
    };

    void importPod(
      humon::HuNode const & src, multisampleState_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, multisampleState_t & dest);

    void exportPod(multisampleState_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      multisampleState_t const & src, std::vector<uint8_t> & dest);

    std::string print(multisampleState_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, multisampleState_t const & src);

    enum class multisampleStateMembers_e : int 
    {
      none = 0,
      rasterizationSamples = 1 << 0,
      sampleShadingEnable = 1 << 1,
      sampleMask = 1 << 2,
      alphaToCoverageEnable = 1 << 3,
      alphaToOneEnable = 1 << 4,
      all = rasterizationSamples | sampleShadingEnable | sampleMask | alphaToCoverageEnable | alphaToOneEnable
    };

    inline bool operator == (multisampleState_t const & lhs, multisampleState_t const & rhs) noexcept
    {
      return
        lhs.rasterizationSamples == rhs.rasterizationSamples &&
        lhs.sampleShadingEnable == rhs.sampleShadingEnable &&
        lhs.sampleMask == rhs.sampleMask &&
        lhs.alphaToCoverageEnable == rhs.alphaToCoverageEnable &&
        lhs.alphaToOneEnable == rhs.alphaToOneEnable;
    };

    inline bool operator != (multisampleState_t const & lhs, multisampleState_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct multisampleStateDiffs_t
    {
      multisampleStateMembers_e diffs;
    };

    inline bool doPodsDiffer(
      multisampleState_t const & lhs,
      multisampleState_t const & rhs,
      multisampleStateDiffs_t & multisampleState) noexcept
    {
      // diff member 'rasterizationSamples':
      if (lhs.rasterizationSamples != rhs.rasterizationSamples)
        { multisampleState.diffs |= multisampleStateMembers_e::rasterizationSamples; }
      // diff member 'sampleShadingEnable':
      if (lhs.sampleShadingEnable != rhs.sampleShadingEnable)
        { multisampleState.diffs |= multisampleStateMembers_e::sampleShadingEnable; }
      // diff member 'sampleMask':
      if (lhs.sampleMask != rhs.sampleMask)
        { multisampleState.diffs |= multisampleStateMembers_e::sampleMask; }
      // diff member 'alphaToCoverageEnable':
      if (lhs.alphaToCoverageEnable != rhs.alphaToCoverageEnable)
        { multisampleState.diffs |= multisampleStateMembers_e::alphaToCoverageEnable; }
      // diff member 'alphaToOneEnable':
      if (lhs.alphaToOneEnable != rhs.alphaToOneEnable)
        { multisampleState.diffs |= multisampleStateMembers_e::alphaToOneEnable; }

      return multisampleState.diffs != multisampleStateMembers_e::none;
    };

    // blendStateAttachment things

    struct blendStateAttachment_t
    {
      vk::BlendFactor srcColorFactor;
      vk::BlendFactor dstColorFactor;
      vk::BlendOp colorOp;
      vk::BlendFactor srcAlphaFactor;
      vk::BlendFactor dstAlphaFactor;
      vk::BlendOp alphaOp;
      std::vector<char> colorWriteMask;
    };

    void importPod(
      humon::HuNode const & src, blendStateAttachment_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, blendStateAttachment_t & dest);

    void exportPod(blendStateAttachment_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      blendStateAttachment_t const & src, std::vector<uint8_t> & dest);

    std::string print(blendStateAttachment_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, blendStateAttachment_t const & src);

    enum class blendStateAttachmentMembers_e : int 
    {
      none = 0,
      srcColorFactor = 1 << 0,
      dstColorFactor = 1 << 1,
      colorOp = 1 << 2,
      srcAlphaFactor = 1 << 3,
      dstAlphaFactor = 1 << 4,
      alphaOp = 1 << 5,
      colorWriteMask = 1 << 6,
      all = srcColorFactor | dstColorFactor | colorOp | srcAlphaFactor | dstAlphaFactor | alphaOp | colorWriteMask
    };

    inline bool operator == (blendStateAttachment_t const & lhs, blendStateAttachment_t const & rhs) noexcept
    {
      return
        lhs.srcColorFactor == rhs.srcColorFactor &&
        lhs.dstColorFactor == rhs.dstColorFactor &&
        lhs.colorOp == rhs.colorOp &&
        lhs.srcAlphaFactor == rhs.srcAlphaFactor &&
        lhs.dstAlphaFactor == rhs.dstAlphaFactor &&
        lhs.alphaOp == rhs.alphaOp &&
        lhs.colorWriteMask == rhs.colorWriteMask;
    };

    inline bool operator != (blendStateAttachment_t const & lhs, blendStateAttachment_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct blendStateAttachmentDiffs_t
    {
      blendStateAttachmentMembers_e diffs;
      std::unordered_set<size_t> colorWriteMaskDiffs;
    };

    inline bool doPodsDiffer(
      blendStateAttachment_t const & lhs,
      blendStateAttachment_t const & rhs,
      blendStateAttachmentDiffs_t & blendStateAttachment) noexcept
    {
      // diff member 'srcColorFactor':
      if (lhs.srcColorFactor != rhs.srcColorFactor)
        { blendStateAttachment.diffs |= blendStateAttachmentMembers_e::srcColorFactor; }
      // diff member 'dstColorFactor':
      if (lhs.dstColorFactor != rhs.dstColorFactor)
        { blendStateAttachment.diffs |= blendStateAttachmentMembers_e::dstColorFactor; }
      // diff member 'colorOp':
      if (lhs.colorOp != rhs.colorOp)
        { blendStateAttachment.diffs |= blendStateAttachmentMembers_e::colorOp; }
      // diff member 'srcAlphaFactor':
      if (lhs.srcAlphaFactor != rhs.srcAlphaFactor)
        { blendStateAttachment.diffs |= blendStateAttachmentMembers_e::srcAlphaFactor; }
      // diff member 'dstAlphaFactor':
      if (lhs.dstAlphaFactor != rhs.dstAlphaFactor)
        { blendStateAttachment.diffs |= blendStateAttachmentMembers_e::dstAlphaFactor; }
      // diff member 'alphaOp':
      if (lhs.alphaOp != rhs.alphaOp)
        { blendStateAttachment.diffs |= blendStateAttachmentMembers_e::alphaOp; }
      // diff member 'colorWriteMask':
      {
        auto [mn, mx] = std::minmax(lhs.colorWriteMask.size(), rhs.colorWriteMask.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.colorWriteMask[i] != rhs.colorWriteMask[i])
          {
            blendStateAttachment.diffs |= blendStateAttachmentMembers_e::colorWriteMask;
            blendStateAttachment.colorWriteMaskDiffs.insert(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          blendStateAttachment.colorWriteMaskDiffs.insert(i);
        }
      }

      return blendStateAttachment.diffs != blendStateAttachmentMembers_e::none;
    };

    // blendState things

    struct blendState_t
    {
      bool logicOpEnable;
      std::vector<blendStateAttachment_t> attachments;
    };

    void importPod(
      humon::HuNode const & src, blendState_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, blendState_t & dest);

    void exportPod(blendState_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      blendState_t const & src, std::vector<uint8_t> & dest);

    std::string print(blendState_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, blendState_t const & src);

    enum class blendStateMembers_e : int 
    {
      none = 0,
      logicOpEnable = 1 << 0,
      attachments = 1 << 1,
      all = logicOpEnable | attachments
    };

    inline bool operator == (blendState_t const & lhs, blendState_t const & rhs) noexcept
    {
      return
        lhs.logicOpEnable == rhs.logicOpEnable &&
        lhs.attachments == rhs.attachments;
    };

    inline bool operator != (blendState_t const & lhs, blendState_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct blendStateDiffs_t
    {
      blendStateMembers_e diffs;
      std::unordered_map<size_t, blendStateAttachmentDiffs_t> attachmentsDiffs;
    };

    inline bool doPodsDiffer(
      blendState_t const & lhs,
      blendState_t const & rhs,
      blendStateDiffs_t & blendState) noexcept
    {
      // diff member 'logicOpEnable':
      if (lhs.logicOpEnable != rhs.logicOpEnable)
        { blendState.diffs |= blendStateMembers_e::logicOpEnable; }
      // diff member 'attachments':
      {
        auto [mn, mx] = std::minmax(lhs.attachments.size(), rhs.attachments.size());
        for (size_t i = 0; i < mn; ++i)
        {
          blendStateAttachmentDiffs_t diffsEntry;
          if (doPodsDiffer(lhs.attachments[i], rhs.attachments[i], diffsEntry))
          {
            blendState.diffs |= blendStateMembers_e::attachments;
            blendState.attachmentsDiffs.insert_or_assign(i, diffsEntry);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          blendStateAttachmentDiffs_t diffsEntry = { .diffs = blendStateAttachmentMembers_e::all };
          blendState.attachmentsDiffs.insert_or_assign(i, diffsEntry);
        }
      }

      return blendState.diffs != blendStateMembers_e::none;
    };

    // tesselationState things

    struct tesselationState_t
    {
    };

    void importPod(
      humon::HuNode const & src, tesselationState_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, tesselationState_t & dest);

    void exportPod(tesselationState_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      tesselationState_t const & src, std::vector<uint8_t> & dest);

    std::string print(tesselationState_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, tesselationState_t const & src);

    enum class tesselationStateMembers_e : int 
    {
      none = 0,
      all = 
    };

    inline bool operator == (tesselationState_t const & lhs, tesselationState_t const & rhs) noexcept
    {
      return
;
    };

    inline bool operator != (tesselationState_t const & lhs, tesselationState_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct tesselationStateDiffs_t
    {
      tesselationStateMembers_e diffs;
    };

    inline bool doPodsDiffer(
      tesselationState_t const & lhs,
      tesselationState_t const & rhs,
      tesselationStateDiffs_t & tesselationState) noexcept
    {

      return tesselationState.diffs != tesselationStateMembers_e::none;
    };

    // stencilOp things

    struct stencilOp_t
    {
      vk::DepthStencilFailOp failOp;
      vk::DepthStencilPassOp passOp;
      vk::DepthStencilPassOp depthFailOp;
      vk::DepthStencilPassOp compareOp;
      vk::SomeKindOfMask compareMask;
      vk::SomeKindOfMask writeMask;
      int reference;
    };

    void importPod(
      humon::HuNode const & src, stencilOp_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, stencilOp_t & dest);

    void exportPod(stencilOp_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      stencilOp_t const & src, std::vector<uint8_t> & dest);

    std::string print(stencilOp_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, stencilOp_t const & src);

    enum class stencilOpMembers_e : int 
    {
      none = 0,
      failOp = 1 << 0,
      passOp = 1 << 1,
      depthFailOp = 1 << 2,
      compareOp = 1 << 3,
      compareMask = 1 << 4,
      writeMask = 1 << 5,
      reference = 1 << 6,
      all = failOp | passOp | depthFailOp | compareOp | compareMask | writeMask | reference
    };

    inline bool operator == (stencilOp_t const & lhs, stencilOp_t const & rhs) noexcept
    {
      return
        lhs.failOp == rhs.failOp &&
        lhs.passOp == rhs.passOp &&
        lhs.depthFailOp == rhs.depthFailOp &&
        lhs.compareOp == rhs.compareOp &&
        lhs.compareMask == rhs.compareMask &&
        lhs.writeMask == rhs.writeMask &&
        lhs.reference == rhs.reference;
    };

    inline bool operator != (stencilOp_t const & lhs, stencilOp_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct stencilOpDiffs_t
    {
      stencilOpMembers_e diffs;
    };

    inline bool doPodsDiffer(
      stencilOp_t const & lhs,
      stencilOp_t const & rhs,
      stencilOpDiffs_t & stencilOp) noexcept
    {
      // diff member 'failOp':
      if (lhs.failOp != rhs.failOp)
        { stencilOp.diffs |= stencilOpMembers_e::failOp; }
      // diff member 'passOp':
      if (lhs.passOp != rhs.passOp)
        { stencilOp.diffs |= stencilOpMembers_e::passOp; }
      // diff member 'depthFailOp':
      if (lhs.depthFailOp != rhs.depthFailOp)
        { stencilOp.diffs |= stencilOpMembers_e::depthFailOp; }
      // diff member 'compareOp':
      if (lhs.compareOp != rhs.compareOp)
        { stencilOp.diffs |= stencilOpMembers_e::compareOp; }
      // diff member 'compareMask':
      if (lhs.compareMask != rhs.compareMask)
        { stencilOp.diffs |= stencilOpMembers_e::compareMask; }
      // diff member 'writeMask':
      if (lhs.writeMask != rhs.writeMask)
        { stencilOp.diffs |= stencilOpMembers_e::writeMask; }
      // diff member 'reference':
      if (lhs.reference != rhs.reference)
        { stencilOp.diffs |= stencilOpMembers_e::reference; }

      return stencilOp.diffs != stencilOpMembers_e::none;
    };

    // depthStencilState things

    struct depthStencilState_t
    {
      bool depthTestEnable;
      bool depthWriteEnable;
      vk::DepthCompareOp depthCompareOp;
      bool depthBoundsTestEnable;
      bool stencilTestEnable;
      stencilOp_t frontStencioOpo;
      stencilOp_t backStencioOpo;
      float minDepthBounds;
      float maxDepthBounds;
    };

    void importPod(
      humon::HuNode const & src, depthStencilState_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, depthStencilState_t & dest);

    void exportPod(depthStencilState_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      depthStencilState_t const & src, std::vector<uint8_t> & dest);

    std::string print(depthStencilState_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, depthStencilState_t const & src);

    enum class depthStencilStateMembers_e : int 
    {
      none = 0,
      depthTestEnable = 1 << 0,
      depthWriteEnable = 1 << 1,
      depthCompareOp = 1 << 2,
      depthBoundsTestEnable = 1 << 3,
      stencilTestEnable = 1 << 4,
      frontStencioOpo = 1 << 5,
      backStencioOpo = 1 << 6,
      minDepthBounds = 1 << 7,
      maxDepthBounds = 1 << 8,
      all = depthTestEnable | depthWriteEnable | depthCompareOp | depthBoundsTestEnable | stencilTestEnable | frontStencioOpo | backStencioOpo | minDepthBounds | maxDepthBounds
    };

    inline bool operator == (depthStencilState_t const & lhs, depthStencilState_t const & rhs) noexcept
    {
      return
        lhs.depthTestEnable == rhs.depthTestEnable &&
        lhs.depthWriteEnable == rhs.depthWriteEnable &&
        lhs.depthCompareOp == rhs.depthCompareOp &&
        lhs.depthBoundsTestEnable == rhs.depthBoundsTestEnable &&
        lhs.stencilTestEnable == rhs.stencilTestEnable &&
        lhs.frontStencioOpo == rhs.frontStencioOpo &&
        lhs.backStencioOpo == rhs.backStencioOpo &&
        lhs.minDepthBounds == rhs.minDepthBounds &&
        lhs.maxDepthBounds == rhs.maxDepthBounds;
    };

    inline bool operator != (depthStencilState_t const & lhs, depthStencilState_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct depthStencilStateDiffs_t
    {
      depthStencilStateMembers_e diffs;
      stencilOpDiffs_t frontStencioOpo;
      stencilOpDiffs_t backStencioOpo;
    };

    inline bool doPodsDiffer(
      depthStencilState_t const & lhs,
      depthStencilState_t const & rhs,
      depthStencilStateDiffs_t & depthStencilState) noexcept
    {
      // diff member 'depthTestEnable':
      if (lhs.depthTestEnable != rhs.depthTestEnable)
        { depthStencilState.diffs |= depthStencilStateMembers_e::depthTestEnable; }
      // diff member 'depthWriteEnable':
      if (lhs.depthWriteEnable != rhs.depthWriteEnable)
        { depthStencilState.diffs |= depthStencilStateMembers_e::depthWriteEnable; }
      // diff member 'depthCompareOp':
      if (lhs.depthCompareOp != rhs.depthCompareOp)
        { depthStencilState.diffs |= depthStencilStateMembers_e::depthCompareOp; }
      // diff member 'depthBoundsTestEnable':
      if (lhs.depthBoundsTestEnable != rhs.depthBoundsTestEnable)
        { depthStencilState.diffs |= depthStencilStateMembers_e::depthBoundsTestEnable; }
      // diff member 'stencilTestEnable':
      if (lhs.stencilTestEnable != rhs.stencilTestEnable)
        { depthStencilState.diffs |= depthStencilStateMembers_e::stencilTestEnable; }
      // diff member 'frontStencioOpo':
      if (doPodsDiffer(lhs.frontStencioOpo, rhs.frontStencioOpo, depthStencilState.frontStencioOpo))
        { depthStencilState.diffs |= depthStencilStateMembers_e::frontStencioOpo; }
      // diff member 'backStencioOpo':
      if (doPodsDiffer(lhs.backStencioOpo, rhs.backStencioOpo, depthStencilState.backStencioOpo))
        { depthStencilState.diffs |= depthStencilStateMembers_e::backStencioOpo; }
      // diff member 'minDepthBounds':
      if (lhs.minDepthBounds != rhs.minDepthBounds)
        { depthStencilState.diffs |= depthStencilStateMembers_e::minDepthBounds; }
      // diff member 'maxDepthBounds':
      if (lhs.maxDepthBounds != rhs.maxDepthBounds)
        { depthStencilState.diffs |= depthStencilStateMembers_e::maxDepthBounds; }

      return depthStencilState.diffs != depthStencilStateMembers_e::none;
    };

    // material things

    struct material_t
    {
      stringDict<stage_t> stages;
      rasterizationState_t rasterizationState;
      multisampleState_t multisampleState;
      blendState_t blendState;
      tesselationState_t tesselationState;
      depthStencilState_t depthStencilState;
      std::vector<vk::DynamicStateFlagBits> dynamicStates;
    };

    void importPod(
      humon::HuNode const & src, material_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, material_t & dest);

    void exportPod(material_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      material_t const & src, std::vector<uint8_t> & dest);

    std::string print(material_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, material_t const & src);

    enum class materialMembers_e : int 
    {
      none = 0,
      stages = 1 << 0,
      rasterizationState = 1 << 1,
      multisampleState = 1 << 2,
      blendState = 1 << 3,
      tesselationState = 1 << 4,
      depthStencilState = 1 << 5,
      dynamicStates = 1 << 6,
      all = stages | rasterizationState | multisampleState | blendState | tesselationState | depthStencilState | dynamicStates
    };

    inline bool operator == (material_t const & lhs, material_t const & rhs) noexcept
    {
      return
        lhs.stages == rhs.stages &&
        lhs.rasterizationState == rhs.rasterizationState &&
        lhs.multisampleState == rhs.multisampleState &&
        lhs.blendState == rhs.blendState &&
        lhs.tesselationState == rhs.tesselationState &&
        lhs.depthStencilState == rhs.depthStencilState &&
        lhs.dynamicStates == rhs.dynamicStates;
    };

    inline bool operator != (material_t const & lhs, material_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct materialDiffs_t
    {
      materialMembers_e diffs;
      std::unordered_map<std::string, stageDiffs_t> stagesDiffs;
      rasterizationStateDiffs_t rasterizationState;
      multisampleStateDiffs_t multisampleState;
      blendStateDiffs_t blendState;
      tesselationStateDiffs_t tesselationState;
      depthStencilStateDiffs_t depthStencilState;
      std::unordered_set<size_t> dynamicStatesDiffs;
    };

    inline bool doPodsDiffer(
      material_t const & lhs,
      material_t const & rhs,
      materialDiffs_t & material) noexcept
    {
      // diff member 'stages':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.stages.keys)
        {
          stageDiffs_t diffsEntry;
          if (auto it = rhs.stages.keys().find(lhsKey); it != rhs.stages.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.stages[lhsIdx], rhs.stages[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          material.diffs |= materialMembers_e::stages;
          material.stagesDiffs.insert_or_assign(lhsKey, diffsEntry);
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.stages.keys())
        {
          if (auto it = lhs.stages.keys.find(rhsKey); it != lhs.stages.keys.end())
            { continue; }

          stageDiffs_t diffsEntry = { .diffs = stageMembers_e::all };
          material.stagesDiffs.insert_or_assign(rhsKey, diffsEntry);
        }
      }
      // diff member 'rasterizationState':
      if (doPodsDiffer(lhs.rasterizationState, rhs.rasterizationState, material.rasterizationState))
        { material.diffs |= materialMembers_e::rasterizationState; }
      // diff member 'multisampleState':
      if (doPodsDiffer(lhs.multisampleState, rhs.multisampleState, material.multisampleState))
        { material.diffs |= materialMembers_e::multisampleState; }
      // diff member 'blendState':
      if (doPodsDiffer(lhs.blendState, rhs.blendState, material.blendState))
        { material.diffs |= materialMembers_e::blendState; }
      // diff member 'tesselationState':
      if (doPodsDiffer(lhs.tesselationState, rhs.tesselationState, material.tesselationState))
        { material.diffs |= materialMembers_e::tesselationState; }
      // diff member 'depthStencilState':
      if (doPodsDiffer(lhs.depthStencilState, rhs.depthStencilState, material.depthStencilState))
        { material.diffs |= materialMembers_e::depthStencilState; }
      // diff member 'dynamicStates':
      {
        auto [mn, mx] = std::minmax(lhs.dynamicStates.size(), rhs.dynamicStates.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.dynamicStates[i] != rhs.dynamicStates[i])
          {
            material.diffs |= materialMembers_e::dynamicStates;
            material.dynamicStatesDiffs.insert(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          material.dynamicStatesDiffs.insert(i);
        }
      }

      return material.diffs != materialMembers_e::none;
    };

  }
}

#endif // #ifndef material_GEN_H
