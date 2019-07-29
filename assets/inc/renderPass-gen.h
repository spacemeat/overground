#ifndef renderPass_GEN_H
#define renderPass_GEN_H

#include <string>
#include <vector>
#include <optional>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  struct attachment_t
  {
    std::string name;
    vk::AttachmentDescriptionFlagBits flags = (vk::AttachmentDescriptionFlagBits)0;
    vk::SampleCountFlagBits numSamples;
    vk::AttachmentLoadOp loadOp;
    vk::AttachmentStoreOp storeOp;
    vk::AttachmentLoadOp stencilLoadOp;
    vk::AttachmentStoreOp stencilStoreOp;
    vk::ImageLayout initialLayout;
    vk::ImageLayout finalLayout;
  };

  void importPod(
    humon::HuNode const & src, attachment_t & dest);

  void importPod(
    std::vector<uint8_t> const & src, attachment_t & dest);

  void exportPod(attachment_t const & src, 
    humon::HuNode & dest, int depth);

  void exportPod(
    attachment_t const & src, std::vector<uint8_t> & dest);

  std::string print(attachment_t const & src, int depth = 0);

  std::ostream & operator << (std::ostream & stream, attachment_t const & src);


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
    vk::SubpassDescriptionFlagBits flags;
    vk::PipelineBindPoint bindPoint;
    std::vector<subpassAttachment_t> inputAttachments;
    std::vector<subpassAttachment_t> colorAttachments;
    std::vector<subpassAttachment_t> resolveAttachments;
    std::optional<subpassAttachment_t> depthStencilAttachment;
    std::vector<unsigned int> preserveAttachments;
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


  struct subpassDependency_t
  {
    int srcSubpass;
    int dstSubpass;
    vk::PipelineStageFlagBits srcStageMask;
    vk::PipelineStageFlagBits dstStageMask;
    vk::AccessFlagBits srcAccessMask;
    vk::AccessFlagBits dstAccessMask;
  };

  void importPod(
    humon::HuNode const & src, subpassDependency_t & dest);

  void importPod(
    std::vector<uint8_t> const & src, subpassDependency_t & dest);

  void exportPod(subpassDependency_t const & src, 
    humon::HuNode & dest, int depth);

  void exportPod(
    subpassDependency_t const & src, std::vector<uint8_t> & dest);

  std::string print(subpassDependency_t const & src, int depth = 0);

  std::ostream & operator << (std::ostream & stream, subpassDependency_t const & src);


  struct renderPass_t
  {
    std::string name;
    std::vector<attachment_t> attachments;
    std::vector<subpass_t> subpasses;
    std::vector<subpassDependency_t> dependencies;
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
