#include "model-gen.h"

using namespace overground;
using namespace overground::model;
using namespace humon;
using namespace std;


void overground::model::importPod(
  humon::HuNode const & src, model_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "mesh")
  {
    auto & src0 = src / "mesh";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.mesh = std::move(dst0);
  }
  if (src % "materials")
  {
    auto & src0 = src / "materials";
    std::vector<std::optional<std::string>> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::optional<std::string> dst1;
      std::string dst2;
      {
        auto & src2 = src1;
        dst2 = (std::string) src2; // leaf
      }
      dst1.emplace(std::move(dst2));

      dst0.push_back(std::move(dst1));
    }
    dest.materials = std::move(dst0);
  }
}

void overground::model::importPod(
std::vector<uint8_t> const & src, model_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::model::exportPod(model_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::model::exportPod(
model_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::model::print(
  model_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "mesh: ";
  ss << (src.mesh);
  ss << "\n" << indentIn << "materials: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.materials.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::optional<std::string> const & src0 = src.materials[i0];

    if ((bool) src0)
    {
      std::string const & src1 = * src0;
      ss << (src1);
    }
    else
      { ss << "<undefined>"; }
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::model::operator << (ostream & stream, model_t const & rhs)
{
  stream << print(rhs);
  return stream;
}
