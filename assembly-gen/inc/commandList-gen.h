#ifndef commandList_GEN_H
#define commandList_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  namespace commandList
  {
    // cmdBindPipeline things

    struct cmdBindPipeline_t
    {
      std::string type;
      vk::PipelineBindPoint bindPoint;
      std::string pipelineName;
    };

    void importPod(
      humon::HuNode const & src, cmdBindPipeline_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdBindPipeline_t & dest);

    void exportPod(cmdBindPipeline_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdBindPipeline_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdBindPipeline_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdBindPipeline_t const & src);

    enum class cmdBindPipelineMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      bindPoint = 1 << 1,
      pipelineName = 1 << 2,
      all = type | bindPoint | pipelineName
    };

    inline bool operator == (cmdBindPipeline_t const & lhs, cmdBindPipeline_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.bindPoint == rhs.bindPoint &&
        lhs.pipelineName == rhs.pipelineName;
    };

    inline bool operator != (cmdBindPipeline_t const & lhs, cmdBindPipeline_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdBindPipelineDiffs_t
    {
      cmdBindPipelineMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdBindPipeline_t const & lhs,
      cmdBindPipeline_t const & rhs,
      cmdBindPipelineDiffs_t & cmdBindPipeline) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdBindPipeline.diffs |= cmdBindPipelineMembers_e::type; }
      // diff member 'bindPoint':
      if (lhs.bindPoint != rhs.bindPoint)
        { cmdBindPipeline.diffs |= cmdBindPipelineMembers_e::bindPoint; }
      // diff member 'pipelineName':
      if (lhs.pipelineName != rhs.pipelineName)
        { cmdBindPipeline.diffs |= cmdBindPipelineMembers_e::pipelineName; }

      return cmdBindPipeline.diffs != cmdBindPipelineMembers_e::none;
    };

    // cmdSetViewport things

    struct cmdSetViewport_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdSetViewport_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdSetViewport_t & dest);

    void exportPod(cmdSetViewport_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdSetViewport_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdSetViewport_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdSetViewport_t const & src);

    enum class cmdSetViewportMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdSetViewport_t const & lhs, cmdSetViewport_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdSetViewport_t const & lhs, cmdSetViewport_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdSetViewportDiffs_t
    {
      cmdSetViewportMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdSetViewport_t const & lhs,
      cmdSetViewport_t const & rhs,
      cmdSetViewportDiffs_t & cmdSetViewport) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdSetViewport.diffs |= cmdSetViewportMembers_e::type; }

      return cmdSetViewport.diffs != cmdSetViewportMembers_e::none;
    };

    // cmdSetScissor things

    struct cmdSetScissor_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdSetScissor_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdSetScissor_t & dest);

    void exportPod(cmdSetScissor_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdSetScissor_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdSetScissor_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdSetScissor_t const & src);

    enum class cmdSetScissorMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdSetScissor_t const & lhs, cmdSetScissor_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdSetScissor_t const & lhs, cmdSetScissor_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdSetScissorDiffs_t
    {
      cmdSetScissorMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdSetScissor_t const & lhs,
      cmdSetScissor_t const & rhs,
      cmdSetScissorDiffs_t & cmdSetScissor) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdSetScissor.diffs |= cmdSetScissorMembers_e::type; }

      return cmdSetScissor.diffs != cmdSetScissorMembers_e::none;
    };

    // cmdSetLineWidth things

    struct cmdSetLineWidth_t
    {
      std::string type;
      float width;
    };

    void importPod(
      humon::HuNode const & src, cmdSetLineWidth_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdSetLineWidth_t & dest);

    void exportPod(cmdSetLineWidth_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdSetLineWidth_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdSetLineWidth_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdSetLineWidth_t const & src);

    enum class cmdSetLineWidthMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      width = 1 << 1,
      all = type | width
    };

    inline bool operator == (cmdSetLineWidth_t const & lhs, cmdSetLineWidth_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.width == rhs.width;
    };

    inline bool operator != (cmdSetLineWidth_t const & lhs, cmdSetLineWidth_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdSetLineWidthDiffs_t
    {
      cmdSetLineWidthMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdSetLineWidth_t const & lhs,
      cmdSetLineWidth_t const & rhs,
      cmdSetLineWidthDiffs_t & cmdSetLineWidth) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdSetLineWidth.diffs |= cmdSetLineWidthMembers_e::type; }
      // diff member 'width':
      if (lhs.width != rhs.width)
        { cmdSetLineWidth.diffs |= cmdSetLineWidthMembers_e::width; }

      return cmdSetLineWidth.diffs != cmdSetLineWidthMembers_e::none;
    };

    // cmdSetDepthBias things

    struct cmdSetDepthBias_t
    {
      std::string type;
      float constantFactor;
      float clamp;
      float slopeFactor;
    };

    void importPod(
      humon::HuNode const & src, cmdSetDepthBias_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdSetDepthBias_t & dest);

    void exportPod(cmdSetDepthBias_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdSetDepthBias_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdSetDepthBias_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdSetDepthBias_t const & src);

    enum class cmdSetDepthBiasMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      constantFactor = 1 << 1,
      clamp = 1 << 2,
      slopeFactor = 1 << 3,
      all = type | constantFactor | clamp | slopeFactor
    };

    inline bool operator == (cmdSetDepthBias_t const & lhs, cmdSetDepthBias_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.constantFactor == rhs.constantFactor &&
        lhs.clamp == rhs.clamp &&
        lhs.slopeFactor == rhs.slopeFactor;
    };

    inline bool operator != (cmdSetDepthBias_t const & lhs, cmdSetDepthBias_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdSetDepthBiasDiffs_t
    {
      cmdSetDepthBiasMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdSetDepthBias_t const & lhs,
      cmdSetDepthBias_t const & rhs,
      cmdSetDepthBiasDiffs_t & cmdSetDepthBias) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdSetDepthBias.diffs |= cmdSetDepthBiasMembers_e::type; }
      // diff member 'constantFactor':
      if (lhs.constantFactor != rhs.constantFactor)
        { cmdSetDepthBias.diffs |= cmdSetDepthBiasMembers_e::constantFactor; }
      // diff member 'clamp':
      if (lhs.clamp != rhs.clamp)
        { cmdSetDepthBias.diffs |= cmdSetDepthBiasMembers_e::clamp; }
      // diff member 'slopeFactor':
      if (lhs.slopeFactor != rhs.slopeFactor)
        { cmdSetDepthBias.diffs |= cmdSetDepthBiasMembers_e::slopeFactor; }

      return cmdSetDepthBias.diffs != cmdSetDepthBiasMembers_e::none;
    };

    // cmdSetBlendConstants things

    struct cmdSetBlendConstants_t
    {
      std::string type;
      std::array<float, 4> constants;
    };

    void importPod(
      humon::HuNode const & src, cmdSetBlendConstants_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdSetBlendConstants_t & dest);

    void exportPod(cmdSetBlendConstants_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdSetBlendConstants_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdSetBlendConstants_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdSetBlendConstants_t const & src);

    enum class cmdSetBlendConstantsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      constants = 1 << 1,
      all = type | constants
    };

    inline bool operator == (cmdSetBlendConstants_t const & lhs, cmdSetBlendConstants_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.constants == rhs.constants;
    };

    inline bool operator != (cmdSetBlendConstants_t const & lhs, cmdSetBlendConstants_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdSetBlendConstantsDiffs_t
    {
      cmdSetBlendConstantsMembers_e diffs;
      std::vector<size_t> constantsDiffs;
    };

    inline bool doPodsDiffer(
      cmdSetBlendConstants_t const & lhs,
      cmdSetBlendConstants_t const & rhs,
      cmdSetBlendConstantsDiffs_t & cmdSetBlendConstants) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdSetBlendConstants.diffs |= cmdSetBlendConstantsMembers_e::type; }
      // diff member 'constants':
      for (size_t i = 0; i < lhs.constants.size(); ++i)
      {
        if (lhs.constants[i] != rhs.constants[i])
        {
          cmdSetBlendConstants.diffs |= cmdSetBlendConstantsMembers_e::constants;
          cmdSetBlendConstants.constantsDiffs.push_back(i);
        }
      }

      return cmdSetBlendConstants.diffs != cmdSetBlendConstantsMembers_e::none;
    };

    // cmdSetDepthBounds things

    struct cmdSetDepthBounds_t
    {
      std::string type;
      float min;
      float max;
    };

    void importPod(
      humon::HuNode const & src, cmdSetDepthBounds_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdSetDepthBounds_t & dest);

    void exportPod(cmdSetDepthBounds_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdSetDepthBounds_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdSetDepthBounds_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdSetDepthBounds_t const & src);

    enum class cmdSetDepthBoundsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      min = 1 << 1,
      max = 1 << 2,
      all = type | min | max
    };

    inline bool operator == (cmdSetDepthBounds_t const & lhs, cmdSetDepthBounds_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.min == rhs.min &&
        lhs.max == rhs.max;
    };

    inline bool operator != (cmdSetDepthBounds_t const & lhs, cmdSetDepthBounds_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdSetDepthBoundsDiffs_t
    {
      cmdSetDepthBoundsMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdSetDepthBounds_t const & lhs,
      cmdSetDepthBounds_t const & rhs,
      cmdSetDepthBoundsDiffs_t & cmdSetDepthBounds) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdSetDepthBounds.diffs |= cmdSetDepthBoundsMembers_e::type; }
      // diff member 'min':
      if (lhs.min != rhs.min)
        { cmdSetDepthBounds.diffs |= cmdSetDepthBoundsMembers_e::min; }
      // diff member 'max':
      if (lhs.max != rhs.max)
        { cmdSetDepthBounds.diffs |= cmdSetDepthBoundsMembers_e::max; }

      return cmdSetDepthBounds.diffs != cmdSetDepthBoundsMembers_e::none;
    };

    // cmdSetStencilCompareMask things

    struct cmdSetStencilCompareMask_t
    {
      std::string type;
      vk::StencilFaceFlagBits faceMask;
      uint32_t compareMask;
    };

    void importPod(
      humon::HuNode const & src, cmdSetStencilCompareMask_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdSetStencilCompareMask_t & dest);

    void exportPod(cmdSetStencilCompareMask_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdSetStencilCompareMask_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdSetStencilCompareMask_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdSetStencilCompareMask_t const & src);

    enum class cmdSetStencilCompareMaskMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      faceMask = 1 << 1,
      compareMask = 1 << 2,
      all = type | faceMask | compareMask
    };

    inline bool operator == (cmdSetStencilCompareMask_t const & lhs, cmdSetStencilCompareMask_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.faceMask == rhs.faceMask &&
        lhs.compareMask == rhs.compareMask;
    };

    inline bool operator != (cmdSetStencilCompareMask_t const & lhs, cmdSetStencilCompareMask_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdSetStencilCompareMaskDiffs_t
    {
      cmdSetStencilCompareMaskMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdSetStencilCompareMask_t const & lhs,
      cmdSetStencilCompareMask_t const & rhs,
      cmdSetStencilCompareMaskDiffs_t & cmdSetStencilCompareMask) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdSetStencilCompareMask.diffs |= cmdSetStencilCompareMaskMembers_e::type; }
      // diff member 'faceMask':
      if (lhs.faceMask != rhs.faceMask)
        { cmdSetStencilCompareMask.diffs |= cmdSetStencilCompareMaskMembers_e::faceMask; }
      // diff member 'compareMask':
      if (lhs.compareMask != rhs.compareMask)
        { cmdSetStencilCompareMask.diffs |= cmdSetStencilCompareMaskMembers_e::compareMask; }

      return cmdSetStencilCompareMask.diffs != cmdSetStencilCompareMaskMembers_e::none;
    };

    // cmdSetStencilWriteMask things

    struct cmdSetStencilWriteMask_t
    {
      std::string type;
      vk::StencilFaceFlagBits faceMask;
      uint32_t writeMask;
    };

    void importPod(
      humon::HuNode const & src, cmdSetStencilWriteMask_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdSetStencilWriteMask_t & dest);

    void exportPod(cmdSetStencilWriteMask_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdSetStencilWriteMask_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdSetStencilWriteMask_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdSetStencilWriteMask_t const & src);

    enum class cmdSetStencilWriteMaskMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      faceMask = 1 << 1,
      writeMask = 1 << 2,
      all = type | faceMask | writeMask
    };

    inline bool operator == (cmdSetStencilWriteMask_t const & lhs, cmdSetStencilWriteMask_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.faceMask == rhs.faceMask &&
        lhs.writeMask == rhs.writeMask;
    };

    inline bool operator != (cmdSetStencilWriteMask_t const & lhs, cmdSetStencilWriteMask_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdSetStencilWriteMaskDiffs_t
    {
      cmdSetStencilWriteMaskMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdSetStencilWriteMask_t const & lhs,
      cmdSetStencilWriteMask_t const & rhs,
      cmdSetStencilWriteMaskDiffs_t & cmdSetStencilWriteMask) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdSetStencilWriteMask.diffs |= cmdSetStencilWriteMaskMembers_e::type; }
      // diff member 'faceMask':
      if (lhs.faceMask != rhs.faceMask)
        { cmdSetStencilWriteMask.diffs |= cmdSetStencilWriteMaskMembers_e::faceMask; }
      // diff member 'writeMask':
      if (lhs.writeMask != rhs.writeMask)
        { cmdSetStencilWriteMask.diffs |= cmdSetStencilWriteMaskMembers_e::writeMask; }

      return cmdSetStencilWriteMask.diffs != cmdSetStencilWriteMaskMembers_e::none;
    };

    // cmdSetStencilReference things

    struct cmdSetStencilReference_t
    {
      std::string type;
      vk::StencilFaceFlagBits faceMask;
      uint32_t reference;
    };

    void importPod(
      humon::HuNode const & src, cmdSetStencilReference_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdSetStencilReference_t & dest);

    void exportPod(cmdSetStencilReference_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdSetStencilReference_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdSetStencilReference_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdSetStencilReference_t const & src);

    enum class cmdSetStencilReferenceMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      faceMask = 1 << 1,
      reference = 1 << 2,
      all = type | faceMask | reference
    };

    inline bool operator == (cmdSetStencilReference_t const & lhs, cmdSetStencilReference_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.faceMask == rhs.faceMask &&
        lhs.reference == rhs.reference;
    };

    inline bool operator != (cmdSetStencilReference_t const & lhs, cmdSetStencilReference_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdSetStencilReferenceDiffs_t
    {
      cmdSetStencilReferenceMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdSetStencilReference_t const & lhs,
      cmdSetStencilReference_t const & rhs,
      cmdSetStencilReferenceDiffs_t & cmdSetStencilReference) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdSetStencilReference.diffs |= cmdSetStencilReferenceMembers_e::type; }
      // diff member 'faceMask':
      if (lhs.faceMask != rhs.faceMask)
        { cmdSetStencilReference.diffs |= cmdSetStencilReferenceMembers_e::faceMask; }
      // diff member 'reference':
      if (lhs.reference != rhs.reference)
        { cmdSetStencilReference.diffs |= cmdSetStencilReferenceMembers_e::reference; }

      return cmdSetStencilReference.diffs != cmdSetStencilReferenceMembers_e::none;
    };

    // cmdBindDescriptorSets things

    struct cmdBindDescriptorSets_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdBindDescriptorSets_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdBindDescriptorSets_t & dest);

    void exportPod(cmdBindDescriptorSets_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdBindDescriptorSets_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdBindDescriptorSets_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdBindDescriptorSets_t const & src);

    enum class cmdBindDescriptorSetsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdBindDescriptorSets_t const & lhs, cmdBindDescriptorSets_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdBindDescriptorSets_t const & lhs, cmdBindDescriptorSets_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdBindDescriptorSetsDiffs_t
    {
      cmdBindDescriptorSetsMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdBindDescriptorSets_t const & lhs,
      cmdBindDescriptorSets_t const & rhs,
      cmdBindDescriptorSetsDiffs_t & cmdBindDescriptorSets) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdBindDescriptorSets.diffs |= cmdBindDescriptorSetsMembers_e::type; }

      return cmdBindDescriptorSets.diffs != cmdBindDescriptorSetsMembers_e::none;
    };

    // cmdBindIndexBuffer things

    struct cmdBindIndexBuffer_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdBindIndexBuffer_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdBindIndexBuffer_t & dest);

    void exportPod(cmdBindIndexBuffer_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdBindIndexBuffer_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdBindIndexBuffer_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdBindIndexBuffer_t const & src);

    enum class cmdBindIndexBufferMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdBindIndexBuffer_t const & lhs, cmdBindIndexBuffer_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdBindIndexBuffer_t const & lhs, cmdBindIndexBuffer_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdBindIndexBufferDiffs_t
    {
      cmdBindIndexBufferMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdBindIndexBuffer_t const & lhs,
      cmdBindIndexBuffer_t const & rhs,
      cmdBindIndexBufferDiffs_t & cmdBindIndexBuffer) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdBindIndexBuffer.diffs |= cmdBindIndexBufferMembers_e::type; }

      return cmdBindIndexBuffer.diffs != cmdBindIndexBufferMembers_e::none;
    };

    // cmdBindIndexBuffers things

    struct cmdBindIndexBuffers_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdBindIndexBuffers_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdBindIndexBuffers_t & dest);

    void exportPod(cmdBindIndexBuffers_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdBindIndexBuffers_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdBindIndexBuffers_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdBindIndexBuffers_t const & src);

    enum class cmdBindIndexBuffersMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdBindIndexBuffers_t const & lhs, cmdBindIndexBuffers_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdBindIndexBuffers_t const & lhs, cmdBindIndexBuffers_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdBindIndexBuffersDiffs_t
    {
      cmdBindIndexBuffersMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdBindIndexBuffers_t const & lhs,
      cmdBindIndexBuffers_t const & rhs,
      cmdBindIndexBuffersDiffs_t & cmdBindIndexBuffers) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdBindIndexBuffers.diffs |= cmdBindIndexBuffersMembers_e::type; }

      return cmdBindIndexBuffers.diffs != cmdBindIndexBuffersMembers_e::none;
    };

    // cmdDraw things

    struct cmdDraw_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdDraw_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdDraw_t & dest);

    void exportPod(cmdDraw_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdDraw_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdDraw_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdDraw_t const & src);

    enum class cmdDrawMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdDraw_t const & lhs, cmdDraw_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdDraw_t const & lhs, cmdDraw_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdDrawDiffs_t
    {
      cmdDrawMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdDraw_t const & lhs,
      cmdDraw_t const & rhs,
      cmdDrawDiffs_t & cmdDraw) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdDraw.diffs |= cmdDrawMembers_e::type; }

      return cmdDraw.diffs != cmdDrawMembers_e::none;
    };

    // cmdDrawIndexed things

    struct cmdDrawIndexed_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdDrawIndexed_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdDrawIndexed_t & dest);

    void exportPod(cmdDrawIndexed_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdDrawIndexed_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdDrawIndexed_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdDrawIndexed_t const & src);

    enum class cmdDrawIndexedMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdDrawIndexed_t const & lhs, cmdDrawIndexed_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdDrawIndexed_t const & lhs, cmdDrawIndexed_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdDrawIndexedDiffs_t
    {
      cmdDrawIndexedMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdDrawIndexed_t const & lhs,
      cmdDrawIndexed_t const & rhs,
      cmdDrawIndexedDiffs_t & cmdDrawIndexed) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdDrawIndexed.diffs |= cmdDrawIndexedMembers_e::type; }

      return cmdDrawIndexed.diffs != cmdDrawIndexedMembers_e::none;
    };

    // cmdDrawIndirect things

    struct cmdDrawIndirect_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdDrawIndirect_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdDrawIndirect_t & dest);

    void exportPod(cmdDrawIndirect_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdDrawIndirect_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdDrawIndirect_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdDrawIndirect_t const & src);

    enum class cmdDrawIndirectMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdDrawIndirect_t const & lhs, cmdDrawIndirect_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdDrawIndirect_t const & lhs, cmdDrawIndirect_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdDrawIndirectDiffs_t
    {
      cmdDrawIndirectMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdDrawIndirect_t const & lhs,
      cmdDrawIndirect_t const & rhs,
      cmdDrawIndirectDiffs_t & cmdDrawIndirect) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdDrawIndirect.diffs |= cmdDrawIndirectMembers_e::type; }

      return cmdDrawIndirect.diffs != cmdDrawIndirectMembers_e::none;
    };

    // cmdDrawIndexedIndirect things

    struct cmdDrawIndexedIndirect_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdDrawIndexedIndirect_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdDrawIndexedIndirect_t & dest);

    void exportPod(cmdDrawIndexedIndirect_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdDrawIndexedIndirect_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdDrawIndexedIndirect_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdDrawIndexedIndirect_t const & src);

    enum class cmdDrawIndexedIndirectMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdDrawIndexedIndirect_t const & lhs, cmdDrawIndexedIndirect_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdDrawIndexedIndirect_t const & lhs, cmdDrawIndexedIndirect_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdDrawIndexedIndirectDiffs_t
    {
      cmdDrawIndexedIndirectMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdDrawIndexedIndirect_t const & lhs,
      cmdDrawIndexedIndirect_t const & rhs,
      cmdDrawIndexedIndirectDiffs_t & cmdDrawIndexedIndirect) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdDrawIndexedIndirect.diffs |= cmdDrawIndexedIndirectMembers_e::type; }

      return cmdDrawIndexedIndirect.diffs != cmdDrawIndexedIndirectMembers_e::none;
    };

    // cmdDispatch things

    struct cmdDispatch_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdDispatch_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdDispatch_t & dest);

    void exportPod(cmdDispatch_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdDispatch_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdDispatch_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdDispatch_t const & src);

    enum class cmdDispatchMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdDispatch_t const & lhs, cmdDispatch_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdDispatch_t const & lhs, cmdDispatch_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdDispatchDiffs_t
    {
      cmdDispatchMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdDispatch_t const & lhs,
      cmdDispatch_t const & rhs,
      cmdDispatchDiffs_t & cmdDispatch) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdDispatch.diffs |= cmdDispatchMembers_e::type; }

      return cmdDispatch.diffs != cmdDispatchMembers_e::none;
    };

    // cmdDispatchIndirect things

    struct cmdDispatchIndirect_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdDispatchIndirect_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdDispatchIndirect_t & dest);

    void exportPod(cmdDispatchIndirect_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdDispatchIndirect_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdDispatchIndirect_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdDispatchIndirect_t const & src);

    enum class cmdDispatchIndirectMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdDispatchIndirect_t const & lhs, cmdDispatchIndirect_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdDispatchIndirect_t const & lhs, cmdDispatchIndirect_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdDispatchIndirectDiffs_t
    {
      cmdDispatchIndirectMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdDispatchIndirect_t const & lhs,
      cmdDispatchIndirect_t const & rhs,
      cmdDispatchIndirectDiffs_t & cmdDispatchIndirect) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdDispatchIndirect.diffs |= cmdDispatchIndirectMembers_e::type; }

      return cmdDispatchIndirect.diffs != cmdDispatchIndirectMembers_e::none;
    };

    // cmdCopyBuffer things

    struct cmdCopyBuffer_t
    {
      std::string type;
      std::string src;
      std::string dst;
    };

    void importPod(
      humon::HuNode const & src, cmdCopyBuffer_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdCopyBuffer_t & dest);

    void exportPod(cmdCopyBuffer_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdCopyBuffer_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdCopyBuffer_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdCopyBuffer_t const & src);

    enum class cmdCopyBufferMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      src = 1 << 1,
      dst = 1 << 2,
      all = type | src | dst
    };

    inline bool operator == (cmdCopyBuffer_t const & lhs, cmdCopyBuffer_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.src == rhs.src &&
        lhs.dst == rhs.dst;
    };

    inline bool operator != (cmdCopyBuffer_t const & lhs, cmdCopyBuffer_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdCopyBufferDiffs_t
    {
      cmdCopyBufferMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdCopyBuffer_t const & lhs,
      cmdCopyBuffer_t const & rhs,
      cmdCopyBufferDiffs_t & cmdCopyBuffer) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdCopyBuffer.diffs |= cmdCopyBufferMembers_e::type; }
      // diff member 'src':
      if (lhs.src != rhs.src)
        { cmdCopyBuffer.diffs |= cmdCopyBufferMembers_e::src; }
      // diff member 'dst':
      if (lhs.dst != rhs.dst)
        { cmdCopyBuffer.diffs |= cmdCopyBufferMembers_e::dst; }

      return cmdCopyBuffer.diffs != cmdCopyBufferMembers_e::none;
    };

    // cmdCopyImage things

    struct cmdCopyImage_t
    {
      std::string type;
      std::string src;
      std::string dst;
    };

    void importPod(
      humon::HuNode const & src, cmdCopyImage_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdCopyImage_t & dest);

    void exportPod(cmdCopyImage_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdCopyImage_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdCopyImage_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdCopyImage_t const & src);

    enum class cmdCopyImageMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      src = 1 << 1,
      dst = 1 << 2,
      all = type | src | dst
    };

    inline bool operator == (cmdCopyImage_t const & lhs, cmdCopyImage_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.src == rhs.src &&
        lhs.dst == rhs.dst;
    };

    inline bool operator != (cmdCopyImage_t const & lhs, cmdCopyImage_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdCopyImageDiffs_t
    {
      cmdCopyImageMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdCopyImage_t const & lhs,
      cmdCopyImage_t const & rhs,
      cmdCopyImageDiffs_t & cmdCopyImage) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdCopyImage.diffs |= cmdCopyImageMembers_e::type; }
      // diff member 'src':
      if (lhs.src != rhs.src)
        { cmdCopyImage.diffs |= cmdCopyImageMembers_e::src; }
      // diff member 'dst':
      if (lhs.dst != rhs.dst)
        { cmdCopyImage.diffs |= cmdCopyImageMembers_e::dst; }

      return cmdCopyImage.diffs != cmdCopyImageMembers_e::none;
    };

    // cmdBlitImage things

    struct cmdBlitImage_t
    {
      std::string type;
      std::string src;
      std::string dst;
      vk::Filter filter;
    };

    void importPod(
      humon::HuNode const & src, cmdBlitImage_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdBlitImage_t & dest);

    void exportPod(cmdBlitImage_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdBlitImage_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdBlitImage_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdBlitImage_t const & src);

    enum class cmdBlitImageMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      src = 1 << 1,
      dst = 1 << 2,
      filter = 1 << 3,
      all = type | src | dst | filter
    };

    inline bool operator == (cmdBlitImage_t const & lhs, cmdBlitImage_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.src == rhs.src &&
        lhs.dst == rhs.dst &&
        lhs.filter == rhs.filter;
    };

    inline bool operator != (cmdBlitImage_t const & lhs, cmdBlitImage_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdBlitImageDiffs_t
    {
      cmdBlitImageMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdBlitImage_t const & lhs,
      cmdBlitImage_t const & rhs,
      cmdBlitImageDiffs_t & cmdBlitImage) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdBlitImage.diffs |= cmdBlitImageMembers_e::type; }
      // diff member 'src':
      if (lhs.src != rhs.src)
        { cmdBlitImage.diffs |= cmdBlitImageMembers_e::src; }
      // diff member 'dst':
      if (lhs.dst != rhs.dst)
        { cmdBlitImage.diffs |= cmdBlitImageMembers_e::dst; }
      // diff member 'filter':
      if (lhs.filter != rhs.filter)
        { cmdBlitImage.diffs |= cmdBlitImageMembers_e::filter; }

      return cmdBlitImage.diffs != cmdBlitImageMembers_e::none;
    };

    // cmdCopyBufferToImage things

    struct cmdCopyBufferToImage_t
    {
      std::string type;
      std::string src;
      std::string dst;
    };

    void importPod(
      humon::HuNode const & src, cmdCopyBufferToImage_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdCopyBufferToImage_t & dest);

    void exportPod(cmdCopyBufferToImage_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdCopyBufferToImage_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdCopyBufferToImage_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdCopyBufferToImage_t const & src);

    enum class cmdCopyBufferToImageMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      src = 1 << 1,
      dst = 1 << 2,
      all = type | src | dst
    };

    inline bool operator == (cmdCopyBufferToImage_t const & lhs, cmdCopyBufferToImage_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.src == rhs.src &&
        lhs.dst == rhs.dst;
    };

    inline bool operator != (cmdCopyBufferToImage_t const & lhs, cmdCopyBufferToImage_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdCopyBufferToImageDiffs_t
    {
      cmdCopyBufferToImageMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdCopyBufferToImage_t const & lhs,
      cmdCopyBufferToImage_t const & rhs,
      cmdCopyBufferToImageDiffs_t & cmdCopyBufferToImage) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdCopyBufferToImage.diffs |= cmdCopyBufferToImageMembers_e::type; }
      // diff member 'src':
      if (lhs.src != rhs.src)
        { cmdCopyBufferToImage.diffs |= cmdCopyBufferToImageMembers_e::src; }
      // diff member 'dst':
      if (lhs.dst != rhs.dst)
        { cmdCopyBufferToImage.diffs |= cmdCopyBufferToImageMembers_e::dst; }

      return cmdCopyBufferToImage.diffs != cmdCopyBufferToImageMembers_e::none;
    };

    // cmdCopyImageToBuffer things

    struct cmdCopyImageToBuffer_t
    {
      std::string type;
      std::string src;
      std::string dst;
    };

    void importPod(
      humon::HuNode const & src, cmdCopyImageToBuffer_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdCopyImageToBuffer_t & dest);

    void exportPod(cmdCopyImageToBuffer_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdCopyImageToBuffer_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdCopyImageToBuffer_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdCopyImageToBuffer_t const & src);

    enum class cmdCopyImageToBufferMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      src = 1 << 1,
      dst = 1 << 2,
      all = type | src | dst
    };

    inline bool operator == (cmdCopyImageToBuffer_t const & lhs, cmdCopyImageToBuffer_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.src == rhs.src &&
        lhs.dst == rhs.dst;
    };

    inline bool operator != (cmdCopyImageToBuffer_t const & lhs, cmdCopyImageToBuffer_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdCopyImageToBufferDiffs_t
    {
      cmdCopyImageToBufferMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdCopyImageToBuffer_t const & lhs,
      cmdCopyImageToBuffer_t const & rhs,
      cmdCopyImageToBufferDiffs_t & cmdCopyImageToBuffer) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdCopyImageToBuffer.diffs |= cmdCopyImageToBufferMembers_e::type; }
      // diff member 'src':
      if (lhs.src != rhs.src)
        { cmdCopyImageToBuffer.diffs |= cmdCopyImageToBufferMembers_e::src; }
      // diff member 'dst':
      if (lhs.dst != rhs.dst)
        { cmdCopyImageToBuffer.diffs |= cmdCopyImageToBufferMembers_e::dst; }

      return cmdCopyImageToBuffer.diffs != cmdCopyImageToBufferMembers_e::none;
    };

    // cmdUpdateBuffer things

    struct cmdUpdateBuffer_t
    {
      std::string type;
      std::string dst;
    };

    void importPod(
      humon::HuNode const & src, cmdUpdateBuffer_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdUpdateBuffer_t & dest);

    void exportPod(cmdUpdateBuffer_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdUpdateBuffer_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdUpdateBuffer_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdUpdateBuffer_t const & src);

    enum class cmdUpdateBufferMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      dst = 1 << 1,
      all = type | dst
    };

    inline bool operator == (cmdUpdateBuffer_t const & lhs, cmdUpdateBuffer_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.dst == rhs.dst;
    };

    inline bool operator != (cmdUpdateBuffer_t const & lhs, cmdUpdateBuffer_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdUpdateBufferDiffs_t
    {
      cmdUpdateBufferMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdUpdateBuffer_t const & lhs,
      cmdUpdateBuffer_t const & rhs,
      cmdUpdateBufferDiffs_t & cmdUpdateBuffer) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdUpdateBuffer.diffs |= cmdUpdateBufferMembers_e::type; }
      // diff member 'dst':
      if (lhs.dst != rhs.dst)
        { cmdUpdateBuffer.diffs |= cmdUpdateBufferMembers_e::dst; }

      return cmdUpdateBuffer.diffs != cmdUpdateBufferMembers_e::none;
    };

    // cmdFillBuffer things

    struct cmdFillBuffer_t
    {
      std::string type;
      std::string dst;
      uint32_t data;
    };

    void importPod(
      humon::HuNode const & src, cmdFillBuffer_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdFillBuffer_t & dest);

    void exportPod(cmdFillBuffer_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdFillBuffer_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdFillBuffer_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdFillBuffer_t const & src);

    enum class cmdFillBufferMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      dst = 1 << 1,
      data = 1 << 2,
      all = type | dst | data
    };

    inline bool operator == (cmdFillBuffer_t const & lhs, cmdFillBuffer_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.dst == rhs.dst &&
        lhs.data == rhs.data;
    };

    inline bool operator != (cmdFillBuffer_t const & lhs, cmdFillBuffer_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdFillBufferDiffs_t
    {
      cmdFillBufferMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdFillBuffer_t const & lhs,
      cmdFillBuffer_t const & rhs,
      cmdFillBufferDiffs_t & cmdFillBuffer) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdFillBuffer.diffs |= cmdFillBufferMembers_e::type; }
      // diff member 'dst':
      if (lhs.dst != rhs.dst)
        { cmdFillBuffer.diffs |= cmdFillBufferMembers_e::dst; }
      // diff member 'data':
      if (lhs.data != rhs.data)
        { cmdFillBuffer.diffs |= cmdFillBufferMembers_e::data; }

      return cmdFillBuffer.diffs != cmdFillBufferMembers_e::none;
    };

    // cmdClearColorImage things

    struct cmdClearColorImage_t
    {
      std::string type;
      std::string dst;
      std::array<float, 4> color;
    };

    void importPod(
      humon::HuNode const & src, cmdClearColorImage_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdClearColorImage_t & dest);

    void exportPod(cmdClearColorImage_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdClearColorImage_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdClearColorImage_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdClearColorImage_t const & src);

    enum class cmdClearColorImageMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      dst = 1 << 1,
      color = 1 << 2,
      all = type | dst | color
    };

    inline bool operator == (cmdClearColorImage_t const & lhs, cmdClearColorImage_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.dst == rhs.dst &&
        lhs.color == rhs.color;
    };

    inline bool operator != (cmdClearColorImage_t const & lhs, cmdClearColorImage_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdClearColorImageDiffs_t
    {
      cmdClearColorImageMembers_e diffs;
      std::vector<size_t> colorDiffs;
    };

    inline bool doPodsDiffer(
      cmdClearColorImage_t const & lhs,
      cmdClearColorImage_t const & rhs,
      cmdClearColorImageDiffs_t & cmdClearColorImage) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdClearColorImage.diffs |= cmdClearColorImageMembers_e::type; }
      // diff member 'dst':
      if (lhs.dst != rhs.dst)
        { cmdClearColorImage.diffs |= cmdClearColorImageMembers_e::dst; }
      // diff member 'color':
      for (size_t i = 0; i < lhs.color.size(); ++i)
      {
        if (lhs.color[i] != rhs.color[i])
        {
          cmdClearColorImage.diffs |= cmdClearColorImageMembers_e::color;
          cmdClearColorImage.colorDiffs.push_back(i);
        }
      }

      return cmdClearColorImage.diffs != cmdClearColorImageMembers_e::none;
    };

    // cmdClearDepthStencilImage things

    struct cmdClearDepthStencilImage_t
    {
      std::string type;
      std::string dst;
      float depth;
      uint32_t stencil;
    };

    void importPod(
      humon::HuNode const & src, cmdClearDepthStencilImage_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdClearDepthStencilImage_t & dest);

    void exportPod(cmdClearDepthStencilImage_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdClearDepthStencilImage_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdClearDepthStencilImage_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdClearDepthStencilImage_t const & src);

    enum class cmdClearDepthStencilImageMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      dst = 1 << 1,
      depth = 1 << 2,
      stencil = 1 << 3,
      all = type | dst | depth | stencil
    };

    inline bool operator == (cmdClearDepthStencilImage_t const & lhs, cmdClearDepthStencilImage_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.dst == rhs.dst &&
        lhs.depth == rhs.depth &&
        lhs.stencil == rhs.stencil;
    };

    inline bool operator != (cmdClearDepthStencilImage_t const & lhs, cmdClearDepthStencilImage_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdClearDepthStencilImageDiffs_t
    {
      cmdClearDepthStencilImageMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdClearDepthStencilImage_t const & lhs,
      cmdClearDepthStencilImage_t const & rhs,
      cmdClearDepthStencilImageDiffs_t & cmdClearDepthStencilImage) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdClearDepthStencilImage.diffs |= cmdClearDepthStencilImageMembers_e::type; }
      // diff member 'dst':
      if (lhs.dst != rhs.dst)
        { cmdClearDepthStencilImage.diffs |= cmdClearDepthStencilImageMembers_e::dst; }
      // diff member 'depth':
      if (lhs.depth != rhs.depth)
        { cmdClearDepthStencilImage.diffs |= cmdClearDepthStencilImageMembers_e::depth; }
      // diff member 'stencil':
      if (lhs.stencil != rhs.stencil)
        { cmdClearDepthStencilImage.diffs |= cmdClearDepthStencilImageMembers_e::stencil; }

      return cmdClearDepthStencilImage.diffs != cmdClearDepthStencilImageMembers_e::none;
    };

    // cmdClearAttachments things

    struct cmdClearAttachments_t
    {
      std::string type;
      std::vector<std::string> attachments;
    };

    void importPod(
      humon::HuNode const & src, cmdClearAttachments_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdClearAttachments_t & dest);

    void exportPod(cmdClearAttachments_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdClearAttachments_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdClearAttachments_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdClearAttachments_t const & src);

    enum class cmdClearAttachmentsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      attachments = 1 << 1,
      all = type | attachments
    };

    inline bool operator == (cmdClearAttachments_t const & lhs, cmdClearAttachments_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.attachments == rhs.attachments;
    };

    inline bool operator != (cmdClearAttachments_t const & lhs, cmdClearAttachments_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdClearAttachmentsDiffs_t
    {
      cmdClearAttachmentsMembers_e diffs;
      std::vector<size_t> attachmentsDiffs;
    };

    inline bool doPodsDiffer(
      cmdClearAttachments_t const & lhs,
      cmdClearAttachments_t const & rhs,
      cmdClearAttachmentsDiffs_t & cmdClearAttachments) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdClearAttachments.diffs |= cmdClearAttachmentsMembers_e::type; }
      // diff member 'attachments':
      {
        auto [mn, mx] = std::minmax(lhs.attachments.size(), rhs.attachments.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.attachments[i] != rhs.attachments[i])
          {
            cmdClearAttachments.diffs |= cmdClearAttachmentsMembers_e::attachments;
            cmdClearAttachments.attachmentsDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          cmdClearAttachments.attachmentsDiffs.push_back(i);
        }
      }

      return cmdClearAttachments.diffs != cmdClearAttachmentsMembers_e::none;
    };

    // cmdResolveImage things

    struct cmdResolveImage_t
    {
      std::string type;
      std::string src;
      std::string dst;
    };

    void importPod(
      humon::HuNode const & src, cmdResolveImage_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdResolveImage_t & dest);

    void exportPod(cmdResolveImage_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdResolveImage_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdResolveImage_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdResolveImage_t const & src);

    enum class cmdResolveImageMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      src = 1 << 1,
      dst = 1 << 2,
      all = type | src | dst
    };

    inline bool operator == (cmdResolveImage_t const & lhs, cmdResolveImage_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.src == rhs.src &&
        lhs.dst == rhs.dst;
    };

    inline bool operator != (cmdResolveImage_t const & lhs, cmdResolveImage_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdResolveImageDiffs_t
    {
      cmdResolveImageMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdResolveImage_t const & lhs,
      cmdResolveImage_t const & rhs,
      cmdResolveImageDiffs_t & cmdResolveImage) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdResolveImage.diffs |= cmdResolveImageMembers_e::type; }
      // diff member 'src':
      if (lhs.src != rhs.src)
        { cmdResolveImage.diffs |= cmdResolveImageMembers_e::src; }
      // diff member 'dst':
      if (lhs.dst != rhs.dst)
        { cmdResolveImage.diffs |= cmdResolveImageMembers_e::dst; }

      return cmdResolveImage.diffs != cmdResolveImageMembers_e::none;
    };

    // cmdSetEvent things

    struct cmdSetEvent_t
    {
      std::string type;
      std::string event;
      vk::PipelineStageFlagBits stageMask;
    };

    void importPod(
      humon::HuNode const & src, cmdSetEvent_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdSetEvent_t & dest);

    void exportPod(cmdSetEvent_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdSetEvent_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdSetEvent_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdSetEvent_t const & src);

    enum class cmdSetEventMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      event = 1 << 1,
      stageMask = 1 << 2,
      all = type | event | stageMask
    };

    inline bool operator == (cmdSetEvent_t const & lhs, cmdSetEvent_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.event == rhs.event &&
        lhs.stageMask == rhs.stageMask;
    };

    inline bool operator != (cmdSetEvent_t const & lhs, cmdSetEvent_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdSetEventDiffs_t
    {
      cmdSetEventMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdSetEvent_t const & lhs,
      cmdSetEvent_t const & rhs,
      cmdSetEventDiffs_t & cmdSetEvent) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdSetEvent.diffs |= cmdSetEventMembers_e::type; }
      // diff member 'event':
      if (lhs.event != rhs.event)
        { cmdSetEvent.diffs |= cmdSetEventMembers_e::event; }
      // diff member 'stageMask':
      if (lhs.stageMask != rhs.stageMask)
        { cmdSetEvent.diffs |= cmdSetEventMembers_e::stageMask; }

      return cmdSetEvent.diffs != cmdSetEventMembers_e::none;
    };

    // cmdWaitEvents things

    struct cmdWaitEvents_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdWaitEvents_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdWaitEvents_t & dest);

    void exportPod(cmdWaitEvents_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdWaitEvents_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdWaitEvents_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdWaitEvents_t const & src);

    enum class cmdWaitEventsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdWaitEvents_t const & lhs, cmdWaitEvents_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdWaitEvents_t const & lhs, cmdWaitEvents_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdWaitEventsDiffs_t
    {
      cmdWaitEventsMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdWaitEvents_t const & lhs,
      cmdWaitEvents_t const & rhs,
      cmdWaitEventsDiffs_t & cmdWaitEvents) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdWaitEvents.diffs |= cmdWaitEventsMembers_e::type; }

      return cmdWaitEvents.diffs != cmdWaitEventsMembers_e::none;
    };

    // cmdPipelineBarrier things

    struct cmdPipelineBarrier_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdPipelineBarrier_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdPipelineBarrier_t & dest);

    void exportPod(cmdPipelineBarrier_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdPipelineBarrier_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdPipelineBarrier_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdPipelineBarrier_t const & src);

    enum class cmdPipelineBarrierMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdPipelineBarrier_t const & lhs, cmdPipelineBarrier_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdPipelineBarrier_t const & lhs, cmdPipelineBarrier_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdPipelineBarrierDiffs_t
    {
      cmdPipelineBarrierMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdPipelineBarrier_t const & lhs,
      cmdPipelineBarrier_t const & rhs,
      cmdPipelineBarrierDiffs_t & cmdPipelineBarrier) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdPipelineBarrier.diffs |= cmdPipelineBarrierMembers_e::type; }

      return cmdPipelineBarrier.diffs != cmdPipelineBarrierMembers_e::none;
    };

    // cmdBeginQuery things

    struct cmdBeginQuery_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdBeginQuery_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdBeginQuery_t & dest);

    void exportPod(cmdBeginQuery_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdBeginQuery_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdBeginQuery_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdBeginQuery_t const & src);

    enum class cmdBeginQueryMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdBeginQuery_t const & lhs, cmdBeginQuery_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdBeginQuery_t const & lhs, cmdBeginQuery_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdBeginQueryDiffs_t
    {
      cmdBeginQueryMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdBeginQuery_t const & lhs,
      cmdBeginQuery_t const & rhs,
      cmdBeginQueryDiffs_t & cmdBeginQuery) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdBeginQuery.diffs |= cmdBeginQueryMembers_e::type; }

      return cmdBeginQuery.diffs != cmdBeginQueryMembers_e::none;
    };

    // cmdEndQuery things

    struct cmdEndQuery_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdEndQuery_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdEndQuery_t & dest);

    void exportPod(cmdEndQuery_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdEndQuery_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdEndQuery_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdEndQuery_t const & src);

    enum class cmdEndQueryMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdEndQuery_t const & lhs, cmdEndQuery_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdEndQuery_t const & lhs, cmdEndQuery_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdEndQueryDiffs_t
    {
      cmdEndQueryMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdEndQuery_t const & lhs,
      cmdEndQuery_t const & rhs,
      cmdEndQueryDiffs_t & cmdEndQuery) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdEndQuery.diffs |= cmdEndQueryMembers_e::type; }

      return cmdEndQuery.diffs != cmdEndQueryMembers_e::none;
    };

    // cmdResetQueryPool things

    struct cmdResetQueryPool_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdResetQueryPool_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdResetQueryPool_t & dest);

    void exportPod(cmdResetQueryPool_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdResetQueryPool_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdResetQueryPool_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdResetQueryPool_t const & src);

    enum class cmdResetQueryPoolMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdResetQueryPool_t const & lhs, cmdResetQueryPool_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdResetQueryPool_t const & lhs, cmdResetQueryPool_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdResetQueryPoolDiffs_t
    {
      cmdResetQueryPoolMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdResetQueryPool_t const & lhs,
      cmdResetQueryPool_t const & rhs,
      cmdResetQueryPoolDiffs_t & cmdResetQueryPool) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdResetQueryPool.diffs |= cmdResetQueryPoolMembers_e::type; }

      return cmdResetQueryPool.diffs != cmdResetQueryPoolMembers_e::none;
    };

    // cmdWriteTimestamp things

    struct cmdWriteTimestamp_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdWriteTimestamp_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdWriteTimestamp_t & dest);

    void exportPod(cmdWriteTimestamp_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdWriteTimestamp_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdWriteTimestamp_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdWriteTimestamp_t const & src);

    enum class cmdWriteTimestampMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdWriteTimestamp_t const & lhs, cmdWriteTimestamp_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdWriteTimestamp_t const & lhs, cmdWriteTimestamp_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdWriteTimestampDiffs_t
    {
      cmdWriteTimestampMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdWriteTimestamp_t const & lhs,
      cmdWriteTimestamp_t const & rhs,
      cmdWriteTimestampDiffs_t & cmdWriteTimestamp) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdWriteTimestamp.diffs |= cmdWriteTimestampMembers_e::type; }

      return cmdWriteTimestamp.diffs != cmdWriteTimestampMembers_e::none;
    };

    // cmdCopyQueryPoolResults things

    struct cmdCopyQueryPoolResults_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdCopyQueryPoolResults_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdCopyQueryPoolResults_t & dest);

    void exportPod(cmdCopyQueryPoolResults_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdCopyQueryPoolResults_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdCopyQueryPoolResults_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdCopyQueryPoolResults_t const & src);

    enum class cmdCopyQueryPoolResultsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdCopyQueryPoolResults_t const & lhs, cmdCopyQueryPoolResults_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdCopyQueryPoolResults_t const & lhs, cmdCopyQueryPoolResults_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdCopyQueryPoolResultsDiffs_t
    {
      cmdCopyQueryPoolResultsMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdCopyQueryPoolResults_t const & lhs,
      cmdCopyQueryPoolResults_t const & rhs,
      cmdCopyQueryPoolResultsDiffs_t & cmdCopyQueryPoolResults) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdCopyQueryPoolResults.diffs |= cmdCopyQueryPoolResultsMembers_e::type; }

      return cmdCopyQueryPoolResults.diffs != cmdCopyQueryPoolResultsMembers_e::none;
    };

    // cmdPushConstants things

    struct cmdPushConstants_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdPushConstants_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdPushConstants_t & dest);

    void exportPod(cmdPushConstants_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdPushConstants_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdPushConstants_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdPushConstants_t const & src);

    enum class cmdPushConstantsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdPushConstants_t const & lhs, cmdPushConstants_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdPushConstants_t const & lhs, cmdPushConstants_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdPushConstantsDiffs_t
    {
      cmdPushConstantsMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdPushConstants_t const & lhs,
      cmdPushConstants_t const & rhs,
      cmdPushConstantsDiffs_t & cmdPushConstants) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdPushConstants.diffs |= cmdPushConstantsMembers_e::type; }

      return cmdPushConstants.diffs != cmdPushConstantsMembers_e::none;
    };

    // cmdBeginRenderPass things

    struct cmdBeginRenderPass_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdBeginRenderPass_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdBeginRenderPass_t & dest);

    void exportPod(cmdBeginRenderPass_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdBeginRenderPass_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdBeginRenderPass_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdBeginRenderPass_t const & src);

    enum class cmdBeginRenderPassMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdBeginRenderPass_t const & lhs, cmdBeginRenderPass_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdBeginRenderPass_t const & lhs, cmdBeginRenderPass_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdBeginRenderPassDiffs_t
    {
      cmdBeginRenderPassMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdBeginRenderPass_t const & lhs,
      cmdBeginRenderPass_t const & rhs,
      cmdBeginRenderPassDiffs_t & cmdBeginRenderPass) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdBeginRenderPass.diffs |= cmdBeginRenderPassMembers_e::type; }

      return cmdBeginRenderPass.diffs != cmdBeginRenderPassMembers_e::none;
    };

    // cmdNextSubpass things

    struct cmdNextSubpass_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdNextSubpass_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdNextSubpass_t & dest);

    void exportPod(cmdNextSubpass_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdNextSubpass_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdNextSubpass_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdNextSubpass_t const & src);

    enum class cmdNextSubpassMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdNextSubpass_t const & lhs, cmdNextSubpass_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdNextSubpass_t const & lhs, cmdNextSubpass_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdNextSubpassDiffs_t
    {
      cmdNextSubpassMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdNextSubpass_t const & lhs,
      cmdNextSubpass_t const & rhs,
      cmdNextSubpassDiffs_t & cmdNextSubpass) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdNextSubpass.diffs |= cmdNextSubpassMembers_e::type; }

      return cmdNextSubpass.diffs != cmdNextSubpassMembers_e::none;
    };

    // cmdEndRenderPass things

    struct cmdEndRenderPass_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, cmdEndRenderPass_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdEndRenderPass_t & dest);

    void exportPod(cmdEndRenderPass_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdEndRenderPass_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdEndRenderPass_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdEndRenderPass_t const & src);

    enum class cmdEndRenderPassMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (cmdEndRenderPass_t const & lhs, cmdEndRenderPass_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (cmdEndRenderPass_t const & lhs, cmdEndRenderPass_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdEndRenderPassDiffs_t
    {
      cmdEndRenderPassMembers_e diffs;
    };

    inline bool doPodsDiffer(
      cmdEndRenderPass_t const & lhs,
      cmdEndRenderPass_t const & rhs,
      cmdEndRenderPassDiffs_t & cmdEndRenderPass) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdEndRenderPass.diffs |= cmdEndRenderPassMembers_e::type; }

      return cmdEndRenderPass.diffs != cmdEndRenderPassMembers_e::none;
    };

    // cmdExecuteCommands things

    struct cmdExecuteCommands_t
    {
      std::string type;
      std::vector<std::string> commandBuffers;
    };

    void importPod(
      humon::HuNode const & src, cmdExecuteCommands_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, cmdExecuteCommands_t & dest);

    void exportPod(cmdExecuteCommands_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      cmdExecuteCommands_t const & src, std::vector<uint8_t> & dest);

    std::string print(cmdExecuteCommands_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, cmdExecuteCommands_t const & src);

    enum class cmdExecuteCommandsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      commandBuffers = 1 << 1,
      all = type | commandBuffers
    };

    inline bool operator == (cmdExecuteCommands_t const & lhs, cmdExecuteCommands_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.commandBuffers == rhs.commandBuffers;
    };

    inline bool operator != (cmdExecuteCommands_t const & lhs, cmdExecuteCommands_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct cmdExecuteCommandsDiffs_t
    {
      cmdExecuteCommandsMembers_e diffs;
      std::vector<size_t> commandBuffersDiffs;
    };

    inline bool doPodsDiffer(
      cmdExecuteCommands_t const & lhs,
      cmdExecuteCommands_t const & rhs,
      cmdExecuteCommandsDiffs_t & cmdExecuteCommands) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { cmdExecuteCommands.diffs |= cmdExecuteCommandsMembers_e::type; }
      // diff member 'commandBuffers':
      {
        auto [mn, mx] = std::minmax(lhs.commandBuffers.size(), rhs.commandBuffers.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.commandBuffers[i] != rhs.commandBuffers[i])
          {
            cmdExecuteCommands.diffs |= cmdExecuteCommandsMembers_e::commandBuffers;
            cmdExecuteCommands.commandBuffersDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          cmdExecuteCommands.commandBuffersDiffs.push_back(i);
        }
      }

      return cmdExecuteCommands.diffs != cmdExecuteCommandsMembers_e::none;
    };

    // commandList things

    struct commandList_t
    {
      std::string name;
      std::string queue;
      std::vector<std::variant<cmdBindPipeline_t, cmdSetViewport_t, cmdSetScissor_t, cmdSetLineWidth_t, cmdSetDepthBias_t, cmdSetBlendConstants_t, cmdSetDepthBounds_t, cmdSetStencilCompareMask_t, cmdSetStencilWriteMask_t, cmdSetStencilReference_t, cmdBindDescriptorSets_t, cmdBindIndexBuffer_t, cmdBindIndexBuffers_t, cmdDraw_t, cmdDrawIndexed_t, cmdDrawIndirect_t, cmdDrawIndexedIndirect_t, cmdDispatch_t, cmdDispatchIndirect_t, cmdCopyBuffer_t, cmdCopyImage_t, cmdBlitImage_t, cmdCopyBufferToImage_t, cmdCopyImageToBuffer_t, cmdUpdateBuffer_t, cmdFillBuffer_t, cmdClearColorImage_t, cmdClearDepthStencilImage_t, cmdClearAttachments_t, cmdResolveImage_t, cmdSetEvent_t, cmdWaitEvents_t, cmdPipelineBarrier_t, cmdPushConstants_t, cmdBeginRenderPass_t, cmdNextSubpass_t, cmdEndRenderPass_t, cmdExecuteCommands_t>> cmds;
    };

    void importPod(
      humon::HuNode const & src, commandList_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, commandList_t & dest);

    void exportPod(commandList_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      commandList_t const & src, std::vector<uint8_t> & dest);

    std::string print(commandList_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, commandList_t const & src);

    enum class commandListMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      queue = 1 << 1,
      cmds = 1 << 2,
      all = name | queue | cmds
    };

    inline bool operator == (commandList_t const & lhs, commandList_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.queue == rhs.queue &&
        lhs.cmds == rhs.cmds;
    };

    inline bool operator != (commandList_t const & lhs, commandList_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct commandListDiffs_t
    {
      commandListMembers_e diffs;
      std::vector<size_t> cmdsDiffs;
    };

    inline bool doPodsDiffer(
      commandList_t const & lhs,
      commandList_t const & rhs,
      commandListDiffs_t & commandList) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { commandList.diffs |= commandListMembers_e::name; }
      // diff member 'queue':
      if (lhs.queue != rhs.queue)
        { commandList.diffs |= commandListMembers_e::queue; }
      // diff member 'cmds':
      {
        auto [mn, mx] = std::minmax(lhs.cmds.size(), rhs.cmds.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.cmds[i] != rhs.cmds[i])
          {
            commandList.diffs |= commandListMembers_e::cmds;
            commandList.cmdsDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          commandList.cmdsDiffs.push_back(i);
        }
      }

      return commandList.diffs != commandListMembers_e::none;
    };

  }
}

#endif // #ifndef commandList_GEN_H
