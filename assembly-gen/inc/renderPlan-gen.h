#ifndef renderPlan_GEN_H
#define renderPlan_GEN_H

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
  namespace renderPlan
  {
    // attachment things

    struct attachment_t
    {
      std::string name;
      vk::AttachmentDescriptionFlagBits flags;
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

    enum class attachmentMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      flags = 1 << 1,
      numSamples = 1 << 2,
      loadOp = 1 << 3,
      storeOp = 1 << 4,
      stencilLoadOp = 1 << 5,
      stencilStoreOp = 1 << 6,
      initialLayout = 1 << 7,
      finalLayout = 1 << 8,
      all = name | flags | numSamples | loadOp | storeOp | stencilLoadOp | stencilStoreOp | initialLayout | finalLayout
    };

    inline bool operator == (attachment_t const & lhs, attachment_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.flags == rhs.flags &&
        lhs.numSamples == rhs.numSamples &&
        lhs.loadOp == rhs.loadOp &&
        lhs.storeOp == rhs.storeOp &&
        lhs.stencilLoadOp == rhs.stencilLoadOp &&
        lhs.stencilStoreOp == rhs.stencilStoreOp &&
        lhs.initialLayout == rhs.initialLayout &&
        lhs.finalLayout == rhs.finalLayout;
    };

    inline bool operator != (attachment_t const & lhs, attachment_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct attachmentDiffs_t
    {
      attachmentMembers_e diffs;
    };

    inline bool doPodsDiffer(
      attachment_t const & lhs,
      attachment_t const & rhs,
      attachmentDiffs_t & attachment) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { attachment.diffs |= attachmentMembers_e::name; }
      // diff member 'flags':
      if (lhs.flags != rhs.flags)
        { attachment.diffs |= attachmentMembers_e::flags; }
      // diff member 'numSamples':
      if (lhs.numSamples != rhs.numSamples)
        { attachment.diffs |= attachmentMembers_e::numSamples; }
      // diff member 'loadOp':
      if (lhs.loadOp != rhs.loadOp)
        { attachment.diffs |= attachmentMembers_e::loadOp; }
      // diff member 'storeOp':
      if (lhs.storeOp != rhs.storeOp)
        { attachment.diffs |= attachmentMembers_e::storeOp; }
      // diff member 'stencilLoadOp':
      if (lhs.stencilLoadOp != rhs.stencilLoadOp)
        { attachment.diffs |= attachmentMembers_e::stencilLoadOp; }
      // diff member 'stencilStoreOp':
      if (lhs.stencilStoreOp != rhs.stencilStoreOp)
        { attachment.diffs |= attachmentMembers_e::stencilStoreOp; }
      // diff member 'initialLayout':
      if (lhs.initialLayout != rhs.initialLayout)
        { attachment.diffs |= attachmentMembers_e::initialLayout; }
      // diff member 'finalLayout':
      if (lhs.finalLayout != rhs.finalLayout)
        { attachment.diffs |= attachmentMembers_e::finalLayout; }

      return attachment.diffs != attachmentMembers_e::none;
    };

    // subpassAttachment things

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

    enum class subpassAttachmentMembers_e : int 
    {
      none = 0,
      attachment = 1 << 0,
      layout = 1 << 1,
      all = attachment | layout
    };

    inline bool operator == (subpassAttachment_t const & lhs, subpassAttachment_t const & rhs) noexcept
    {
      return
        lhs.attachment == rhs.attachment &&
        lhs.layout == rhs.layout;
    };

    inline bool operator != (subpassAttachment_t const & lhs, subpassAttachment_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct subpassAttachmentDiffs_t
    {
      subpassAttachmentMembers_e diffs;
    };

    inline bool doPodsDiffer(
      subpassAttachment_t const & lhs,
      subpassAttachment_t const & rhs,
      subpassAttachmentDiffs_t & subpassAttachment) noexcept
    {
      // diff member 'attachment':
      if (lhs.attachment != rhs.attachment)
        { subpassAttachment.diffs |= subpassAttachmentMembers_e::attachment; }
      // diff member 'layout':
      if (lhs.layout != rhs.layout)
        { subpassAttachment.diffs |= subpassAttachmentMembers_e::layout; }

      return subpassAttachment.diffs != subpassAttachmentMembers_e::none;
    };

    // subpass things

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

    enum class subpassMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      flags = 1 << 1,
      bindPoint = 1 << 2,
      inputAttachments = 1 << 3,
      colorAttachments = 1 << 4,
      resolveAttachments = 1 << 5,
      depthStencilAttachment = 1 << 6,
      preserveAttachments = 1 << 7,
      all = name | flags | bindPoint | inputAttachments | colorAttachments | resolveAttachments | depthStencilAttachment | preserveAttachments
    };

    inline bool operator == (subpass_t const & lhs, subpass_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.flags == rhs.flags &&
        lhs.bindPoint == rhs.bindPoint &&
        lhs.inputAttachments == rhs.inputAttachments &&
        lhs.colorAttachments == rhs.colorAttachments &&
        lhs.resolveAttachments == rhs.resolveAttachments &&
        lhs.depthStencilAttachment == rhs.depthStencilAttachment &&
        lhs.preserveAttachments == rhs.preserveAttachments;
    };

    inline bool operator != (subpass_t const & lhs, subpass_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct subpassDiffs_t
    {
      subpassMembers_e diffs;
      std::unordered_map<size_t, subpassAttachmentDiffs_t> inputAttachmentsDiffs;
      std::unordered_map<size_t, subpassAttachmentDiffs_t> colorAttachmentsDiffs;
      std::unordered_map<size_t, subpassAttachmentDiffs_t> resolveAttachmentsDiffs;
      std::unordered_set<size_t> preserveAttachmentsDiffs;
    };

    inline bool doPodsDiffer(
      subpass_t const & lhs,
      subpass_t const & rhs,
      subpassDiffs_t & subpass) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { subpass.diffs |= subpassMembers_e::name; }
      // diff member 'flags':
      if (lhs.flags != rhs.flags)
        { subpass.diffs |= subpassMembers_e::flags; }
      // diff member 'bindPoint':
      if (lhs.bindPoint != rhs.bindPoint)
        { subpass.diffs |= subpassMembers_e::bindPoint; }
      // diff member 'inputAttachments':
      {
        auto [mn, mx] = std::minmax(lhs.inputAttachments.size(), rhs.inputAttachments.size());
        for (size_t i = 0; i < mn; ++i)
        {
          subpassAttachmentDiffs_t diffsEntry;
          if (doPodsDiffer(lhs.inputAttachments[i], rhs.inputAttachments[i], diffsEntry))
          {
            subpass.diffs |= subpassMembers_e::inputAttachments;
            subpass.inputAttachmentsDiffs.insert_or_assign(i, diffsEntry);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          subpassAttachmentDiffs_t diffsEntry = { .diffs = subpassAttachmentMembers_e::all };
          subpass.inputAttachmentsDiffs.insert_or_assign(i, diffsEntry);
        }
      }
      // diff member 'colorAttachments':
      {
        auto [mn, mx] = std::minmax(lhs.colorAttachments.size(), rhs.colorAttachments.size());
        for (size_t i = 0; i < mn; ++i)
        {
          subpassAttachmentDiffs_t diffsEntry;
          if (doPodsDiffer(lhs.colorAttachments[i], rhs.colorAttachments[i], diffsEntry))
          {
            subpass.diffs |= subpassMembers_e::colorAttachments;
            subpass.colorAttachmentsDiffs.insert_or_assign(i, diffsEntry);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          subpassAttachmentDiffs_t diffsEntry = { .diffs = subpassAttachmentMembers_e::all };
          subpass.colorAttachmentsDiffs.insert_or_assign(i, diffsEntry);
        }
      }
      // diff member 'resolveAttachments':
      {
        auto [mn, mx] = std::minmax(lhs.resolveAttachments.size(), rhs.resolveAttachments.size());
        for (size_t i = 0; i < mn; ++i)
        {
          subpassAttachmentDiffs_t diffsEntry;
          if (doPodsDiffer(lhs.resolveAttachments[i], rhs.resolveAttachments[i], diffsEntry))
          {
            subpass.diffs |= subpassMembers_e::resolveAttachments;
            subpass.resolveAttachmentsDiffs.insert_or_assign(i, diffsEntry);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          subpassAttachmentDiffs_t diffsEntry = { .diffs = subpassAttachmentMembers_e::all };
          subpass.resolveAttachmentsDiffs.insert_or_assign(i, diffsEntry);
        }
      }
      // diff member 'depthStencilAttachment':
      if (lhs.depthStencilAttachment != rhs.depthStencilAttachment)
        { subpass.diffs |= subpassMembers_e::depthStencilAttachment; }
      // diff member 'preserveAttachments':
      {
        auto [mn, mx] = std::minmax(lhs.preserveAttachments.size(), rhs.preserveAttachments.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.preserveAttachments[i] != rhs.preserveAttachments[i])
          {
            subpass.diffs |= subpassMembers_e::preserveAttachments;
            subpass.preserveAttachmentsDiffs.insert(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          subpass.preserveAttachmentsDiffs.insert(i);
        }
      }

      return subpass.diffs != subpassMembers_e::none;
    };

    // subpassDependency things

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

    enum class subpassDependencyMembers_e : int 
    {
      none = 0,
      srcSubpass = 1 << 0,
      dstSubpass = 1 << 1,
      srcStageMask = 1 << 2,
      dstStageMask = 1 << 3,
      srcAccessMask = 1 << 4,
      dstAccessMask = 1 << 5,
      all = srcSubpass | dstSubpass | srcStageMask | dstStageMask | srcAccessMask | dstAccessMask
    };

    inline bool operator == (subpassDependency_t const & lhs, subpassDependency_t const & rhs) noexcept
    {
      return
        lhs.srcSubpass == rhs.srcSubpass &&
        lhs.dstSubpass == rhs.dstSubpass &&
        lhs.srcStageMask == rhs.srcStageMask &&
        lhs.dstStageMask == rhs.dstStageMask &&
        lhs.srcAccessMask == rhs.srcAccessMask &&
        lhs.dstAccessMask == rhs.dstAccessMask;
    };

    inline bool operator != (subpassDependency_t const & lhs, subpassDependency_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct subpassDependencyDiffs_t
    {
      subpassDependencyMembers_e diffs;
    };

    inline bool doPodsDiffer(
      subpassDependency_t const & lhs,
      subpassDependency_t const & rhs,
      subpassDependencyDiffs_t & subpassDependency) noexcept
    {
      // diff member 'srcSubpass':
      if (lhs.srcSubpass != rhs.srcSubpass)
        { subpassDependency.diffs |= subpassDependencyMembers_e::srcSubpass; }
      // diff member 'dstSubpass':
      if (lhs.dstSubpass != rhs.dstSubpass)
        { subpassDependency.diffs |= subpassDependencyMembers_e::dstSubpass; }
      // diff member 'srcStageMask':
      if (lhs.srcStageMask != rhs.srcStageMask)
        { subpassDependency.diffs |= subpassDependencyMembers_e::srcStageMask; }
      // diff member 'dstStageMask':
      if (lhs.dstStageMask != rhs.dstStageMask)
        { subpassDependency.diffs |= subpassDependencyMembers_e::dstStageMask; }
      // diff member 'srcAccessMask':
      if (lhs.srcAccessMask != rhs.srcAccessMask)
        { subpassDependency.diffs |= subpassDependencyMembers_e::srcAccessMask; }
      // diff member 'dstAccessMask':
      if (lhs.dstAccessMask != rhs.dstAccessMask)
        { subpassDependency.diffs |= subpassDependencyMembers_e::dstAccessMask; }

      return subpassDependency.diffs != subpassDependencyMembers_e::none;
    };

    // renderPass things

    struct renderPass_t
    {
      std::string name;
      stringDict<attachment_t> attachments;
      stringDict<subpass_t> subpasses;
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

    enum class renderPassMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      attachments = 1 << 1,
      subpasses = 1 << 2,
      dependencies = 1 << 3,
      all = name | attachments | subpasses | dependencies
    };

    inline bool operator == (renderPass_t const & lhs, renderPass_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.attachments == rhs.attachments &&
        lhs.subpasses == rhs.subpasses &&
        lhs.dependencies == rhs.dependencies;
    };

    inline bool operator != (renderPass_t const & lhs, renderPass_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct renderPassDiffs_t
    {
      renderPassMembers_e diffs;
      std::unordered_map<std::string, attachmentDiffs_t> attachmentsDiffs;
      std::unordered_map<std::string, subpassDiffs_t> subpassesDiffs;
      std::unordered_map<size_t, subpassDependencyDiffs_t> dependenciesDiffs;
    };

    inline bool doPodsDiffer(
      renderPass_t const & lhs,
      renderPass_t const & rhs,
      renderPassDiffs_t & renderPass) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { renderPass.diffs |= renderPassMembers_e::name; }
      // diff member 'attachments':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.attachments.keys)
        {
          attachmentDiffs_t diffsEntry;
          if (auto it = rhs.attachments.keys().find(lhsKey); it != rhs.attachments.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.attachments[lhsIdx], rhs.attachments[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          renderPass.diffs |= renderPassMembers_e::attachments;
          renderPass.attachmentsDiffs.insert_or_assign(lhsKey, diffsEntry);
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.attachments.keys())
        {
          if (auto it = lhs.attachments.keys.find(rhsKey); it != lhs.attachments.keys.end())
            { continue; }

          attachmentDiffs_t diffsEntry = { .diffs = attachmentMembers_e::all };
          renderPass.attachmentsDiffs.insert_or_assign(rhsKey, diffsEntry);
        }
      }
      // diff member 'subpasses':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.subpasses.keys)
        {
          subpassDiffs_t diffsEntry;
          if (auto it = rhs.subpasses.keys().find(lhsKey); it != rhs.subpasses.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.subpasses[lhsIdx], rhs.subpasses[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          renderPass.diffs |= renderPassMembers_e::subpasses;
          renderPass.subpassesDiffs.insert_or_assign(lhsKey, diffsEntry);
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.subpasses.keys())
        {
          if (auto it = lhs.subpasses.keys.find(rhsKey); it != lhs.subpasses.keys.end())
            { continue; }

          subpassDiffs_t diffsEntry = { .diffs = subpassMembers_e::all };
          renderPass.subpassesDiffs.insert_or_assign(rhsKey, diffsEntry);
        }
      }
      // diff member 'dependencies':
      {
        auto [mn, mx] = std::minmax(lhs.dependencies.size(), rhs.dependencies.size());
        for (size_t i = 0; i < mn; ++i)
        {
          subpassDependencyDiffs_t diffsEntry;
          if (doPodsDiffer(lhs.dependencies[i], rhs.dependencies[i], diffsEntry))
          {
            renderPass.diffs |= renderPassMembers_e::dependencies;
            renderPass.dependenciesDiffs.insert_or_assign(i, diffsEntry);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          subpassDependencyDiffs_t diffsEntry = { .diffs = subpassDependencyMembers_e::all };
          renderPass.dependenciesDiffs.insert_or_assign(i, diffsEntry);
        }
      }

      return renderPass.diffs != renderPassMembers_e::none;
    };

    // identifyVisibleThings things

    struct identifyVisibleThings_t
    {
      std::string type;
      std::vector<std::string> tags;
    };

    void importPod(
      humon::HuNode const & src, identifyVisibleThings_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, identifyVisibleThings_t & dest);

    void exportPod(identifyVisibleThings_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      identifyVisibleThings_t const & src, std::vector<uint8_t> & dest);

    std::string print(identifyVisibleThings_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, identifyVisibleThings_t const & src);

    enum class identifyVisibleThingsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      tags = 1 << 1,
      all = type | tags
    };

    inline bool operator == (identifyVisibleThings_t const & lhs, identifyVisibleThings_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.tags == rhs.tags;
    };

    inline bool operator != (identifyVisibleThings_t const & lhs, identifyVisibleThings_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct identifyVisibleThingsDiffs_t
    {
      identifyVisibleThingsMembers_e diffs;
      std::unordered_set<size_t> tagsDiffs;
    };

    inline bool doPodsDiffer(
      identifyVisibleThings_t const & lhs,
      identifyVisibleThings_t const & rhs,
      identifyVisibleThingsDiffs_t & identifyVisibleThings) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { identifyVisibleThings.diffs |= identifyVisibleThingsMembers_e::type; }
      // diff member 'tags':
      {
        auto [mn, mx] = std::minmax(lhs.tags.size(), rhs.tags.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.tags[i] != rhs.tags[i])
          {
            identifyVisibleThings.diffs |= identifyVisibleThingsMembers_e::tags;
            identifyVisibleThings.tagsDiffs.insert(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          identifyVisibleThings.tagsDiffs.insert(i);
        }
      }

      return identifyVisibleThings.diffs != identifyVisibleThingsMembers_e::none;
    };

    // drawRecursiveCameras things

    struct drawRecursiveCameras_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, drawRecursiveCameras_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, drawRecursiveCameras_t & dest);

    void exportPod(drawRecursiveCameras_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      drawRecursiveCameras_t const & src, std::vector<uint8_t> & dest);

    std::string print(drawRecursiveCameras_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, drawRecursiveCameras_t const & src);

    enum class drawRecursiveCamerasMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (drawRecursiveCameras_t const & lhs, drawRecursiveCameras_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (drawRecursiveCameras_t const & lhs, drawRecursiveCameras_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct drawRecursiveCamerasDiffs_t
    {
      drawRecursiveCamerasMembers_e diffs;
    };

    inline bool doPodsDiffer(
      drawRecursiveCameras_t const & lhs,
      drawRecursiveCameras_t const & rhs,
      drawRecursiveCamerasDiffs_t & drawRecursiveCameras) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { drawRecursiveCameras.diffs |= drawRecursiveCamerasMembers_e::type; }

      return drawRecursiveCameras.diffs != drawRecursiveCamerasMembers_e::none;
    };

    // computeShadows things

    struct computeShadows_t
    {
      std::string type;
      std::vector<std::string> tags;
    };

    void importPod(
      humon::HuNode const & src, computeShadows_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, computeShadows_t & dest);

    void exportPod(computeShadows_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      computeShadows_t const & src, std::vector<uint8_t> & dest);

    std::string print(computeShadows_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, computeShadows_t const & src);

    enum class computeShadowsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      tags = 1 << 1,
      all = type | tags
    };

    inline bool operator == (computeShadows_t const & lhs, computeShadows_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.tags == rhs.tags;
    };

    inline bool operator != (computeShadows_t const & lhs, computeShadows_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct computeShadowsDiffs_t
    {
      computeShadowsMembers_e diffs;
      std::unordered_set<size_t> tagsDiffs;
    };

    inline bool doPodsDiffer(
      computeShadows_t const & lhs,
      computeShadows_t const & rhs,
      computeShadowsDiffs_t & computeShadows) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { computeShadows.diffs |= computeShadowsMembers_e::type; }
      // diff member 'tags':
      {
        auto [mn, mx] = std::minmax(lhs.tags.size(), rhs.tags.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.tags[i] != rhs.tags[i])
          {
            computeShadows.diffs |= computeShadowsMembers_e::tags;
            computeShadows.tagsDiffs.insert(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          computeShadows.tagsDiffs.insert(i);
        }
      }

      return computeShadows.diffs != computeShadowsMembers_e::none;
    };

    // updateUbos things

    struct updateUbos_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, updateUbos_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, updateUbos_t & dest);

    void exportPod(updateUbos_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      updateUbos_t const & src, std::vector<uint8_t> & dest);

    std::string print(updateUbos_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, updateUbos_t const & src);

    enum class updateUbosMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (updateUbos_t const & lhs, updateUbos_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (updateUbos_t const & lhs, updateUbos_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct updateUbosDiffs_t
    {
      updateUbosMembers_e diffs;
    };

    inline bool doPodsDiffer(
      updateUbos_t const & lhs,
      updateUbos_t const & rhs,
      updateUbosDiffs_t & updateUbos) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { updateUbos.diffs |= updateUbosMembers_e::type; }

      return updateUbos.diffs != updateUbosMembers_e::none;
    };

    // setRenderPass things

    struct setRenderPass_t
    {
      std::string type;
      std::string renderPassName;
    };

    void importPod(
      humon::HuNode const & src, setRenderPass_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, setRenderPass_t & dest);

    void exportPod(setRenderPass_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      setRenderPass_t const & src, std::vector<uint8_t> & dest);

    std::string print(setRenderPass_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, setRenderPass_t const & src);

    enum class setRenderPassMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      renderPassName = 1 << 1,
      all = type | renderPassName
    };

    inline bool operator == (setRenderPass_t const & lhs, setRenderPass_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.renderPassName == rhs.renderPassName;
    };

    inline bool operator != (setRenderPass_t const & lhs, setRenderPass_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct setRenderPassDiffs_t
    {
      setRenderPassMembers_e diffs;
    };

    inline bool doPodsDiffer(
      setRenderPass_t const & lhs,
      setRenderPass_t const & rhs,
      setRenderPassDiffs_t & setRenderPass) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { setRenderPass.diffs |= setRenderPassMembers_e::type; }
      // diff member 'renderPassName':
      if (lhs.renderPassName != rhs.renderPassName)
        { setRenderPass.diffs |= setRenderPassMembers_e::renderPassName; }

      return setRenderPass.diffs != setRenderPassMembers_e::none;
    };

    // nextSubpass things

    struct nextSubpass_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, nextSubpass_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, nextSubpass_t & dest);

    void exportPod(nextSubpass_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      nextSubpass_t const & src, std::vector<uint8_t> & dest);

    std::string print(nextSubpass_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, nextSubpass_t const & src);

    enum class nextSubpassMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (nextSubpass_t const & lhs, nextSubpass_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (nextSubpass_t const & lhs, nextSubpass_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct nextSubpassDiffs_t
    {
      nextSubpassMembers_e diffs;
    };

    inline bool doPodsDiffer(
      nextSubpass_t const & lhs,
      nextSubpass_t const & rhs,
      nextSubpassDiffs_t & nextSubpass) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { nextSubpass.diffs |= nextSubpassMembers_e::type; }

      return nextSubpass.diffs != nextSubpassMembers_e::none;
    };

    // endRenderPass things

    struct endRenderPass_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, endRenderPass_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, endRenderPass_t & dest);

    void exportPod(endRenderPass_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      endRenderPass_t const & src, std::vector<uint8_t> & dest);

    std::string print(endRenderPass_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, endRenderPass_t const & src);

    enum class endRenderPassMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (endRenderPass_t const & lhs, endRenderPass_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (endRenderPass_t const & lhs, endRenderPass_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct endRenderPassDiffs_t
    {
      endRenderPassMembers_e diffs;
    };

    inline bool doPodsDiffer(
      endRenderPass_t const & lhs,
      endRenderPass_t const & rhs,
      endRenderPassDiffs_t & endRenderPass) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { endRenderPass.diffs |= endRenderPassMembers_e::type; }

      return endRenderPass.diffs != endRenderPassMembers_e::none;
    };

    // computeDepth things

    struct computeDepth_t
    {
      std::string type;
      std::vector<std::string> tags;
    };

    void importPod(
      humon::HuNode const & src, computeDepth_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, computeDepth_t & dest);

    void exportPod(computeDepth_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      computeDepth_t const & src, std::vector<uint8_t> & dest);

    std::string print(computeDepth_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, computeDepth_t const & src);

    enum class computeDepthMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      tags = 1 << 1,
      all = type | tags
    };

    inline bool operator == (computeDepth_t const & lhs, computeDepth_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type &&
        lhs.tags == rhs.tags;
    };

    inline bool operator != (computeDepth_t const & lhs, computeDepth_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct computeDepthDiffs_t
    {
      computeDepthMembers_e diffs;
      std::unordered_set<size_t> tagsDiffs;
    };

    inline bool doPodsDiffer(
      computeDepth_t const & lhs,
      computeDepth_t const & rhs,
      computeDepthDiffs_t & computeDepth) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { computeDepth.diffs |= computeDepthMembers_e::type; }
      // diff member 'tags':
      {
        auto [mn, mx] = std::minmax(lhs.tags.size(), rhs.tags.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.tags[i] != rhs.tags[i])
          {
            computeDepth.diffs |= computeDepthMembers_e::tags;
            computeDepth.tagsDiffs.insert(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          computeDepth.tagsDiffs.insert(i);
        }
      }

      return computeDepth.diffs != computeDepthMembers_e::none;
    };

    // drawUi things

    struct drawUi_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, drawUi_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, drawUi_t & dest);

    void exportPod(drawUi_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      drawUi_t const & src, std::vector<uint8_t> & dest);

    std::string print(drawUi_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, drawUi_t const & src);

    enum class drawUiMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (drawUi_t const & lhs, drawUi_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (drawUi_t const & lhs, drawUi_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct drawUiDiffs_t
    {
      drawUiMembers_e diffs;
    };

    inline bool doPodsDiffer(
      drawUi_t const & lhs,
      drawUi_t const & rhs,
      drawUiDiffs_t & drawUi) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { drawUi.diffs |= drawUiMembers_e::type; }

      return drawUi.diffs != drawUiMembers_e::none;
    };

    // drawOpaque things

    struct drawOpaque_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, drawOpaque_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, drawOpaque_t & dest);

    void exportPod(drawOpaque_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      drawOpaque_t const & src, std::vector<uint8_t> & dest);

    std::string print(drawOpaque_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, drawOpaque_t const & src);

    enum class drawOpaqueMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (drawOpaque_t const & lhs, drawOpaque_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (drawOpaque_t const & lhs, drawOpaque_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct drawOpaqueDiffs_t
    {
      drawOpaqueMembers_e diffs;
    };

    inline bool doPodsDiffer(
      drawOpaque_t const & lhs,
      drawOpaque_t const & rhs,
      drawOpaqueDiffs_t & drawOpaque) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { drawOpaque.diffs |= drawOpaqueMembers_e::type; }

      return drawOpaque.diffs != drawOpaqueMembers_e::none;
    };

    // drawTransparent things

    struct drawTransparent_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, drawTransparent_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, drawTransparent_t & dest);

    void exportPod(drawTransparent_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      drawTransparent_t const & src, std::vector<uint8_t> & dest);

    std::string print(drawTransparent_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, drawTransparent_t const & src);

    enum class drawTransparentMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (drawTransparent_t const & lhs, drawTransparent_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (drawTransparent_t const & lhs, drawTransparent_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct drawTransparentDiffs_t
    {
      drawTransparentMembers_e diffs;
    };

    inline bool doPodsDiffer(
      drawTransparent_t const & lhs,
      drawTransparent_t const & rhs,
      drawTransparentDiffs_t & drawTransparent) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { drawTransparent.diffs |= drawTransparentMembers_e::type; }

      return drawTransparent.diffs != drawTransparentMembers_e::none;
    };

    // drawImposters things

    struct drawImposters_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, drawImposters_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, drawImposters_t & dest);

    void exportPod(drawImposters_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      drawImposters_t const & src, std::vector<uint8_t> & dest);

    std::string print(drawImposters_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, drawImposters_t const & src);

    enum class drawImpostersMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (drawImposters_t const & lhs, drawImposters_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (drawImposters_t const & lhs, drawImposters_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct drawImpostersDiffs_t
    {
      drawImpostersMembers_e diffs;
    };

    inline bool doPodsDiffer(
      drawImposters_t const & lhs,
      drawImposters_t const & rhs,
      drawImpostersDiffs_t & drawImposters) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { drawImposters.diffs |= drawImpostersMembers_e::type; }

      return drawImposters.diffs != drawImpostersMembers_e::none;
    };

    // drawSkybox things

    struct drawSkybox_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, drawSkybox_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, drawSkybox_t & dest);

    void exportPod(drawSkybox_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      drawSkybox_t const & src, std::vector<uint8_t> & dest);

    std::string print(drawSkybox_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, drawSkybox_t const & src);

    enum class drawSkyboxMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (drawSkybox_t const & lhs, drawSkybox_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (drawSkybox_t const & lhs, drawSkybox_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct drawSkyboxDiffs_t
    {
      drawSkyboxMembers_e diffs;
    };

    inline bool doPodsDiffer(
      drawSkybox_t const & lhs,
      drawSkybox_t const & rhs,
      drawSkyboxDiffs_t & drawSkybox) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { drawSkybox.diffs |= drawSkyboxMembers_e::type; }

      return drawSkybox.diffs != drawSkyboxMembers_e::none;
    };

    // runPostEffects things

    struct runPostEffects_t
    {
      std::string type;
    };

    void importPod(
      humon::HuNode const & src, runPostEffects_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, runPostEffects_t & dest);

    void exportPod(runPostEffects_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      runPostEffects_t const & src, std::vector<uint8_t> & dest);

    std::string print(runPostEffects_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, runPostEffects_t const & src);

    enum class runPostEffectsMembers_e : int 
    {
      none = 0,
      type = 1 << 0,
      all = type
    };

    inline bool operator == (runPostEffects_t const & lhs, runPostEffects_t const & rhs) noexcept
    {
      return
        lhs.type == rhs.type;
    };

    inline bool operator != (runPostEffects_t const & lhs, runPostEffects_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct runPostEffectsDiffs_t
    {
      runPostEffectsMembers_e diffs;
    };

    inline bool doPodsDiffer(
      runPostEffects_t const & lhs,
      runPostEffects_t const & rhs,
      runPostEffectsDiffs_t & runPostEffects) noexcept
    {
      // diff member 'type':
      if (lhs.type != rhs.type)
        { runPostEffects.diffs |= runPostEffectsMembers_e::type; }

      return runPostEffects.diffs != runPostEffectsMembers_e::none;
    };

    // operationList things

    struct operationList_t
    {
      std::string name;
      bool primaryPlan;
      std::vector<std::variant<identifyVisibleThings_t, drawRecursiveCameras_t, computeShadows_t, updateUbos_t, setRenderPass_t, nextSubpass_t, endRenderPass_t, computeDepth_t, drawUi_t, drawOpaque_t, drawTransparent_t, drawImposters_t, drawSkybox_t, runPostEffects_t>> ops;
    };

    void importPod(
      humon::HuNode const & src, operationList_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, operationList_t & dest);

    void exportPod(operationList_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      operationList_t const & src, std::vector<uint8_t> & dest);

    std::string print(operationList_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, operationList_t const & src);

    enum class operationListMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      primaryPlan = 1 << 1,
      ops = 1 << 2,
      all = name | primaryPlan | ops
    };

    inline bool operator == (operationList_t const & lhs, operationList_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.primaryPlan == rhs.primaryPlan &&
        lhs.ops == rhs.ops;
    };

    inline bool operator != (operationList_t const & lhs, operationList_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct operationListDiffs_t
    {
      operationListMembers_e diffs;
      std::unordered_set<size_t> opsDiffs;
    };

    inline bool doPodsDiffer(
      operationList_t const & lhs,
      operationList_t const & rhs,
      operationListDiffs_t & operationList) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { operationList.diffs |= operationListMembers_e::name; }
      // diff member 'primaryPlan':
      if (lhs.primaryPlan != rhs.primaryPlan)
        { operationList.diffs |= operationListMembers_e::primaryPlan; }
      // diff member 'ops':
      {
        auto [mn, mx] = std::minmax(lhs.ops.size(), rhs.ops.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.ops[i] != rhs.ops[i])
          {
            operationList.diffs |= operationListMembers_e::ops;
            operationList.opsDiffs.insert(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          operationList.opsDiffs.insert(i);
        }
      }

      return operationList.diffs != operationListMembers_e::none;
    };

    // renderPlan things

    struct renderPlan_t
    {
      std::string name;
      stringDict<renderPass_t> renderPasses;
      stringDict<operationList_t> operations;
    };

    void importPod(
      humon::HuNode const & src, renderPlan_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, renderPlan_t & dest);

    void exportPod(renderPlan_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      renderPlan_t const & src, std::vector<uint8_t> & dest);

    std::string print(renderPlan_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, renderPlan_t const & src);

    enum class renderPlanMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      renderPasses = 1 << 1,
      operations = 1 << 2,
      all = name | renderPasses | operations
    };

    inline bool operator == (renderPlan_t const & lhs, renderPlan_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.renderPasses == rhs.renderPasses &&
        lhs.operations == rhs.operations;
    };

    inline bool operator != (renderPlan_t const & lhs, renderPlan_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct renderPlanDiffs_t
    {
      renderPlanMembers_e diffs;
      std::unordered_map<std::string, renderPassDiffs_t> renderPassesDiffs;
      std::unordered_map<std::string, operationListDiffs_t> operationsDiffs;
    };

    inline bool doPodsDiffer(
      renderPlan_t const & lhs,
      renderPlan_t const & rhs,
      renderPlanDiffs_t & renderPlan) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { renderPlan.diffs |= renderPlanMembers_e::name; }
      // diff member 'renderPasses':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.renderPasses.keys)
        {
          renderPassDiffs_t diffsEntry;
          if (auto it = rhs.renderPasses.keys().find(lhsKey); it != rhs.renderPasses.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.renderPasses[lhsIdx], rhs.renderPasses[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          renderPlan.diffs |= renderPlanMembers_e::renderPasses;
          renderPlan.renderPassesDiffs.insert_or_assign(lhsKey, diffsEntry);
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.renderPasses.keys())
        {
          if (auto it = lhs.renderPasses.keys.find(rhsKey); it != lhs.renderPasses.keys.end())
            { continue; }

          renderPassDiffs_t diffsEntry = { .diffs = renderPassMembers_e::all };
          renderPlan.renderPassesDiffs.insert_or_assign(rhsKey, diffsEntry);
        }
      }
      // diff member 'operations':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.operations.keys)
        {
          operationListDiffs_t diffsEntry;
          if (auto it = rhs.operations.keys().find(lhsKey); it != rhs.operations.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.operations[lhsIdx], rhs.operations[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          renderPlan.diffs |= renderPlanMembers_e::operations;
          renderPlan.operationsDiffs.insert_or_assign(lhsKey, diffsEntry);
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.operations.keys())
        {
          if (auto it = lhs.operations.keys.find(rhsKey); it != lhs.operations.keys.end())
            { continue; }

          operationListDiffs_t diffsEntry = { .diffs = operationListMembers_e::all };
          renderPlan.operationsDiffs.insert_or_assign(rhsKey, diffsEntry);
        }
      }

      return renderPlan.diffs != renderPlanMembers_e::none;
    };

  }
}

#endif // #ifndef renderPlan_GEN_H
