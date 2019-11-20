#include "renderPlan-gen.h"

using namespace overground;
using namespace overground::renderPlan;
using namespace humon;
using namespace std;


void overground::renderPlan::importPod(
  humon::HuNode const & src, attachment_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "flags")
  {
    auto & src0 = src / "flags";
    vk::AttachmentDescriptionFlagBits dst0;
    dst0 = fromString<vk::AttachmentDescriptionFlagBits>((std::string) src0); // leaf
    dest.flags = std::move(dst0);
  }
  if (src % "numSamples")
  {
    auto & src0 = src / "numSamples";
    vk::SampleCountFlagBits dst0;
    dst0 = fromString<vk::SampleCountFlagBits>((std::string) src0); // leaf
    dest.numSamples = std::move(dst0);
  }
  if (src % "loadOp")
  {
    auto & src0 = src / "loadOp";
    vk::AttachmentLoadOp dst0;
    dst0 = fromString<vk::AttachmentLoadOp>((std::string) src0); // leaf
    dest.loadOp = std::move(dst0);
  }
  if (src % "storeOp")
  {
    auto & src0 = src / "storeOp";
    vk::AttachmentStoreOp dst0;
    dst0 = fromString<vk::AttachmentStoreOp>((std::string) src0); // leaf
    dest.storeOp = std::move(dst0);
  }
  if (src % "stencilLoadOp")
  {
    auto & src0 = src / "stencilLoadOp";
    vk::AttachmentLoadOp dst0;
    dst0 = fromString<vk::AttachmentLoadOp>((std::string) src0); // leaf
    dest.stencilLoadOp = std::move(dst0);
  }
  if (src % "stencilStoreOp")
  {
    auto & src0 = src / "stencilStoreOp";
    vk::AttachmentStoreOp dst0;
    dst0 = fromString<vk::AttachmentStoreOp>((std::string) src0); // leaf
    dest.stencilStoreOp = std::move(dst0);
  }
  if (src % "initialLayout")
  {
    auto & src0 = src / "initialLayout";
    vk::ImageLayout dst0;
    dst0 = fromString<vk::ImageLayout>((std::string) src0); // leaf
    dest.initialLayout = std::move(dst0);
  }
  if (src % "finalLayout")
  {
    auto & src0 = src / "finalLayout";
    vk::ImageLayout dst0;
    dst0 = fromString<vk::ImageLayout>((std::string) src0); // leaf
    dest.finalLayout = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, attachment_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(attachment_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
attachment_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  attachment_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "flags: ";
  ss << to_string(src.flags);
  ss << "\n" << indentIn << "numSamples: ";
  ss << to_string(src.numSamples);
  ss << "\n" << indentIn << "loadOp: ";
  ss << to_string(src.loadOp);
  ss << "\n" << indentIn << "storeOp: ";
  ss << to_string(src.storeOp);
  ss << "\n" << indentIn << "stencilLoadOp: ";
  ss << to_string(src.stencilLoadOp);
  ss << "\n" << indentIn << "stencilStoreOp: ";
  ss << to_string(src.stencilStoreOp);
  ss << "\n" << indentIn << "initialLayout: ";
  ss << to_string(src.initialLayout);
  ss << "\n" << indentIn << "finalLayout: ";
  ss << to_string(src.finalLayout);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, attachment_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, subpassAttachment_t & dest)
{
  if (src % "attachment")
  {
    auto & src0 = src / "attachment";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.attachment = std::move(dst0);
  }
  if (src % "layout")
  {
    auto & src0 = src / "layout";
    vk::ImageLayout dst0;
    dst0 = fromString<vk::ImageLayout>((std::string) src0); // leaf
    dest.layout = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, subpassAttachment_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(subpassAttachment_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
subpassAttachment_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  subpassAttachment_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "attachment: ";
  ss << (src.attachment);
  ss << "\n" << indentIn << "layout: ";
  ss << to_string(src.layout);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, subpassAttachment_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, subpass_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "flags")
  {
    auto & src0 = src / "flags";
    vk::SubpassDescriptionFlagBits dst0;
    dst0 = fromString<vk::SubpassDescriptionFlagBits>((std::string) src0); // leaf
    dest.flags = std::move(dst0);
  }
  if (src % "bindPoint")
  {
    auto & src0 = src / "bindPoint";
    vk::PipelineBindPoint dst0;
    dst0 = fromString<vk::PipelineBindPoint>((std::string) src0); // leaf
    dest.bindPoint = std::move(dst0);
  }
  if (src % "inputAttachments")
  {
    auto & src0 = src / "inputAttachments";
    std::vector<subpassAttachment_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      subpassAttachment_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.inputAttachments = std::move(dst0);
  }
  if (src % "colorAttachments")
  {
    auto & src0 = src / "colorAttachments";
    std::vector<subpassAttachment_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      subpassAttachment_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.colorAttachments = std::move(dst0);
  }
  if (src % "resolveAttachments")
  {
    auto & src0 = src / "resolveAttachments";
    std::vector<subpassAttachment_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      subpassAttachment_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.resolveAttachments = std::move(dst0);
  }
  if (src % "depthStencilAttachment")
  {
    auto & src0 = src / "depthStencilAttachment";
    std::optional<subpassAttachment_t> dst0;
    subpassAttachment_t dst1;
    {
      auto & src1 = src0;
      importPod(src1, dst1);
    }
    dst0.emplace(std::move(dst1));
    dest.depthStencilAttachment = std::move(dst0);
  }
  if (src % "preserveAttachments")
  {
    auto & src0 = src / "preserveAttachments";
    std::vector<unsigned int> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      unsigned int dst1;
      dst1 = (unsigned int) src1; // leaf

      dst0.push_back(std::move(dst1));
    }
    dest.preserveAttachments = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, subpass_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(subpass_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
subpass_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  subpass_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "flags: ";
  ss << to_string(src.flags);
  ss << "\n" << indentIn << "bindPoint: ";
  ss << to_string(src.bindPoint);
  ss << "\n" << indentIn << "inputAttachments: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.inputAttachments.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    subpassAttachment_t const & src0 = src.inputAttachments[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "colorAttachments: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.colorAttachments.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    subpassAttachment_t const & src0 = src.colorAttachments[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "resolveAttachments: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.resolveAttachments.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    subpassAttachment_t const & src0 = src.resolveAttachments[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "depthStencilAttachment: ";

  if ((bool) src.depthStencilAttachment)
  {
    subpassAttachment_t const & src0 = * src.depthStencilAttachment;
    ss << print(src0, depth + 1);
  }
  else
    { ss << "<undefined>"; }
  ss << "\n" << indentIn << "preserveAttachments: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.preserveAttachments.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    unsigned int const & src0 = src.preserveAttachments[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, subpass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, subpassDependency_t & dest)
{
  if (src % "srcSubpass")
  {
    auto & src0 = src / "srcSubpass";
    int dst0;
    dst0 = (int) src0; // leaf
    dest.srcSubpass = std::move(dst0);
  }
  if (src % "dstSubpass")
  {
    auto & src0 = src / "dstSubpass";
    int dst0;
    dst0 = (int) src0; // leaf
    dest.dstSubpass = std::move(dst0);
  }
  if (src % "srcStageMask")
  {
    auto & src0 = src / "srcStageMask";
    vk::PipelineStageFlagBits dst0;
    dst0 = fromString<vk::PipelineStageFlagBits>((std::string) src0); // leaf
    dest.srcStageMask = std::move(dst0);
  }
  if (src % "dstStageMask")
  {
    auto & src0 = src / "dstStageMask";
    vk::PipelineStageFlagBits dst0;
    dst0 = fromString<vk::PipelineStageFlagBits>((std::string) src0); // leaf
    dest.dstStageMask = std::move(dst0);
  }
  if (src % "srcAccessMask")
  {
    auto & src0 = src / "srcAccessMask";
    vk::AccessFlagBits dst0;
    dst0 = fromString<vk::AccessFlagBits>((std::string) src0); // leaf
    dest.srcAccessMask = std::move(dst0);
  }
  if (src % "dstAccessMask")
  {
    auto & src0 = src / "dstAccessMask";
    vk::AccessFlagBits dst0;
    dst0 = fromString<vk::AccessFlagBits>((std::string) src0); // leaf
    dest.dstAccessMask = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, subpassDependency_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(subpassDependency_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
subpassDependency_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  subpassDependency_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "srcSubpass: ";
  ss << (src.srcSubpass);
  ss << "\n" << indentIn << "dstSubpass: ";
  ss << (src.dstSubpass);
  ss << "\n" << indentIn << "srcStageMask: ";
  ss << to_string(src.srcStageMask);
  ss << "\n" << indentIn << "dstStageMask: ";
  ss << to_string(src.dstStageMask);
  ss << "\n" << indentIn << "srcAccessMask: ";
  ss << to_string(src.srcAccessMask);
  ss << "\n" << indentIn << "dstAccessMask: ";
  ss << to_string(src.dstAccessMask);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, subpassDependency_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, renderPass_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "attachments")
  {
    auto & src0 = src / "attachments";
    stringDict<attachment_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      attachment_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.attachments = std::move(dst0);
  }
  if (src % "subpasses")
  {
    auto & src0 = src / "subpasses";
    stringDict<subpass_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      subpass_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.subpasses = std::move(dst0);
  }
  if (src % "dependencies")
  {
    auto & src0 = src / "dependencies";
    std::vector<subpassDependency_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      subpassDependency_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.dependencies = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, renderPass_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(renderPass_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
renderPass_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  renderPass_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "attachments: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.attachments.size(); ++i0)
  {
    auto const & [key, idx] = src.attachments.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    attachment_t const & src0 = src.attachments[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << indentIn << "subpasses: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.subpasses.size(); ++i0)
  {
    auto const & [key, idx] = src.subpasses.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    subpass_t const & src0 = src.subpasses[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << indentIn << "dependencies: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.dependencies.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    subpassDependency_t const & src0 = src.dependencies[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, renderPass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, identifyVisibleThings_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "tags")
  {
    auto & src0 = src / "tags";
    std::vector<std::string> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf

      dst0.push_back(std::move(dst1));
    }
    dest.tags = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, identifyVisibleThings_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(identifyVisibleThings_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
identifyVisibleThings_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  identifyVisibleThings_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "tags: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.tags.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.tags[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, identifyVisibleThings_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, drawRecursiveCameras_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, drawRecursiveCameras_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(drawRecursiveCameras_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
drawRecursiveCameras_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  drawRecursiveCameras_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, drawRecursiveCameras_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, computeShadows_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "tags")
  {
    auto & src0 = src / "tags";
    std::vector<std::string> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf

      dst0.push_back(std::move(dst1));
    }
    dest.tags = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, computeShadows_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(computeShadows_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
computeShadows_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  computeShadows_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "tags: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.tags.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.tags[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, computeShadows_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, updateUbos_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, updateUbos_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(updateUbos_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
updateUbos_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  updateUbos_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, updateUbos_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, setRenderPass_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "renderPassName")
  {
    auto & src0 = src / "renderPassName";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.renderPassName = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, setRenderPass_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(setRenderPass_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
setRenderPass_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  setRenderPass_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "renderPassName: ";
  ss << (src.renderPassName);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, setRenderPass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, nextSubpass_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, nextSubpass_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(nextSubpass_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
nextSubpass_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  nextSubpass_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, nextSubpass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, endRenderPass_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, endRenderPass_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(endRenderPass_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
endRenderPass_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  endRenderPass_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, endRenderPass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, computeDepth_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "tags")
  {
    auto & src0 = src / "tags";
    std::vector<std::string> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf

      dst0.push_back(std::move(dst1));
    }
    dest.tags = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, computeDepth_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(computeDepth_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
computeDepth_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  computeDepth_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "tags: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.tags.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.tags[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, computeDepth_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, drawUi_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, drawUi_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(drawUi_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
drawUi_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  drawUi_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, drawUi_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, drawOpaque_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, drawOpaque_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(drawOpaque_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
drawOpaque_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  drawOpaque_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, drawOpaque_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, drawTransparent_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, drawTransparent_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(drawTransparent_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
drawTransparent_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  drawTransparent_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, drawTransparent_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, drawImposters_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, drawImposters_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(drawImposters_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
drawImposters_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  drawImposters_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, drawImposters_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, drawSkybox_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, drawSkybox_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(drawSkybox_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
drawSkybox_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  drawSkybox_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, drawSkybox_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, runPostEffects_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, runPostEffects_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(runPostEffects_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
runPostEffects_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  runPostEffects_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, runPostEffects_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, operationList_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "primaryPlan")
  {
    auto & src0 = src / "primaryPlan";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.primaryPlan = std::move(dst0);
  }
  if (src % "ops")
  {
    auto & src0 = src / "ops";
    std::vector<std::variant<identifyVisibleThings_t, drawRecursiveCameras_t, computeShadows_t, updateUbos_t, setRenderPass_t, nextSubpass_t, endRenderPass_t, computeDepth_t, drawUi_t, drawOpaque_t, drawTransparent_t, drawImposters_t, drawSkybox_t, runPostEffects_t>> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::variant<identifyVisibleThings_t, drawRecursiveCameras_t, computeShadows_t, updateUbos_t, setRenderPass_t, nextSubpass_t, endRenderPass_t, computeDepth_t, drawUi_t, drawOpaque_t, drawTransparent_t, drawImposters_t, drawSkybox_t, runPostEffects_t> dst1;
      {
        auto & src2 = src1;
        if (src2 % "type")
        {
          std::string const & typ = src2 / "type";
          if (typ == "") { throw std::runtime_error("objects of variant type require a \"type\" key."); }
          else if (typ == "identifyVisibleThings")
          {
            identifyVisibleThings_t dst2;
            importPod(src2, dst2);
            dst1.emplace<identifyVisibleThings_t>(std::move(dst2));
          }
          else if (typ == "drawRecursiveCameras")
          {
            drawRecursiveCameras_t dst2;
            importPod(src2, dst2);
            dst1.emplace<drawRecursiveCameras_t>(std::move(dst2));
          }
          else if (typ == "computeShadows")
          {
            computeShadows_t dst2;
            importPod(src2, dst2);
            dst1.emplace<computeShadows_t>(std::move(dst2));
          }
          else if (typ == "updateUbos")
          {
            updateUbos_t dst2;
            importPod(src2, dst2);
            dst1.emplace<updateUbos_t>(std::move(dst2));
          }
          else if (typ == "setRenderPass")
          {
            setRenderPass_t dst2;
            importPod(src2, dst2);
            dst1.emplace<setRenderPass_t>(std::move(dst2));
          }
          else if (typ == "nextSubpass")
          {
            nextSubpass_t dst2;
            importPod(src2, dst2);
            dst1.emplace<nextSubpass_t>(std::move(dst2));
          }
          else if (typ == "endRenderPass")
          {
            endRenderPass_t dst2;
            importPod(src2, dst2);
            dst1.emplace<endRenderPass_t>(std::move(dst2));
          }
          else if (typ == "computeDepth")
          {
            computeDepth_t dst2;
            importPod(src2, dst2);
            dst1.emplace<computeDepth_t>(std::move(dst2));
          }
          else if (typ == "drawUi")
          {
            drawUi_t dst2;
            importPod(src2, dst2);
            dst1.emplace<drawUi_t>(std::move(dst2));
          }
          else if (typ == "drawOpaque")
          {
            drawOpaque_t dst2;
            importPod(src2, dst2);
            dst1.emplace<drawOpaque_t>(std::move(dst2));
          }
          else if (typ == "drawTransparent")
          {
            drawTransparent_t dst2;
            importPod(src2, dst2);
            dst1.emplace<drawTransparent_t>(std::move(dst2));
          }
          else if (typ == "drawImposters")
          {
            drawImposters_t dst2;
            importPod(src2, dst2);
            dst1.emplace<drawImposters_t>(std::move(dst2));
          }
          else if (typ == "drawSkybox")
          {
            drawSkybox_t dst2;
            importPod(src2, dst2);
            dst1.emplace<drawSkybox_t>(std::move(dst2));
          }
          else if (typ == "runPostEffects")
          {
            runPostEffects_t dst2;
            importPod(src2, dst2);
            dst1.emplace<runPostEffects_t>(std::move(dst2));
          }

        }
        else { throw std::runtime_error("objects of variant type require a \"kind\" key."); }
      }

      dst0.push_back(std::move(dst1));
    }
    dest.ops = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, operationList_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(operationList_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
operationList_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  operationList_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "primaryPlan: ";
  ss << (src.primaryPlan);
  ss << "\n" << indentIn << "ops: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.ops.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::variant<identifyVisibleThings_t, drawRecursiveCameras_t, computeShadows_t, updateUbos_t, setRenderPass_t, nextSubpass_t, endRenderPass_t, computeDepth_t, drawUi_t, drawOpaque_t, drawTransparent_t, drawImposters_t, drawSkybox_t, runPostEffects_t> const & src0 = src.ops[i0];

    if (src0.valueless_by_exception())
      { ss << "bad state\n"; }
    else if (std::holds_alternative<identifyVisibleThings_t>(src0))
    {
      identifyVisibleThings_t const & src1 = std::get<identifyVisibleThings_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<drawRecursiveCameras_t>(src0))
    {
      drawRecursiveCameras_t const & src1 = std::get<drawRecursiveCameras_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<computeShadows_t>(src0))
    {
      computeShadows_t const & src1 = std::get<computeShadows_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<updateUbos_t>(src0))
    {
      updateUbos_t const & src1 = std::get<updateUbos_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<setRenderPass_t>(src0))
    {
      setRenderPass_t const & src1 = std::get<setRenderPass_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<nextSubpass_t>(src0))
    {
      nextSubpass_t const & src1 = std::get<nextSubpass_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<endRenderPass_t>(src0))
    {
      endRenderPass_t const & src1 = std::get<endRenderPass_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<computeDepth_t>(src0))
    {
      computeDepth_t const & src1 = std::get<computeDepth_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<drawUi_t>(src0))
    {
      drawUi_t const & src1 = std::get<drawUi_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<drawOpaque_t>(src0))
    {
      drawOpaque_t const & src1 = std::get<drawOpaque_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<drawTransparent_t>(src0))
    {
      drawTransparent_t const & src1 = std::get<drawTransparent_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<drawImposters_t>(src0))
    {
      drawImposters_t const & src1 = std::get<drawImposters_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<drawSkybox_t>(src0))
    {
      drawSkybox_t const & src1 = std::get<drawSkybox_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<runPostEffects_t>(src0))
    {
      runPostEffects_t const & src1 = std::get<runPostEffects_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else { ss << "(unknown variant)\n"; }
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, operationList_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::renderPlan::importPod(
  humon::HuNode const & src, renderPlan_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "renderPasses")
  {
    auto & src0 = src / "renderPasses";
    stringDict<renderPass_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      renderPass_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.renderPasses = std::move(dst0);
  }
  if (src % "operations")
  {
    auto & src0 = src / "operations";
    stringDict<operationList_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      operationList_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.operations = std::move(dst0);
  }
}

void overground::renderPlan::importPod(
std::vector<uint8_t> const & src, renderPlan_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(renderPlan_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::renderPlan::exportPod(
renderPlan_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::renderPlan::print(
  renderPlan_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "renderPasses: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.renderPasses.size(); ++i0)
  {
    auto const & [key, idx] = src.renderPasses.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    renderPass_t const & src0 = src.renderPasses[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << indentIn << "operations: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.operations.size(); ++i0)
  {
    auto const & [key, idx] = src.operations.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    operationList_t const & src0 = src.operations[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::renderPlan::operator << (ostream & stream, renderPlan_t const & rhs)
{
  stream << print(rhs);
  return stream;
}
