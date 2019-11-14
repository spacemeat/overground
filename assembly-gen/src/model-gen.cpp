#include "model-gen.h"

using namespace overground;
using namespace overground::model;
using namespace humon;
using namespace std;


void overground::model::importPod(
  humon::HuNode const & src, submodel_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "material")
  {
    auto & src0 = src / "material";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.material = std::move(dst0);
  }
  if (src % "tags")
  {
    auto & src0 = src / "tags";
    std::vector<string> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      string dst1;
      dst1 = (string) src1; // leaf

      dst0.push_back(std::move(dst1));
    }
    dest.tags = std::move(dst0);
  }
}

void overground::model::importPod(
std::vector<uint8_t> const & src, submodel_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::model::exportPod(submodel_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::model::exportPod(
submodel_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::model::print(
  submodel_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "material: ";
  ss << (src.material);
  ss << "\n" << indentIn << "tags: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.tags.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    string const & src0 = src.tags[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::model::operator << (ostream & stream, submodel_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

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
  if (src % "submodels")
  {
    auto & src0 = src / "submodels";
    stringDict<submodel_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      submodel_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.submodels = std::move(dst0);
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
  ss << "\n" << indentIn << "submodels: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.submodels.size(); ++i0)
  {
    auto const & [key, idx] = src.submodels.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    submodel_t const & src0 = src.submodels[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::model::operator << (ostream & stream, model_t const & rhs)
{
  stream << print(rhs);
  return stream;
}
