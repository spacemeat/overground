#include "renderPass-gen.h"

using namespace overground;
using namespace humon;
using namespace std;


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
  // NOTE: This operation has not been implemented yet.
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
  // NOTE: This operation has not been implemented yet.
}


std::string overground::print(
subpassAttachment_t const & src, int depth)
{
  std::ostringstream ss;
  ss << "{\n";
    ss << "    " << "attachment: ";
    ss << (src.attachment) << "\n";
    ss << "    " << "layout: ";
    ss << to_string(src.layout) << "\n";
  ss << "}\n";
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
  if (src % "bindPoint")
  {
    auto & src0 = src / "bindPoint";
    vk::PipelineBindPoint dst0;
    dst0 = fromString<vk::PipelineBindPoint>((std::string) src0); // leaf
    dest.bindPoint = std::move(dst0);
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
}

void overground::importPod(
std::vector<uint8_t> const & src, subpass_t & dest)
{
  // NOTE: This operation has not been implemented yet.
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
  // NOTE: This operation has not been implemented yet.
}


std::string overground::print(
subpass_t const & src, int depth)
{
  std::ostringstream ss;
  ss << "{\n";
    ss << "    " << "name: ";
    ss << (src.name) << "\n";
    ss << "    " << "bindPoint: ";
    ss << to_string(src.bindPoint) << "\n";
    ss << "    " << "colorAttachments: ";
    ss << "[\n";
    for (size_t i1 = 0; i1 < src.colorAttachments.size(); ++i1)
    {
      subpassAttachment_t const & src1 = src.colorAttachments[i1];
      ss << "    ";
      ss << print(src1, 3);
    }
    ss << "  " << "]\n";
  ss << "}\n";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, subpass_t const & rhs)
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
}

void overground::importPod(
std::vector<uint8_t> const & src, renderPass_t & dest)
{
  // NOTE: This operation has not been implemented yet.
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
  // NOTE: This operation has not been implemented yet.
}


std::string overground::print(
renderPass_t const & src, int depth)
{
  std::ostringstream ss;
  ss << "{\n";
    ss << "    " << "name: ";
    ss << (src.name) << "\n";
    ss << "    " << "numSamples: ";
    ss << to_string(src.numSamples) << "\n";
    ss << "    " << "loadOp: ";
    ss << to_string(src.loadOp) << "\n";
    ss << "    " << "storeOp: ";
    ss << to_string(src.storeOp) << "\n";
    ss << "    " << "stencilLoadOp: ";
    ss << to_string(src.stencilLoadOp) << "\n";
    ss << "    " << "stencilStoreOp: ";
    ss << to_string(src.stencilStoreOp) << "\n";
    ss << "    " << "initialLayout: ";
    ss << to_string(src.initialLayout) << "\n";
    ss << "    " << "finalLayout: ";
    ss << to_string(src.finalLayout) << "\n";
    ss << "    " << "subpasses: ";
    ss << "[\n";
    for (size_t i1 = 0; i1 < src.subpasses.size(); ++i1)
    {
      subpass_t const & src1 = src.subpasses[i1];
      ss << "    ";
      ss << print(src1, 3);
    }
    ss << "  " << "]\n";
  ss << "}\n";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, renderPass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


