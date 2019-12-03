#include "asset-gen.h"

using namespace overground;
using namespace overground::asset;
using namespace humon;
using namespace std;


void overground::asset::importPod(
  humon::HuNode const & src, mesh_t & dest)
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
std::vector<uint8_t> const & src, mesh_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(mesh_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(
mesh_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::asset::print(
  mesh_t const & src, int depth)
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

ostream & overground::asset::operator << (ostream & stream, mesh_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::asset::importPod(
  humon::HuNode const & src, image_t & dest)
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
}

void overground::asset::importPod(
std::vector<uint8_t> const & src, image_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(image_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(
image_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::asset::print(
  image_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "format: ";
  ss << to_string(src.format);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::asset::operator << (ostream & stream, image_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::asset::importPod(
  humon::HuNode const & src, shader_t & dest)
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
std::vector<uint8_t> const & src, shader_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(shader_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::asset::exportPod(
shader_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::asset::print(
  shader_t const & src, int depth)
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

ostream & overground::asset::operator << (ostream & stream, shader_t const & rhs)
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
    std::optional<std::string> dst0;
    std::string dst1;
    {
      auto & src1 = src0;
      dst1 = (std::string) src1; // leaf
    }
    dst0.emplace(std::move(dst1));
    dest.srcFile = std::move(dst0);
  }
  if (src % "monitorFile")
  {
    auto & src0 = src / "monitorFile";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.monitorFile = std::move(dst0);
  }
  if (src % "importData")
  {
    auto & src0 = src / "importData";
    std::variant<mesh_t, image_t, shader_t> dst0;
    {
      auto & src1 = src0;
      if (src1 % "type")
      {
        std::string const & typ = src1 / "type";
        if (typ == "") { throw std::runtime_error("objects of variant type require a \"type\" key."); }
        else if (typ == "mesh")
        {
          mesh_t dst1;
          importPod(src1, dst1);
          dst0.emplace<mesh_t>(std::move(dst1));
        }
        else if (typ == "image")
        {
          image_t dst1;
          importPod(src1, dst1);
          dst0.emplace<image_t>(std::move(dst1));
        }
        else if (typ == "shader")
        {
          shader_t dst1;
          importPod(src1, dst1);
          dst0.emplace<shader_t>(std::move(dst1));
        }

      }
      else { throw std::runtime_error("objects of variant type require a \"kind\" key."); }
    }
    dest.importData = std::move(dst0);
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
    std::string const & src0 = * src.srcFile;
    ss << (src0);
  }
  else
    { ss << "<undefined>"; }
  ss << "\n" << indentIn << "monitorFile: ";
  ss << (src.monitorFile);
  ss << "\n" << indentIn << "importData: ";

  if (src.importData.valueless_by_exception())
    { ss << "bad state\n"; }
  else if (std::holds_alternative<mesh_t>(src.importData))
  {
    mesh_t const & src0 = std::get<mesh_t>(src.importData);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else if (std::holds_alternative<image_t>(src.importData))
  {
    image_t const & src0 = std::get<image_t>(src.importData);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else if (std::holds_alternative<shader_t>(src.importData))
  {
    shader_t const & src0 = std::get<shader_t>(src.importData);
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
