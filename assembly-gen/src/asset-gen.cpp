#include "asset-gen.h"

using namespace overground;
using namespace overground::asset;
using namespace humon;
using namespace std;


void overground::asset::importPod(
  humon::HuNode const & src, meshAsset_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
}

void overground::asset::importPod(
std::vector<uint8_t> const & src, meshAsset_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(meshAsset_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(
meshAsset_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::asset::print(
  meshAsset_t const & src, int depth)
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

ostream & overground::asset::operator << (ostream & stream, meshAsset_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::asset::importPod(
  humon::HuNode const & src, imageAsset_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "format")
  {
    auto & src0 = src / "format";
    vk::Format dst0;
    dst0 = fromString<vk::Format>((std::string) src0); // leaf
    dest.format = std::move(dst0);
  }
  if (src % "compression")
  {
    auto & src0 = src / "compression";
    std::optional<string> dst0;
    string dst1;
    {
      auto & src1 = src0;
      dst1 = (string) src1; // leaf
    }
    dst0.emplace(std::move(dst1));
    dest.compression = std::move(dst0);
  }
}

void overground::asset::importPod(
std::vector<uint8_t> const & src, imageAsset_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(imageAsset_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(
imageAsset_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::asset::print(
  imageAsset_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "format: ";
  ss << to_string(src.format);
  ss << "\n" << indentIn << "compression: ";

  if ((bool) src.compression)
  {
    string const & src0 = * src.compression;
    ss << (src0);
  }
  else
    { ss << "<undefined>"; }
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::asset::operator << (ostream & stream, imageAsset_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::asset::importPod(
  humon::HuNode const & src, shaderAsset_t & dest)
{
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "entryPoint")
  {
    auto & src0 = src / "entryPoint";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.entryPoint = std::move(dst0);
  }
}

void overground::asset::importPod(
std::vector<uint8_t> const & src, shaderAsset_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(shaderAsset_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(
shaderAsset_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::asset::print(
  shaderAsset_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "entryPoint: ";
  ss << (src.entryPoint);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::asset::operator << (ostream & stream, shaderAsset_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::asset::importPod(
  humon::HuNode const & src, asset_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "srcFile")
  {
    auto & src0 = src / "srcFile";
    std::optional<string> dst0;
    string dst1;
    {
      auto & src1 = src0;
      dst1 = (string) src1; // leaf
    }
    dst0.emplace(std::move(dst1));
    dest.srcFile = std::move(dst0);
  }
  if (src % "assFile")
  {
    auto & src0 = src / "assFile";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.assFile = std::move(dst0);
  }
  if (src % "monitorFile")
  {
    auto & src0 = src / "monitorFile";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.monitorFile = std::move(dst0);
  }
  if (src % "data")
  {
    auto & src0 = src / "data";
    std::variant<meshAsset_t, imageAsset_t, shaderAsset_t> dst0;
    {
      auto & src1 = src0;
      if (src1 % "type")
      {
        std::string const & typ = src1 / "type";
        if (typ == "") { throw std::runtime_error("objects of variant type require a \"type\" key."); }
        else if (typ == "meshAsset_t")
        {
          meshAsset_t dst1;
      importPod(src1, dst1);
          dst0.emplace<meshAsset_t>(std::move(dst1));
        }
        else if (typ == "imageAsset_t")
        {
          imageAsset_t dst1;
      importPod(src1, dst1);
          dst0.emplace<imageAsset_t>(std::move(dst1));
        }
        else if (typ == "shaderAsset_t")
        {
          shaderAsset_t dst1;
      importPod(src1, dst1);
          dst0.emplace<shaderAsset_t>(std::move(dst1));
        }

      }
      else { throw std::runtime_error("objects of variant type require a \"kind\" key."); }
    }
    dest.data = std::move(dst0);
  }
}

void overground::asset::importPod(
std::vector<uint8_t> const & src, asset_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(asset_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(
asset_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::asset::print(
  asset_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "srcFile: ";

  if ((bool) src.srcFile)
  {
    string const & src0 = * src.srcFile;
    ss << (src0);
  }
  else
    { ss << "<undefined>"; }
  ss << "\n" << indentIn << "assFile: ";
  ss << (src.assFile);
  ss << "\n" << indentIn << "monitorFile: ";
  ss << (src.monitorFile);
  ss << "\n" << indentIn << "data: ";

  if (src.data.valueless_by_exception())
    { ss << "bad state\n"; }
  else if (std::holds_alternative<meshAsset_t>(src.data))
  {
    meshAsset_t const & src0 = std::get<meshAsset_t>(src.data);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else if (std::holds_alternative<imageAsset_t>(src.data))
  {
    imageAsset_t const & src0 = std::get<imageAsset_t>(src.data);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else if (std::holds_alternative<shaderAsset_t>(src.data))
  {
    shaderAsset_t const & src0 = std::get<shaderAsset_t>(src.data);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else { ss << "(unknown variant)\n"; }
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::asset::operator << (ostream & stream, asset_t const & rhs)
{
  stream << print(rhs);
  return stream;
}
