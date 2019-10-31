#include "material-gen.h"

using namespace overground;
using namespace overground::material;
using namespace humon;
using namespace std;


void overground::material::importPod(
  humon::HuNode const & src, shaderModule_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "shaderName")
  {
    auto & src0 = src / "shaderName";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.shaderName = std::move(dst0);
  }
}

void overground::material::importPod(
std::vector<uint8_t> const & src, shaderModule_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(shaderModule_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
shaderModule_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  shaderModule_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "shaderName: ";
  ss << (src.shaderName);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, shaderModule_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::material::importPod(
  humon::HuNode const & src, vertexDeclEntry_t & dest)
{
  if (src % "offset")
  {
    auto & src0 = src / "offset";
    int dst0;
    dst0 = (int) src0; // leaf
    dest.offset = std::move(dst0);
  }
  if (src % "format")
  {
    auto & src0 = src / "format";
    vk::Format dst0;
    dst0 = fromString<vk::Format>((std::string) src0); // leaf
    dest.format = std::move(dst0);
  }
}

void overground::material::importPod(
std::vector<uint8_t> const & src, vertexDeclEntry_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(vertexDeclEntry_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
vertexDeclEntry_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  vertexDeclEntry_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "offset: ";
  ss << (src.offset);
  ss << "\n" << indentIn << "format: ";
  ss << to_string(src.format);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, vertexDeclEntry_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::material::importPod(
  humon::HuNode const & src, stage_t & dest)
{
  if (src % "stage")
  {
    auto & src0 = src / "stage";
    vk::ShaderStage dst0;
    dst0 = fromString<vk::ShaderStage>((std::string) src0); // leaf
    dest.stage = std::move(dst0);
  }
  if (src % "module")
  {
    auto & src0 = src / "module";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.module = std::move(dst0);
  }
  if (src % "entry")
  {
    auto & src0 = src / "entry";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.entry = std::move(dst0);
  }
}

void overground::material::importPod(
std::vector<uint8_t> const & src, stage_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(stage_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
stage_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  stage_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "stage: ";
  ss << to_string(src.stage);
  ss << "\n" << indentIn << "module: ";
  ss << (src.module);
  ss << "\n" << indentIn << "entry: ";
  ss << (src.entry);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, stage_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::material::importPod(
  humon::HuNode const & src, rasterizationState_t & dest)
{
  if (src % "depthClampEnable")
  {
    auto & src0 = src / "depthClampEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.depthClampEnable = std::move(dst0);
  }
  if (src % "rasterizerDiscardEnable")
  {
    auto & src0 = src / "rasterizerDiscardEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.rasterizerDiscardEnable = std::move(dst0);
  }
  if (src % "polygonFillMode")
  {
    auto & src0 = src / "polygonFillMode";
    vk::FillMode dst0;
    dst0 = fromString<vk::FillMode>((std::string) src0); // leaf
    dest.polygonFillMode = std::move(dst0);
  }
  if (src % "cullMode")
  {
    auto & src0 = src / "cullMode";
    vk::CullMode dst0;
    dst0 = fromString<vk::CullMode>((std::string) src0); // leaf
    dest.cullMode = std::move(dst0);
  }
  if (src % "frontFace")
  {
    auto & src0 = src / "frontFace";
    vk::FaceOrientation dst0;
    dst0 = fromString<vk::FaceOrientation>((std::string) src0); // leaf
    dest.frontFace = std::move(dst0);
  }
  if (src % "depthBiasEnable")
  {
    auto & src0 = src / "depthBiasEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.depthBiasEnable = std::move(dst0);
  }
  if (src % "lineWidth")
  {
    auto & src0 = src / "lineWidth";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.lineWidth = std::move(dst0);
  }
}

void overground::material::importPod(
std::vector<uint8_t> const & src, rasterizationState_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(rasterizationState_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
rasterizationState_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  rasterizationState_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "depthClampEnable: ";
  ss << (src.depthClampEnable);
  ss << "\n" << indentIn << "rasterizerDiscardEnable: ";
  ss << (src.rasterizerDiscardEnable);
  ss << "\n" << indentIn << "polygonFillMode: ";
  ss << to_string(src.polygonFillMode);
  ss << "\n" << indentIn << "cullMode: ";
  ss << to_string(src.cullMode);
  ss << "\n" << indentIn << "frontFace: ";
  ss << to_string(src.frontFace);
  ss << "\n" << indentIn << "depthBiasEnable: ";
  ss << (src.depthBiasEnable);
  ss << "\n" << indentIn << "lineWidth: ";
  ss << (src.lineWidth);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, rasterizationState_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::material::importPod(
  humon::HuNode const & src, multisampleState_t & dest)
{
  if (src % "rasterizationSamples")
  {
    auto & src0 = src / "rasterizationSamples";
    int dst0;
    dst0 = (int) src0; // leaf
    dest.rasterizationSamples = std::move(dst0);
  }
  if (src % "sampleShadingEnable")
  {
    auto & src0 = src / "sampleShadingEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.sampleShadingEnable = std::move(dst0);
  }
  if (src % "sampleMask")
  {
    auto & src0 = src / "sampleMask";
    vk::SampleMask dst0;
    dst0 = fromString<vk::SampleMask>((std::string) src0); // leaf
    dest.sampleMask = std::move(dst0);
  }
  if (src % "alphaToCoverageEnable")
  {
    auto & src0 = src / "alphaToCoverageEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.alphaToCoverageEnable = std::move(dst0);
  }
  if (src % "alphaToOneEnable")
  {
    auto & src0 = src / "alphaToOneEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.alphaToOneEnable = std::move(dst0);
  }
}

void overground::material::importPod(
std::vector<uint8_t> const & src, multisampleState_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(multisampleState_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
multisampleState_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  multisampleState_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "rasterizationSamples: ";
  ss << (src.rasterizationSamples);
  ss << "\n" << indentIn << "sampleShadingEnable: ";
  ss << (src.sampleShadingEnable);
  ss << "\n" << indentIn << "sampleMask: ";
  ss << to_string(src.sampleMask);
  ss << "\n" << indentIn << "alphaToCoverageEnable: ";
  ss << (src.alphaToCoverageEnable);
  ss << "\n" << indentIn << "alphaToOneEnable: ";
  ss << (src.alphaToOneEnable);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, multisampleState_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::material::importPod(
  humon::HuNode const & src, blendStateAttachment_t & dest)
{
  if (src % "srcColorFactor")
  {
    auto & src0 = src / "srcColorFactor";
    vk::BlendFactor dst0;
    dst0 = fromString<vk::BlendFactor>((std::string) src0); // leaf
    dest.srcColorFactor = std::move(dst0);
  }
  if (src % "dstColorFactor")
  {
    auto & src0 = src / "dstColorFactor";
    vk::BlendFactor dst0;
    dst0 = fromString<vk::BlendFactor>((std::string) src0); // leaf
    dest.dstColorFactor = std::move(dst0);
  }
  if (src % "colorOp")
  {
    auto & src0 = src / "colorOp";
    vk::BlendOp dst0;
    dst0 = fromString<vk::BlendOp>((std::string) src0); // leaf
    dest.colorOp = std::move(dst0);
  }
  if (src % "srcAlphaFactor")
  {
    auto & src0 = src / "srcAlphaFactor";
    vk::BlendFactor dst0;
    dst0 = fromString<vk::BlendFactor>((std::string) src0); // leaf
    dest.srcAlphaFactor = std::move(dst0);
  }
  if (src % "dstAlphaFactor")
  {
    auto & src0 = src / "dstAlphaFactor";
    vk::BlendFactor dst0;
    dst0 = fromString<vk::BlendFactor>((std::string) src0); // leaf
    dest.dstAlphaFactor = std::move(dst0);
  }
  if (src % "alphaOp")
  {
    auto & src0 = src / "alphaOp";
    vk::BlendOp dst0;
    dst0 = fromString<vk::BlendOp>((std::string) src0); // leaf
    dest.alphaOp = std::move(dst0);
  }
  if (src % "colorWriteMask")
  {
    auto & src0 = src / "colorWriteMask";
    std::vector<char> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      char dst1;
      dst1 = (char) src1; // leaf

      dst0.push_back(std::move(dst1));
    }
    dest.colorWriteMask = std::move(dst0);
  }
}

void overground::material::importPod(
std::vector<uint8_t> const & src, blendStateAttachment_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(blendStateAttachment_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
blendStateAttachment_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  blendStateAttachment_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "srcColorFactor: ";
  ss << to_string(src.srcColorFactor);
  ss << "\n" << indentIn << "dstColorFactor: ";
  ss << to_string(src.dstColorFactor);
  ss << "\n" << indentIn << "colorOp: ";
  ss << to_string(src.colorOp);
  ss << "\n" << indentIn << "srcAlphaFactor: ";
  ss << to_string(src.srcAlphaFactor);
  ss << "\n" << indentIn << "dstAlphaFactor: ";
  ss << to_string(src.dstAlphaFactor);
  ss << "\n" << indentIn << "alphaOp: ";
  ss << to_string(src.alphaOp);
  ss << "\n" << indentIn << "colorWriteMask: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.colorWriteMask.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    char const & src0 = src.colorWriteMask[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, blendStateAttachment_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::material::importPod(
  humon::HuNode const & src, blendState_t & dest)
{
  if (src % "logicOpEnable")
  {
    auto & src0 = src / "logicOpEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.logicOpEnable = std::move(dst0);
  }
  if (src % "attachments")
  {
    auto & src0 = src / "attachments";
    std::vector<blendStateAttachment_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      blendStateAttachment_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.attachments = std::move(dst0);
  }
}

void overground::material::importPod(
std::vector<uint8_t> const & src, blendState_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(blendState_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
blendState_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  blendState_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "logicOpEnable: ";
  ss << (src.logicOpEnable);
  ss << "\n" << indentIn << "attachments: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.attachments.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    blendStateAttachment_t const & src0 = src.attachments[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, blendState_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::material::importPod(
  humon::HuNode const & src, tesselationState_t & dest)
{
}

void overground::material::importPod(
std::vector<uint8_t> const & src, tesselationState_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(tesselationState_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
tesselationState_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  tesselationState_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, tesselationState_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::material::importPod(
  humon::HuNode const & src, stencilOp_t & dest)
{
  if (src % "failOp")
  {
    auto & src0 = src / "failOp";
    vk::DepthStencilFailOp dst0;
    dst0 = fromString<vk::DepthStencilFailOp>((std::string) src0); // leaf
    dest.failOp = std::move(dst0);
  }
  if (src % "passOp")
  {
    auto & src0 = src / "passOp";
    vk::DepthStencilPassOp dst0;
    dst0 = fromString<vk::DepthStencilPassOp>((std::string) src0); // leaf
    dest.passOp = std::move(dst0);
  }
  if (src % "depthFailOp")
  {
    auto & src0 = src / "depthFailOp";
    vk::DepthStencilPassOp dst0;
    dst0 = fromString<vk::DepthStencilPassOp>((std::string) src0); // leaf
    dest.depthFailOp = std::move(dst0);
  }
  if (src % "compareOp")
  {
    auto & src0 = src / "compareOp";
    vk::DepthStencilPassOp dst0;
    dst0 = fromString<vk::DepthStencilPassOp>((std::string) src0); // leaf
    dest.compareOp = std::move(dst0);
  }
  if (src % "compareMask")
  {
    auto & src0 = src / "compareMask";
    vk::SomeKindOfMask dst0;
    dst0 = fromString<vk::SomeKindOfMask>((std::string) src0); // leaf
    dest.compareMask = std::move(dst0);
  }
  if (src % "writeMask")
  {
    auto & src0 = src / "writeMask";
    vk::SomeKindOfMask dst0;
    dst0 = fromString<vk::SomeKindOfMask>((std::string) src0); // leaf
    dest.writeMask = std::move(dst0);
  }
  if (src % "reference")
  {
    auto & src0 = src / "reference";
    int dst0;
    dst0 = (int) src0; // leaf
    dest.reference = std::move(dst0);
  }
}

void overground::material::importPod(
std::vector<uint8_t> const & src, stencilOp_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(stencilOp_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
stencilOp_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  stencilOp_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "failOp: ";
  ss << to_string(src.failOp);
  ss << "\n" << indentIn << "passOp: ";
  ss << to_string(src.passOp);
  ss << "\n" << indentIn << "depthFailOp: ";
  ss << to_string(src.depthFailOp);
  ss << "\n" << indentIn << "compareOp: ";
  ss << to_string(src.compareOp);
  ss << "\n" << indentIn << "compareMask: ";
  ss << to_string(src.compareMask);
  ss << "\n" << indentIn << "writeMask: ";
  ss << to_string(src.writeMask);
  ss << "\n" << indentIn << "reference: ";
  ss << (src.reference);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, stencilOp_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::material::importPod(
  humon::HuNode const & src, depthStencilState_t & dest)
{
  if (src % "depthTestEnable")
  {
    auto & src0 = src / "depthTestEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.depthTestEnable = std::move(dst0);
  }
  if (src % "depthWriteEnable")
  {
    auto & src0 = src / "depthWriteEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.depthWriteEnable = std::move(dst0);
  }
  if (src % "depthCompareOp")
  {
    auto & src0 = src / "depthCompareOp";
    vk::DepthCompareOp dst0;
    dst0 = fromString<vk::DepthCompareOp>((std::string) src0); // leaf
    dest.depthCompareOp = std::move(dst0);
  }
  if (src % "depthBoundsTestEnable")
  {
    auto & src0 = src / "depthBoundsTestEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.depthBoundsTestEnable = std::move(dst0);
  }
  if (src % "stencilTestEnable")
  {
    auto & src0 = src / "stencilTestEnable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.stencilTestEnable = std::move(dst0);
  }
  if (src % "frontStencioOpo")
  {
    auto & src0 = src / "frontStencioOpo";
    stencilOp_t dst0;
    importPod(src0, dst0);
    dest.frontStencioOpo = std::move(dst0);
  }
  if (src % "backStencioOpo")
  {
    auto & src0 = src / "backStencioOpo";
    stencilOp_t dst0;
    importPod(src0, dst0);
    dest.backStencioOpo = std::move(dst0);
  }
  if (src % "minDepthBounds")
  {
    auto & src0 = src / "minDepthBounds";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.minDepthBounds = std::move(dst0);
  }
  if (src % "maxDepthBounds")
  {
    auto & src0 = src / "maxDepthBounds";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.maxDepthBounds = std::move(dst0);
  }
}

void overground::material::importPod(
std::vector<uint8_t> const & src, depthStencilState_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(depthStencilState_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
depthStencilState_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  depthStencilState_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "depthTestEnable: ";
  ss << (src.depthTestEnable);
  ss << "\n" << indentIn << "depthWriteEnable: ";
  ss << (src.depthWriteEnable);
  ss << "\n" << indentIn << "depthCompareOp: ";
  ss << to_string(src.depthCompareOp);
  ss << "\n" << indentIn << "depthBoundsTestEnable: ";
  ss << (src.depthBoundsTestEnable);
  ss << "\n" << indentIn << "stencilTestEnable: ";
  ss << (src.stencilTestEnable);
  ss << "\n" << indentIn << "frontStencioOpo: ";
  ss << print(src.frontStencioOpo, depth + 1);
  ss << "\n" << indentIn << "backStencioOpo: ";
  ss << print(src.backStencioOpo, depth + 1);
  ss << "\n" << indentIn << "minDepthBounds: ";
  ss << (src.minDepthBounds);
  ss << "\n" << indentIn << "maxDepthBounds: ";
  ss << (src.maxDepthBounds);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, depthStencilState_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::material::importPod(
  humon::HuNode const & src, material_t & dest)
{
  if (src % "vertexDecl")
  {
    auto & src0 = src / "vertexDecl";
    std::vector<vertexDeclEntry_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      vertexDeclEntry_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.vertexDecl = std::move(dst0);
  }
  if (src % "stages")
  {
    auto & src0 = src / "stages";
    std::vector<stage_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      stage_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.stages = std::move(dst0);
  }
  if (src % "rasterizationState")
  {
    auto & src0 = src / "rasterizationState";
    rasterizationState_t dst0;
    importPod(src0, dst0);
    dest.rasterizationState = std::move(dst0);
  }
  if (src % "multisampleState")
  {
    auto & src0 = src / "multisampleState";
    multisampleState_t dst0;
    importPod(src0, dst0);
    dest.multisampleState = std::move(dst0);
  }
  if (src % "blendState")
  {
    auto & src0 = src / "blendState";
    blendState_t dst0;
    importPod(src0, dst0);
    dest.blendState = std::move(dst0);
  }
  if (src % "tesselationState")
  {
    auto & src0 = src / "tesselationState";
    tesselationState_t dst0;
    importPod(src0, dst0);
    dest.tesselationState = std::move(dst0);
  }
  if (src % "depthStencilState")
  {
    auto & src0 = src / "depthStencilState";
    depthStencilState_t dst0;
    importPod(src0, dst0);
    dest.depthStencilState = std::move(dst0);
  }
  if (src % "dynamicStates")
  {
    auto & src0 = src / "dynamicStates";
    std::vector<vk::DynamicStateFlagBits> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      vk::DynamicStateFlagBits dst1;
      dst1 = fromString<vk::DynamicStateFlagBits>((std::string) src1); // leaf

      dst0.push_back(std::move(dst1));
    }
    dest.dynamicStates = std::move(dst0);
  }
}

void overground::material::importPod(
std::vector<uint8_t> const & src, material_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(material_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::material::exportPod(
material_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::material::print(
  material_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "vertexDecl: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.vertexDecl.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    vertexDeclEntry_t const & src0 = src.vertexDecl[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "stages: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.stages.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    stage_t const & src0 = src.stages[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "rasterizationState: ";
  ss << print(src.rasterizationState, depth + 1);
  ss << "\n" << indentIn << "multisampleState: ";
  ss << print(src.multisampleState, depth + 1);
  ss << "\n" << indentIn << "blendState: ";
  ss << print(src.blendState, depth + 1);
  ss << "\n" << indentIn << "tesselationState: ";
  ss << print(src.tesselationState, depth + 1);
  ss << "\n" << indentIn << "depthStencilState: ";
  ss << print(src.depthStencilState, depth + 1);
  ss << "\n" << indentIn << "dynamicStates: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.dynamicStates.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    vk::DynamicStateFlagBits const & src0 = src.dynamicStates[i0];
    ss << "\n" << indentIn;
    ss << to_string(src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::material::operator << (ostream & stream, material_t const & rhs)
{
  stream << print(rhs);
  return stream;
}
