#include "commandList-gen.h"

using namespace overground;
using namespace overground::commandList;
using namespace humon;
using namespace std;


void overground::commandList::importPod(
  humon::HuNode const & src, cmdBindPipeline_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "bindPoint")
  {
    auto & src0 = src / "bindPoint";
    vk::PipelineBindPoint dst0;
    dst0 = fromString<vk::PipelineBindPoint>((std::string) src0); // leaf
    dest.bindPoint = std::move(dst0);
  }
  if (src % "pipelineName")
  {
    auto & src0 = src / "pipelineName";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.pipelineName = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdBindPipeline_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdBindPipeline_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdBindPipeline_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdBindPipeline_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "bindPoint: ";
  ss << to_string(src.bindPoint);
  ss << "\n" << indentIn << "pipelineName: ";
  ss << (src.pipelineName);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdBindPipeline_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdSetViewport_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdSetViewport_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdSetViewport_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdSetViewport_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdSetViewport_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdSetViewport_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdSetScissor_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdSetScissor_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdSetScissor_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdSetScissor_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdSetScissor_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdSetScissor_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdSetLineWidth_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "width")
  {
    auto & src0 = src / "width";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.width = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdSetLineWidth_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdSetLineWidth_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdSetLineWidth_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdSetLineWidth_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "width: ";
  ss << (src.width);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdSetLineWidth_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdSetDepthBias_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "constantFactor")
  {
    auto & src0 = src / "constantFactor";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.constantFactor = std::move(dst0);
  }
  if (src % "clamp")
  {
    auto & src0 = src / "clamp";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.clamp = std::move(dst0);
  }
  if (src % "slopeFactor")
  {
    auto & src0 = src / "slopeFactor";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.slopeFactor = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdSetDepthBias_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdSetDepthBias_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdSetDepthBias_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdSetDepthBias_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "constantFactor: ";
  ss << (src.constantFactor);
  ss << "\n" << indentIn << "clamp: ";
  ss << (src.clamp);
  ss << "\n" << indentIn << "slopeFactor: ";
  ss << (src.slopeFactor);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdSetDepthBias_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdSetBlendConstants_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "constants")
  {
    auto & src0 = src / "constants";
    std::array<float, 4> dst0;
    for (size_t i0 = 0; i0 < 4; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.constants = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdSetBlendConstants_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdSetBlendConstants_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdSetBlendConstants_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdSetBlendConstants_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "constants: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.constants.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.constants[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdSetBlendConstants_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdSetDepthBounds_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "min")
  {
    auto & src0 = src / "min";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.min = std::move(dst0);
  }
  if (src % "max")
  {
    auto & src0 = src / "max";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.max = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdSetDepthBounds_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdSetDepthBounds_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdSetDepthBounds_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdSetDepthBounds_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "min: ";
  ss << (src.min);
  ss << "\n" << indentIn << "max: ";
  ss << (src.max);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdSetDepthBounds_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdSetStencilCompareMask_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "faceMask")
  {
    auto & src0 = src / "faceMask";
    vk::StencilFaceFlagBits dst0;
    dst0 = fromString<vk::StencilFaceFlagBits>((std::string) src0); // leaf
    dest.faceMask = std::move(dst0);
  }
  if (src % "compareMask")
  {
    auto & src0 = src / "compareMask";
    uint32_t dst0;
    dst0 = (uint32_t) src0; // leaf
    dest.compareMask = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdSetStencilCompareMask_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdSetStencilCompareMask_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdSetStencilCompareMask_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdSetStencilCompareMask_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "faceMask: ";
  ss << to_string(src.faceMask);
  ss << "\n" << indentIn << "compareMask: ";
  ss << (src.compareMask);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdSetStencilCompareMask_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdSetStencilWriteMask_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "faceMask")
  {
    auto & src0 = src / "faceMask";
    vk::StencilFaceFlagBits dst0;
    dst0 = fromString<vk::StencilFaceFlagBits>((std::string) src0); // leaf
    dest.faceMask = std::move(dst0);
  }
  if (src % "writeMask")
  {
    auto & src0 = src / "writeMask";
    uint32_t dst0;
    dst0 = (uint32_t) src0; // leaf
    dest.writeMask = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdSetStencilWriteMask_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdSetStencilWriteMask_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdSetStencilWriteMask_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdSetStencilWriteMask_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "faceMask: ";
  ss << to_string(src.faceMask);
  ss << "\n" << indentIn << "writeMask: ";
  ss << (src.writeMask);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdSetStencilWriteMask_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdSetStencilReference_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "faceMask")
  {
    auto & src0 = src / "faceMask";
    vk::StencilFaceFlagBits dst0;
    dst0 = fromString<vk::StencilFaceFlagBits>((std::string) src0); // leaf
    dest.faceMask = std::move(dst0);
  }
  if (src % "reference")
  {
    auto & src0 = src / "reference";
    uint32_t dst0;
    dst0 = (uint32_t) src0; // leaf
    dest.reference = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdSetStencilReference_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdSetStencilReference_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdSetStencilReference_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdSetStencilReference_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "faceMask: ";
  ss << to_string(src.faceMask);
  ss << "\n" << indentIn << "reference: ";
  ss << (src.reference);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdSetStencilReference_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdBindDescriptorSets_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdBindDescriptorSets_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdBindDescriptorSets_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdBindDescriptorSets_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdBindDescriptorSets_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdBindDescriptorSets_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdBindIndexBuffer_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdBindIndexBuffer_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdBindIndexBuffer_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdBindIndexBuffer_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdBindIndexBuffer_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdBindIndexBuffer_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdBindIndexBuffers_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdBindIndexBuffers_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdBindIndexBuffers_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdBindIndexBuffers_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdBindIndexBuffers_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdBindIndexBuffers_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdDraw_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdDraw_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdDraw_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdDraw_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdDraw_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdDraw_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdDrawIndexed_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdDrawIndexed_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdDrawIndexed_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdDrawIndexed_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdDrawIndexed_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdDrawIndexed_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdDrawIndirect_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdDrawIndirect_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdDrawIndirect_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdDrawIndirect_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdDrawIndirect_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdDrawIndirect_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdDrawIndexedIndirect_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdDrawIndexedIndirect_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdDrawIndexedIndirect_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdDrawIndexedIndirect_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdDrawIndexedIndirect_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdDrawIndexedIndirect_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdDispatch_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdDispatch_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdDispatch_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdDispatch_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdDispatch_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdDispatch_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdDispatchIndirect_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdDispatchIndirect_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdDispatchIndirect_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdDispatchIndirect_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdDispatchIndirect_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdDispatchIndirect_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdCopyBuffer_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "src")
  {
    auto & src0 = src / "src";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.src = std::move(dst0);
  }
  if (src % "dst")
  {
    auto & src0 = src / "dst";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.dst = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdCopyBuffer_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdCopyBuffer_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdCopyBuffer_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdCopyBuffer_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "src: ";
  ss << (src.src);
  ss << "\n" << indentIn << "dst: ";
  ss << (src.dst);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdCopyBuffer_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdCopyImage_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "src")
  {
    auto & src0 = src / "src";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.src = std::move(dst0);
  }
  if (src % "dst")
  {
    auto & src0 = src / "dst";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.dst = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdCopyImage_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdCopyImage_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdCopyImage_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdCopyImage_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "src: ";
  ss << (src.src);
  ss << "\n" << indentIn << "dst: ";
  ss << (src.dst);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdCopyImage_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdBlitImage_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "src")
  {
    auto & src0 = src / "src";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.src = std::move(dst0);
  }
  if (src % "dst")
  {
    auto & src0 = src / "dst";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.dst = std::move(dst0);
  }
  if (src % "filter")
  {
    auto & src0 = src / "filter";
    vk::Filter dst0;
    dst0 = fromString<vk::Filter>((std::string) src0); // leaf
    dest.filter = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdBlitImage_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdBlitImage_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdBlitImage_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdBlitImage_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "src: ";
  ss << (src.src);
  ss << "\n" << indentIn << "dst: ";
  ss << (src.dst);
  ss << "\n" << indentIn << "filter: ";
  ss << to_string(src.filter);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdBlitImage_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdCopyBufferToImage_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "src")
  {
    auto & src0 = src / "src";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.src = std::move(dst0);
  }
  if (src % "dst")
  {
    auto & src0 = src / "dst";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.dst = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdCopyBufferToImage_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdCopyBufferToImage_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdCopyBufferToImage_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdCopyBufferToImage_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "src: ";
  ss << (src.src);
  ss << "\n" << indentIn << "dst: ";
  ss << (src.dst);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdCopyBufferToImage_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdCopyImageToBuffer_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "src")
  {
    auto & src0 = src / "src";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.src = std::move(dst0);
  }
  if (src % "dst")
  {
    auto & src0 = src / "dst";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.dst = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdCopyImageToBuffer_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdCopyImageToBuffer_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdCopyImageToBuffer_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdCopyImageToBuffer_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "src: ";
  ss << (src.src);
  ss << "\n" << indentIn << "dst: ";
  ss << (src.dst);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdCopyImageToBuffer_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdUpdateBuffer_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "dst")
  {
    auto & src0 = src / "dst";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.dst = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdUpdateBuffer_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdUpdateBuffer_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdUpdateBuffer_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdUpdateBuffer_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "dst: ";
  ss << (src.dst);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdUpdateBuffer_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdFillBuffer_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "dst")
  {
    auto & src0 = src / "dst";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.dst = std::move(dst0);
  }
  if (src % "data")
  {
    auto & src0 = src / "data";
    uint32_t dst0;
    dst0 = (uint32_t) src0; // leaf
    dest.data = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdFillBuffer_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdFillBuffer_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdFillBuffer_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdFillBuffer_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "dst: ";
  ss << (src.dst);
  ss << "\n" << indentIn << "data: ";
  ss << (src.data);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdFillBuffer_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdClearColorImage_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "dst")
  {
    auto & src0 = src / "dst";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.dst = std::move(dst0);
  }
  if (src % "color")
  {
    auto & src0 = src / "color";
    std::array<float, 4> dst0;
    for (size_t i0 = 0; i0 < 4; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.color = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdClearColorImage_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdClearColorImage_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdClearColorImage_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdClearColorImage_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "dst: ";
  ss << (src.dst);
  ss << "\n" << indentIn << "color: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.color.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.color[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdClearColorImage_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdClearDepthStencilImage_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "dst")
  {
    auto & src0 = src / "dst";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.dst = std::move(dst0);
  }
  if (src % "depth")
  {
    auto & src0 = src / "depth";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.depth = std::move(dst0);
  }
  if (src % "stencil")
  {
    auto & src0 = src / "stencil";
    uint32_t dst0;
    dst0 = (uint32_t) src0; // leaf
    dest.stencil = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdClearDepthStencilImage_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdClearDepthStencilImage_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdClearDepthStencilImage_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdClearDepthStencilImage_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "dst: ";
  ss << (src.dst);
  ss << "\n" << indentIn << "depth: ";
  ss << (src.depth);
  ss << "\n" << indentIn << "stencil: ";
  ss << (src.stencil);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdClearDepthStencilImage_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdClearAttachments_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "attachments")
  {
    auto & src0 = src / "attachments";
    std::vector<std::string> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf

      dst0.push_back(std::move(dst1));
    }
    dest.attachments = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdClearAttachments_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdClearAttachments_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdClearAttachments_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdClearAttachments_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "attachments: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.attachments.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.attachments[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdClearAttachments_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdResolveImage_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "src")
  {
    auto & src0 = src / "src";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.src = std::move(dst0);
  }
  if (src % "dst")
  {
    auto & src0 = src / "dst";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.dst = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdResolveImage_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdResolveImage_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdResolveImage_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdResolveImage_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "src: ";
  ss << (src.src);
  ss << "\n" << indentIn << "dst: ";
  ss << (src.dst);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdResolveImage_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdSetEvent_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "event")
  {
    auto & src0 = src / "event";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.event = std::move(dst0);
  }
  if (src % "stageMask")
  {
    auto & src0 = src / "stageMask";
    vk::PipelineStageFlagBits dst0;
    dst0 = fromString<vk::PipelineStageFlagBits>((std::string) src0); // leaf
    dest.stageMask = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdSetEvent_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdSetEvent_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdSetEvent_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdSetEvent_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "event: ";
  ss << (src.event);
  ss << "\n" << indentIn << "stageMask: ";
  ss << to_string(src.stageMask);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdSetEvent_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdWaitEvents_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdWaitEvents_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdWaitEvents_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdWaitEvents_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdWaitEvents_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdWaitEvents_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdPipelineBarrier_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdPipelineBarrier_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdPipelineBarrier_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdPipelineBarrier_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdPipelineBarrier_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdPipelineBarrier_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdBeginQuery_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdBeginQuery_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdBeginQuery_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdBeginQuery_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdBeginQuery_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdBeginQuery_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdEndQuery_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdEndQuery_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdEndQuery_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdEndQuery_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdEndQuery_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdEndQuery_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdResetQueryPool_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdResetQueryPool_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdResetQueryPool_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdResetQueryPool_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdResetQueryPool_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdResetQueryPool_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdWriteTimestamp_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdWriteTimestamp_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdWriteTimestamp_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdWriteTimestamp_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdWriteTimestamp_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdWriteTimestamp_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdCopyQueryPoolResults_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdCopyQueryPoolResults_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdCopyQueryPoolResults_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdCopyQueryPoolResults_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdCopyQueryPoolResults_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdCopyQueryPoolResults_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdPushConstants_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdPushConstants_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdPushConstants_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdPushConstants_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdPushConstants_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdPushConstants_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdBeginRenderPass_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdBeginRenderPass_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdBeginRenderPass_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdBeginRenderPass_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdBeginRenderPass_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdBeginRenderPass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdNextSubpass_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdNextSubpass_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdNextSubpass_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdNextSubpass_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdNextSubpass_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdNextSubpass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdEndRenderPass_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdEndRenderPass_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdEndRenderPass_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdEndRenderPass_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdEndRenderPass_t const & src, int depth)
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

ostream & overground::commandList::operator << (ostream & stream, cmdEndRenderPass_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, cmdExecuteCommands_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "commandBuffers")
  {
    auto & src0 = src / "commandBuffers";
    std::vector<std::string> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::string dst1;
      dst1 = (std::string) src1; // leaf

      dst0.push_back(std::move(dst1));
    }
    dest.commandBuffers = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, cmdExecuteCommands_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(cmdExecuteCommands_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
cmdExecuteCommands_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  cmdExecuteCommands_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "commandBuffers: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.commandBuffers.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::string const & src0 = src.commandBuffers[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::commandList::operator << (ostream & stream, cmdExecuteCommands_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::commandList::importPod(
  humon::HuNode const & src, commandList_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "queue")
  {
    auto & src0 = src / "queue";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.queue = std::move(dst0);
  }
  if (src % "cmds")
  {
    auto & src0 = src / "cmds";
    std::vector<std::variant<cmdBindPipeline_t, cmdSetViewport_t, cmdSetScissor_t, cmdSetLineWidth_t, cmdSetDepthBias_t, cmdSetBlendConstants_t, cmdSetDepthBounds_t, cmdSetStencilCompareMask_t, cmdSetStencilWriteMask_t, cmdSetStencilReference_t, cmdBindDescriptorSets_t, cmdBindIndexBuffer_t, cmdBindIndexBuffers_t, cmdDraw_t, cmdDrawIndexed_t, cmdDrawIndirect_t, cmdDrawIndexedIndirect_t, cmdDispatch_t, cmdDispatchIndirect_t, cmdCopyBuffer_t, cmdCopyImage_t, cmdBlitImage_t, cmdCopyBufferToImage_t, cmdCopyImageToBuffer_t, cmdUpdateBuffer_t, cmdFillBuffer_t, cmdClearColorImage_t, cmdClearDepthStencilImage_t, cmdClearAttachments_t, cmdResolveImage_t, cmdSetEvent_t, cmdWaitEvents_t, cmdPipelineBarrier_t, cmdPushConstants_t, cmdBeginRenderPass_t, cmdNextSubpass_t, cmdEndRenderPass_t, cmdExecuteCommands_t>> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::variant<cmdBindPipeline_t, cmdSetViewport_t, cmdSetScissor_t, cmdSetLineWidth_t, cmdSetDepthBias_t, cmdSetBlendConstants_t, cmdSetDepthBounds_t, cmdSetStencilCompareMask_t, cmdSetStencilWriteMask_t, cmdSetStencilReference_t, cmdBindDescriptorSets_t, cmdBindIndexBuffer_t, cmdBindIndexBuffers_t, cmdDraw_t, cmdDrawIndexed_t, cmdDrawIndirect_t, cmdDrawIndexedIndirect_t, cmdDispatch_t, cmdDispatchIndirect_t, cmdCopyBuffer_t, cmdCopyImage_t, cmdBlitImage_t, cmdCopyBufferToImage_t, cmdCopyImageToBuffer_t, cmdUpdateBuffer_t, cmdFillBuffer_t, cmdClearColorImage_t, cmdClearDepthStencilImage_t, cmdClearAttachments_t, cmdResolveImage_t, cmdSetEvent_t, cmdWaitEvents_t, cmdPipelineBarrier_t, cmdPushConstants_t, cmdBeginRenderPass_t, cmdNextSubpass_t, cmdEndRenderPass_t, cmdExecuteCommands_t> dst1;
      {
        auto & src2 = src1;
        if (src2 % "type")
        {
          std::string const & typ = src2 / "type";
          if (typ == "") { throw std::runtime_error("objects of variant type require a \"type\" key."); }
          else if (typ == "cmdBindPipeline_t")
          {
            cmdBindPipeline_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdBindPipeline_t>(std::move(dst2));
          }
          else if (typ == "cmdSetViewport_t")
          {
            cmdSetViewport_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdSetViewport_t>(std::move(dst2));
          }
          else if (typ == "cmdSetScissor_t")
          {
            cmdSetScissor_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdSetScissor_t>(std::move(dst2));
          }
          else if (typ == "cmdSetLineWidth_t")
          {
            cmdSetLineWidth_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdSetLineWidth_t>(std::move(dst2));
          }
          else if (typ == "cmdSetDepthBias_t")
          {
            cmdSetDepthBias_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdSetDepthBias_t>(std::move(dst2));
          }
          else if (typ == "cmdSetBlendConstants_t")
          {
            cmdSetBlendConstants_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdSetBlendConstants_t>(std::move(dst2));
          }
          else if (typ == "cmdSetDepthBounds_t")
          {
            cmdSetDepthBounds_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdSetDepthBounds_t>(std::move(dst2));
          }
          else if (typ == "cmdSetStencilCompareMask_t")
          {
            cmdSetStencilCompareMask_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdSetStencilCompareMask_t>(std::move(dst2));
          }
          else if (typ == "cmdSetStencilWriteMask_t")
          {
            cmdSetStencilWriteMask_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdSetStencilWriteMask_t>(std::move(dst2));
          }
          else if (typ == "cmdSetStencilReference_t")
          {
            cmdSetStencilReference_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdSetStencilReference_t>(std::move(dst2));
          }
          else if (typ == "cmdBindDescriptorSets_t")
          {
            cmdBindDescriptorSets_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdBindDescriptorSets_t>(std::move(dst2));
          }
          else if (typ == "cmdBindIndexBuffer_t")
          {
            cmdBindIndexBuffer_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdBindIndexBuffer_t>(std::move(dst2));
          }
          else if (typ == "cmdBindIndexBuffers_t")
          {
            cmdBindIndexBuffers_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdBindIndexBuffers_t>(std::move(dst2));
          }
          else if (typ == "cmdDraw_t")
          {
            cmdDraw_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdDraw_t>(std::move(dst2));
          }
          else if (typ == "cmdDrawIndexed_t")
          {
            cmdDrawIndexed_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdDrawIndexed_t>(std::move(dst2));
          }
          else if (typ == "cmdDrawIndirect_t")
          {
            cmdDrawIndirect_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdDrawIndirect_t>(std::move(dst2));
          }
          else if (typ == "cmdDrawIndexedIndirect_t")
          {
            cmdDrawIndexedIndirect_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdDrawIndexedIndirect_t>(std::move(dst2));
          }
          else if (typ == "cmdDispatch_t")
          {
            cmdDispatch_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdDispatch_t>(std::move(dst2));
          }
          else if (typ == "cmdDispatchIndirect_t")
          {
            cmdDispatchIndirect_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdDispatchIndirect_t>(std::move(dst2));
          }
          else if (typ == "cmdCopyBuffer_t")
          {
            cmdCopyBuffer_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdCopyBuffer_t>(std::move(dst2));
          }
          else if (typ == "cmdCopyImage_t")
          {
            cmdCopyImage_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdCopyImage_t>(std::move(dst2));
          }
          else if (typ == "cmdBlitImage_t")
          {
            cmdBlitImage_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdBlitImage_t>(std::move(dst2));
          }
          else if (typ == "cmdCopyBufferToImage_t")
          {
            cmdCopyBufferToImage_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdCopyBufferToImage_t>(std::move(dst2));
          }
          else if (typ == "cmdCopyImageToBuffer_t")
          {
            cmdCopyImageToBuffer_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdCopyImageToBuffer_t>(std::move(dst2));
          }
          else if (typ == "cmdUpdateBuffer_t")
          {
            cmdUpdateBuffer_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdUpdateBuffer_t>(std::move(dst2));
          }
          else if (typ == "cmdFillBuffer_t")
          {
            cmdFillBuffer_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdFillBuffer_t>(std::move(dst2));
          }
          else if (typ == "cmdClearColorImage_t")
          {
            cmdClearColorImage_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdClearColorImage_t>(std::move(dst2));
          }
          else if (typ == "cmdClearDepthStencilImage_t")
          {
            cmdClearDepthStencilImage_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdClearDepthStencilImage_t>(std::move(dst2));
          }
          else if (typ == "cmdClearAttachments_t")
          {
            cmdClearAttachments_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdClearAttachments_t>(std::move(dst2));
          }
          else if (typ == "cmdResolveImage_t")
          {
            cmdResolveImage_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdResolveImage_t>(std::move(dst2));
          }
          else if (typ == "cmdSetEvent_t")
          {
            cmdSetEvent_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdSetEvent_t>(std::move(dst2));
          }
          else if (typ == "cmdWaitEvents_t")
          {
            cmdWaitEvents_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdWaitEvents_t>(std::move(dst2));
          }
          else if (typ == "cmdPipelineBarrier_t")
          {
            cmdPipelineBarrier_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdPipelineBarrier_t>(std::move(dst2));
          }
          else if (typ == "cmdPushConstants_t")
          {
            cmdPushConstants_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdPushConstants_t>(std::move(dst2));
          }
          else if (typ == "cmdBeginRenderPass_t")
          {
            cmdBeginRenderPass_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdBeginRenderPass_t>(std::move(dst2));
          }
          else if (typ == "cmdNextSubpass_t")
          {
            cmdNextSubpass_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdNextSubpass_t>(std::move(dst2));
          }
          else if (typ == "cmdEndRenderPass_t")
          {
            cmdEndRenderPass_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdEndRenderPass_t>(std::move(dst2));
          }
          else if (typ == "cmdExecuteCommands_t")
          {
            cmdExecuteCommands_t dst2;
        importPod(src2, dst2);
            dst1.emplace<cmdExecuteCommands_t>(std::move(dst2));
          }

        }
        else { throw std::runtime_error("objects of variant type require a \"kind\" key."); }
      }

      dst0.push_back(std::move(dst1));
    }
    dest.cmds = std::move(dst0);
  }
}

void overground::commandList::importPod(
std::vector<uint8_t> const & src, commandList_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(commandList_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::commandList::exportPod(
commandList_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::commandList::print(
  commandList_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "queue: ";
  ss << (src.queue);
  ss << "\n" << indentIn << "cmds: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.cmds.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::variant<cmdBindPipeline_t, cmdSetViewport_t, cmdSetScissor_t, cmdSetLineWidth_t, cmdSetDepthBias_t, cmdSetBlendConstants_t, cmdSetDepthBounds_t, cmdSetStencilCompareMask_t, cmdSetStencilWriteMask_t, cmdSetStencilReference_t, cmdBindDescriptorSets_t, cmdBindIndexBuffer_t, cmdBindIndexBuffers_t, cmdDraw_t, cmdDrawIndexed_t, cmdDrawIndirect_t, cmdDrawIndexedIndirect_t, cmdDispatch_t, cmdDispatchIndirect_t, cmdCopyBuffer_t, cmdCopyImage_t, cmdBlitImage_t, cmdCopyBufferToImage_t, cmdCopyImageToBuffer_t, cmdUpdateBuffer_t, cmdFillBuffer_t, cmdClearColorImage_t, cmdClearDepthStencilImage_t, cmdClearAttachments_t, cmdResolveImage_t, cmdSetEvent_t, cmdWaitEvents_t, cmdPipelineBarrier_t, cmdPushConstants_t, cmdBeginRenderPass_t, cmdNextSubpass_t, cmdEndRenderPass_t, cmdExecuteCommands_t> const & src0 = src.cmds[i0];

    if (src0.valueless_by_exception())
      { ss << "bad state\n"; }
    else if (std::holds_alternative<cmdBindPipeline_t>(src0))
    {
      cmdBindPipeline_t const & src1 = std::get<cmdBindPipeline_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdSetViewport_t>(src0))
    {
      cmdSetViewport_t const & src1 = std::get<cmdSetViewport_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdSetScissor_t>(src0))
    {
      cmdSetScissor_t const & src1 = std::get<cmdSetScissor_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdSetLineWidth_t>(src0))
    {
      cmdSetLineWidth_t const & src1 = std::get<cmdSetLineWidth_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdSetDepthBias_t>(src0))
    {
      cmdSetDepthBias_t const & src1 = std::get<cmdSetDepthBias_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdSetBlendConstants_t>(src0))
    {
      cmdSetBlendConstants_t const & src1 = std::get<cmdSetBlendConstants_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdSetDepthBounds_t>(src0))
    {
      cmdSetDepthBounds_t const & src1 = std::get<cmdSetDepthBounds_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdSetStencilCompareMask_t>(src0))
    {
      cmdSetStencilCompareMask_t const & src1 = std::get<cmdSetStencilCompareMask_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdSetStencilWriteMask_t>(src0))
    {
      cmdSetStencilWriteMask_t const & src1 = std::get<cmdSetStencilWriteMask_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdSetStencilReference_t>(src0))
    {
      cmdSetStencilReference_t const & src1 = std::get<cmdSetStencilReference_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdBindDescriptorSets_t>(src0))
    {
      cmdBindDescriptorSets_t const & src1 = std::get<cmdBindDescriptorSets_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdBindIndexBuffer_t>(src0))
    {
      cmdBindIndexBuffer_t const & src1 = std::get<cmdBindIndexBuffer_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdBindIndexBuffers_t>(src0))
    {
      cmdBindIndexBuffers_t const & src1 = std::get<cmdBindIndexBuffers_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdDraw_t>(src0))
    {
      cmdDraw_t const & src1 = std::get<cmdDraw_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdDrawIndexed_t>(src0))
    {
      cmdDrawIndexed_t const & src1 = std::get<cmdDrawIndexed_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdDrawIndirect_t>(src0))
    {
      cmdDrawIndirect_t const & src1 = std::get<cmdDrawIndirect_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdDrawIndexedIndirect_t>(src0))
    {
      cmdDrawIndexedIndirect_t const & src1 = std::get<cmdDrawIndexedIndirect_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdDispatch_t>(src0))
    {
      cmdDispatch_t const & src1 = std::get<cmdDispatch_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdDispatchIndirect_t>(src0))
    {
      cmdDispatchIndirect_t const & src1 = std::get<cmdDispatchIndirect_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdCopyBuffer_t>(src0))
    {
      cmdCopyBuffer_t const & src1 = std::get<cmdCopyBuffer_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdCopyImage_t>(src0))
    {
      cmdCopyImage_t const & src1 = std::get<cmdCopyImage_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdBlitImage_t>(src0))
    {
      cmdBlitImage_t const & src1 = std::get<cmdBlitImage_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdCopyBufferToImage_t>(src0))
    {
      cmdCopyBufferToImage_t const & src1 = std::get<cmdCopyBufferToImage_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdCopyImageToBuffer_t>(src0))
    {
      cmdCopyImageToBuffer_t const & src1 = std::get<cmdCopyImageToBuffer_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdUpdateBuffer_t>(src0))
    {
      cmdUpdateBuffer_t const & src1 = std::get<cmdUpdateBuffer_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdFillBuffer_t>(src0))
    {
      cmdFillBuffer_t const & src1 = std::get<cmdFillBuffer_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdClearColorImage_t>(src0))
    {
      cmdClearColorImage_t const & src1 = std::get<cmdClearColorImage_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdClearDepthStencilImage_t>(src0))
    {
      cmdClearDepthStencilImage_t const & src1 = std::get<cmdClearDepthStencilImage_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdClearAttachments_t>(src0))
    {
      cmdClearAttachments_t const & src1 = std::get<cmdClearAttachments_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdResolveImage_t>(src0))
    {
      cmdResolveImage_t const & src1 = std::get<cmdResolveImage_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdSetEvent_t>(src0))
    {
      cmdSetEvent_t const & src1 = std::get<cmdSetEvent_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdWaitEvents_t>(src0))
    {
      cmdWaitEvents_t const & src1 = std::get<cmdWaitEvents_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdPipelineBarrier_t>(src0))
    {
      cmdPipelineBarrier_t const & src1 = std::get<cmdPipelineBarrier_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdPushConstants_t>(src0))
    {
      cmdPushConstants_t const & src1 = std::get<cmdPushConstants_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdBeginRenderPass_t>(src0))
    {
      cmdBeginRenderPass_t const & src1 = std::get<cmdBeginRenderPass_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdNextSubpass_t>(src0))
    {
      cmdNextSubpass_t const & src1 = std::get<cmdNextSubpass_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdEndRenderPass_t>(src0))
    {
      cmdEndRenderPass_t const & src1 = std::get<cmdEndRenderPass_t>(src0);
      ss << "\n" << indentIn;
      ss << print(src1, depth + 1);
    }
    else if (std::holds_alternative<cmdExecuteCommands_t>(src0))
    {
      cmdExecuteCommands_t const & src1 = std::get<cmdExecuteCommands_t>(src0);
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

ostream & overground::commandList::operator << (ostream & stream, commandList_t const & rhs)
{
  stream << print(rhs);
  return stream;
}
