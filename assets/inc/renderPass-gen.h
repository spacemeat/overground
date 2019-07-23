#ifndef renderPass_GEN_H
#define renderPass_GEN_H

#include <string>
#include <vector>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  struct subpassAttachment_t
  {
    std::string attachment;
    vk::ImageLayout layout;
  };

  void importPod(
    humon::HuNode const & src, subpassAttachment_t & dest);

  void importPod(
    std::vector<uint8_t> const & src, subpassAttachment_t & dest);

  void exportPod(subpassAttachment_t const & src, 
    humon::HuNode & dest, int depth);

  void exportPod(
    subpassAttachment_t const & src, std::vector<uint8_t> & dest);

  std::string print(subpassAttachment_t const & src, int depth = 0);

  std::ostream & operator << (std::ostream & stream, subpassAttachment_t const & src);


  struct subpass_t
  {
    std::string name;
    vk::PipelineBindPoint bindPoint;
    std::vector<subpassAttachment_t> colorAttachments;
  };

  void importPod(
    humon::HuNode const & src, subpass_t & dest);

  void importPod(
    std::vector<uint8_t> const & src, subpass_t & dest);

  void exportPod(subpass_t const & src, 
    humon::HuNode & dest, int depth);

  void exportPod(
    subpass_t const & src, std::vector<uint8_t> & dest);

  std::string print(subpass_t const & src, int depth = 0);

  std::ostream & operator << (std::ostream & stream, subpass_t const & src);


  struct renderPass_t
  {
    std::string name;
    vk::SampleCountFlagBits numSamples;
    vk::AttachmentLoadOp loadOp;
    vk::AttachmentStoreOp storeOp;
    vk::AttachmentLoadOp stencilLoadOp;
    vk::AttachmentStoreOp stencilStoreOp;
    vk::ImageLayout initialLayout;
    vk::ImageLayout finalLayout;
    std::vector<subpass_t> subpasses;
  };

  void importPod(
    humon::HuNode const & src, renderPass_t & dest);

  void importPod(
    std::vector<uint8_t> const & src, renderPass_t & dest);

  void exportPod(renderPass_t const & src, 
    humon::HuNode & dest, int depth);

  void exportPod(
    renderPass_t const & src, std::vector<uint8_t> & dest);

  std::string print(renderPass_t const & src, int depth = 0);

  std::ostream & operator << (std::ostream & stream, renderPass_t const & src);


}

#endif // #ifndef renderPass_GEN_H
