#include "renderPass-gen.h"

using namespace overground;
using namespace humon;
using namespace std;


void overground::importPod(
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
void overground::importPod(
std::vector<uint8_t> const & src, attachment_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(attachment_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
attachment_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
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


ostream & overground::operator << (ostream & stream, attachment_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


void overground::importPod(
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
void overground::importPod(
std::vector<uint8_t> const & src, subpassAttachment_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(subpassAttachment_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
subpassAttachment_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
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


ostream & overground::operator << (ostream & stream, subpassAttachment_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


void overground::importPod(
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
void overground::importPod(
std::vector<uint8_t> const & src, subpass_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(subpass_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
subpass_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
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


ostream & overground::operator << (ostream & stream, subpass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


void overground::importPod(
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
void overground::importPod(
std::vector<uint8_t> const & src, subpassDependency_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(subpassDependency_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
subpassDependency_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
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


ostream & overground::operator << (ostream & stream, subpassDependency_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


void overground::importPod(
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
    std::vector<attachment_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      attachment_t dst1;
      importPod(src1, dst1);
      dst0.push_back(std::move(dst1));
    }
    dest.attachments = std::move(dst0);
  }
  if (src % "subpasses")
  {
    auto & src0 = src / "subpasses";
    std::vector<subpass_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      subpass_t dst1;
      importPod(src1, dst1);
      dst0.push_back(std::move(dst1));
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
void overground::importPod(
std::vector<uint8_t> const & src, renderPass_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(renderPass_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
renderPass_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
renderPass_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "attachments: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.attachments.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    attachment_t const & src0 = src.attachments[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "subpasses: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.subpasses.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    subpass_t const & src0 = src.subpasses[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
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


ostream & overground::operator << (ostream & stream, renderPass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


