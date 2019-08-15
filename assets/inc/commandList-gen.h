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


}

#endif // #ifndef commandList_GEN_H
