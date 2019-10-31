#include "tableau-gen.h"

using namespace overground;
using namespace overground::tableau;
using namespace humon;
using namespace std;


void overground::tableau::importPod(
  humon::HuNode const & src, matrixTransform_t & dest)
{
  if (src % "transform")
  {
    auto & src0 = src / "transform";
    std::array<float, 16> dst0;
    for (size_t i0 = 0; i0 < 16; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.transform = std::move(dst0);
  }
}

void overground::tableau::importPod(
std::vector<uint8_t> const & src, matrixTransform_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(matrixTransform_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
matrixTransform_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  matrixTransform_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "transform: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.transform.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.transform[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::tableau::operator << (ostream & stream, matrixTransform_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::tableau::importPod(
  humon::HuNode const & src, srtTransform_t & dest)
{
  if (src % "scale")
  {
    auto & src0 = src / "scale";
    std::array<float, 3> dst0;
    for (size_t i0 = 0; i0 < 3; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.scale = std::move(dst0);
  }
  if (src % "rotation")
  {
    auto & src0 = src / "rotation";
    std::array<float, 3> dst0;
    for (size_t i0 = 0; i0 < 3; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.rotation = std::move(dst0);
  }
  if (src % "translate")
  {
    auto & src0 = src / "translate";
    std::array<float, 3> dst0;
    for (size_t i0 = 0; i0 < 3; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.translate = std::move(dst0);
  }
}

void overground::tableau::importPod(
std::vector<uint8_t> const & src, srtTransform_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(srtTransform_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
srtTransform_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  srtTransform_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "scale: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.scale.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.scale[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "rotation: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.rotation.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.rotation[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "translate: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.translate.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.translate[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::tableau::operator << (ostream & stream, srtTransform_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::tableau::importPod(
  humon::HuNode const & src, drawableSubmodel_t & dest)
{
  if (src % "submesh")
  {
    auto & src0 = src / "submesh";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.submesh = std::move(dst0);
  }
  if (src % "material")
  {
    auto & src0 = src / "material";
    std::optional<std::string> dst0;
    std::string dst1;
    {
      auto & src1 = src0;
      dst1 = (std::string) src1; // leaf
    }
    dst0.emplace(std::move(dst1));
    dest.material = std::move(dst0);
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

void overground::tableau::importPod(
std::vector<uint8_t> const & src, drawableSubmodel_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(drawableSubmodel_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
drawableSubmodel_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  drawableSubmodel_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "submesh: ";
  ss << (src.submesh);
  ss << "\n" << indentIn << "material: ";

  if ((bool) src.material)
  {
    std::string const & src0 = * src.material;
    ss << (src0);
  }
  else
    { ss << "<undefined>"; }
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

ostream & overground::tableau::operator << (ostream & stream, drawableSubmodel_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::tableau::importPod(
  humon::HuNode const & src, drawableModel_t & dest)
{
  if (src % "mesh")
  {
    auto & src0 = src / "mesh";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.mesh = std::move(dst0);
  }
  if (src % "subModels")
  {
    auto & src0 = src / "subModels";
    std::vector<drawableSubmodel_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      drawableSubmodel_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.subModels = std::move(dst0);
  }
}

void overground::tableau::importPod(
std::vector<uint8_t> const & src, drawableModel_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(drawableModel_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
drawableModel_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  drawableModel_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "mesh: ";
  ss << (src.mesh);
  ss << "\n" << indentIn << "subModels: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.subModels.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    drawableSubmodel_t const & src0 = src.subModels[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::tableau::operator << (ostream & stream, drawableModel_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::tableau::importPod(
  humon::HuNode const & src, directionalLight_t & dest)
{
  if (src % "color")
  {
    auto & src0 = src / "color";
    std::array<float, 3> dst0;
    for (size_t i0 = 0; i0 < 3; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.color = std::move(dst0);
  }
}

void overground::tableau::importPod(
std::vector<uint8_t> const & src, directionalLight_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(directionalLight_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
directionalLight_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  directionalLight_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
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

ostream & overground::tableau::operator << (ostream & stream, directionalLight_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::tableau::importPod(
  humon::HuNode const & src, pointLight_t & dest)
{
  if (src % "attenuation")
  {
    auto & src0 = src / "attenuation";
    std::array<float, 3> dst0;
    for (size_t i0 = 0; i0 < 3; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.attenuation = std::move(dst0);
  }
  if (src % "color")
  {
    auto & src0 = src / "color";
    std::array<float, 3> dst0;
    for (size_t i0 = 0; i0 < 3; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.color = std::move(dst0);
  }
}

void overground::tableau::importPod(
std::vector<uint8_t> const & src, pointLight_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(pointLight_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
pointLight_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  pointLight_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "attenuation: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.attenuation.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.attenuation[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
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

ostream & overground::tableau::operator << (ostream & stream, pointLight_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::tableau::importPod(
  humon::HuNode const & src, spotLight_t & dest)
{
  if (src % "attenuation")
  {
    auto & src0 = src / "attenuation";
    std::array<float, 3> dst0;
    for (size_t i0 = 0; i0 < 3; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.attenuation = std::move(dst0);
  }
  if (src % "hotspot")
  {
    auto & src0 = src / "hotspot";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.hotspot = std::move(dst0);
  }
  if (src % "falloff")
  {
    auto & src0 = src / "falloff";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.falloff = std::move(dst0);
  }
  if (src % "color")
  {
    auto & src0 = src / "color";
    std::array<float, 3> dst0;
    for (size_t i0 = 0; i0 < 3; ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.color = std::move(dst0);
  }
}

void overground::tableau::importPod(
std::vector<uint8_t> const & src, spotLight_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(spotLight_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
spotLight_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  spotLight_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "attenuation: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.attenuation.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.attenuation[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "hotspot: ";
  ss << (src.hotspot);
  ss << "\n" << indentIn << "falloff: ";
  ss << (src.falloff);
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

ostream & overground::tableau::operator << (ostream & stream, spotLight_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::tableau::importPod(
  humon::HuNode const & src, camera_t & dest)
{
  if (src % "fovAroundYAxis")
  {
    auto & src0 = src / "fovAroundYAxis";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.fovAroundYAxis = std::move(dst0);
  }
  if (src % "minDepth")
  {
    auto & src0 = src / "minDepth";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.minDepth = std::move(dst0);
  }
  if (src % "maxDepth")
  {
    auto & src0 = src / "maxDepth";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.maxDepth = std::move(dst0);
  }
  if (src % "renderPlan")
  {
    auto & src0 = src / "renderPlan";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.renderPlan = std::move(dst0);
  }
}

void overground::tableau::importPod(
std::vector<uint8_t> const & src, camera_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(camera_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
camera_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  camera_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "fovAroundYAxis: ";
  ss << (src.fovAroundYAxis);
  ss << "\n" << indentIn << "minDepth: ";
  ss << (src.minDepth);
  ss << "\n" << indentIn << "maxDepth: ";
  ss << (src.maxDepth);
  ss << "\n" << indentIn << "renderPlan: ";
  ss << (src.renderPlan);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::tableau::operator << (ostream & stream, camera_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::tableau::importPod(
  humon::HuNode const & src, feature_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "type")
  {
    auto & src0 = src / "type";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.type = std::move(dst0);
  }
  if (src % "data")
  {
    auto & src0 = src / "data";
    std::variant<matrixTransform_t, srtTransform_t, drawableModel_t, directionalLight_t, pointLight_t, spotLight_t, camera_t> dst0;
    {
      auto & src1 = src0;
      if (src1 % "type")
      {
        std::string const & typ = src1 / "type";
        if (typ == "") { throw std::runtime_error("objects of variant type require a \"type\" key."); }
        else if (typ == "matrixTransform_t")
        {
          matrixTransform_t dst1;
      importPod(src1, dst1);
          dst0.emplace<matrixTransform_t>(std::move(dst1));
        }
        else if (typ == "srtTransform_t")
        {
          srtTransform_t dst1;
      importPod(src1, dst1);
          dst0.emplace<srtTransform_t>(std::move(dst1));
        }
        else if (typ == "drawableModel_t")
        {
          drawableModel_t dst1;
      importPod(src1, dst1);
          dst0.emplace<drawableModel_t>(std::move(dst1));
        }
        else if (typ == "directionalLight_t")
        {
          directionalLight_t dst1;
      importPod(src1, dst1);
          dst0.emplace<directionalLight_t>(std::move(dst1));
        }
        else if (typ == "pointLight_t")
        {
          pointLight_t dst1;
      importPod(src1, dst1);
          dst0.emplace<pointLight_t>(std::move(dst1));
        }
        else if (typ == "spotLight_t")
        {
          spotLight_t dst1;
      importPod(src1, dst1);
          dst0.emplace<spotLight_t>(std::move(dst1));
        }
        else if (typ == "camera_t")
        {
          camera_t dst1;
      importPod(src1, dst1);
          dst0.emplace<camera_t>(std::move(dst1));
        }

      }
      else { throw std::runtime_error("objects of variant type require a \"kind\" key."); }
    }
    dest.data = std::move(dst0);
  }
}

void overground::tableau::importPod(
std::vector<uint8_t> const & src, feature_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(feature_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
feature_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  feature_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "type: ";
  ss << (src.type);
  ss << "\n" << indentIn << "data: ";

  if (src.data.valueless_by_exception())
    { ss << "bad state\n"; }
  else if (std::holds_alternative<matrixTransform_t>(src.data))
  {
    matrixTransform_t const & src0 = std::get<matrixTransform_t>(src.data);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else if (std::holds_alternative<srtTransform_t>(src.data))
  {
    srtTransform_t const & src0 = std::get<srtTransform_t>(src.data);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else if (std::holds_alternative<drawableModel_t>(src.data))
  {
    drawableModel_t const & src0 = std::get<drawableModel_t>(src.data);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else if (std::holds_alternative<directionalLight_t>(src.data))
  {
    directionalLight_t const & src0 = std::get<directionalLight_t>(src.data);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else if (std::holds_alternative<pointLight_t>(src.data))
  {
    pointLight_t const & src0 = std::get<pointLight_t>(src.data);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else if (std::holds_alternative<spotLight_t>(src.data))
  {
    spotLight_t const & src0 = std::get<spotLight_t>(src.data);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else if (std::holds_alternative<camera_t>(src.data))
  {
    camera_t const & src0 = std::get<camera_t>(src.data);
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
  }
  else { ss << "(unknown variant)\n"; }
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::tableau::operator << (ostream & stream, feature_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::tableau::importPod(
  humon::HuNode const & src, object_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "children")
  {
    auto & src0 = src / "children";
    std::vector<object_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      object_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.children = std::move(dst0);
  }
  if (src % "features")
  {
    auto & src0 = src / "features";
    std::vector<feature_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      feature_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.features = std::move(dst0);
  }
}

void overground::tableau::importPod(
std::vector<uint8_t> const & src, object_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(object_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
object_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  object_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "children: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.children.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    object_t const & src0 = src.children[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "features: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.features.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    feature_t const & src0 = src.features[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::tableau::operator << (ostream & stream, object_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::tableau::importPod(
  humon::HuNode const & src, tableau_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "objects")
  {
    auto & src0 = src / "objects";
    std::vector<object_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      object_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.objects = std::move(dst0);
  }
}

void overground::tableau::importPod(
std::vector<uint8_t> const & src, tableau_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(tableau_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::tableau::exportPod(
tableau_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::tableau::print(
  tableau_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "objects: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.objects.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    object_t const & src0 = src.objects[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::tableau::operator << (ostream & stream, tableau_t const & rhs)
{
  stream << print(rhs);
  return stream;
}
