#include "assembly-gen.h"

using namespace overground;
using namespace overground::assembly;
using namespace humon;
using namespace std;


void overground::assembly::importPod(
  humon::HuNode const & src, assembly_t & dest)
{
  if (src % "configs")
  {
    auto & src0 = src / "configs";
    stringDict<config::config_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      config::config_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.configs = std::move(dst0);
  }
  if (src % "renderPlans")
  {
    auto & src0 = src / "renderPlans";
    stringDict<renderPlan::renderPlan_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      renderPlan::renderPlan_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.renderPlans = std::move(dst0);
  }
  if (src % "assets")
  {
    auto & src0 = src / "assets";
    stringDict<asset::asset_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      asset::asset_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.assets = std::move(dst0);
  }
  if (src % "materials")
  {
    auto & src0 = src / "materials";
    stringDict<material::material_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      material::material_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.materials = std::move(dst0);
  }
  if (src % "models")
  {
    auto & src0 = src / "models";
    stringDict<model::model_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      model::model_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.models = std::move(dst0);
  }
  if (src % "tableaux")
  {
    auto & src0 = src / "tableaux";
    stringDict<tableau::tableau_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      tableau::tableau_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.tableaux = std::move(dst0);
  }
  if (src % "tableauGroups")
  {
    auto & src0 = src / "tableauGroups";
    stringDict<std::vector<std::string>> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      std::vector<std::string> dst1;

      for (size_t i1 = 0; i1 < src1.size(); ++i1)
      {
        auto & src2 = src1 / i1;
        std::string dst2;
        dst2 = (std::string) src2; // leaf

        dst1.push_back(std::move(dst2));
      }
      dst0.push_back(key, std::move(dst1));
    }
    dest.tableauGroups = std::move(dst0);
  }
  if (src % "usingConfig")
  {
    auto & src0 = src / "usingConfig";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.usingConfig = std::move(dst0);
  }
  if (src % "usingTableauGroup")
  {
    auto & src0 = src / "usingTableauGroup";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.usingTableauGroup = std::move(dst0);
  }
}

void overground::assembly::importPod(
std::vector<uint8_t> const & src, assembly_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::assembly::exportPod(assembly_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::assembly::exportPod(
assembly_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::assembly::print(
  assembly_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "configs: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.configs.size(); ++i0)
  {
    auto const & [key, idx] = src.configs.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    config::config_t const & src0 = src.configs[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << indentIn << "renderPlans: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.renderPlans.size(); ++i0)
  {
    auto const & [key, idx] = src.renderPlans.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    renderPlan::renderPlan_t const & src0 = src.renderPlans[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << indentIn << "assets: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.assets.size(); ++i0)
  {
    auto const & [key, idx] = src.assets.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    asset::asset_t const & src0 = src.assets[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << indentIn << "materials: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.materials.size(); ++i0)
  {
    auto const & [key, idx] = src.materials.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    material::material_t const & src0 = src.materials[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << indentIn << "models: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.models.size(); ++i0)
  {
    auto const & [key, idx] = src.models.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    model::model_t const & src0 = src.models[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << indentIn << "tableaux: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.tableaux.size(); ++i0)
  {
    auto const & [key, idx] = src.tableaux.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    tableau::tableau_t const & src0 = src.tableaux[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << indentIn << "tableauGroups: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.tableauGroups.size(); ++i0)
  {
    auto const & [key, idx] = src.tableauGroups.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::vector<std::string> const & src0 = src.tableauGroups[idx];
    ss << indentIn << key << ": ";
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      std::string const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << (src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << indentIn << "usingConfig: ";
  ss << (src.usingConfig);
  ss << "\n" << indentIn << "usingTableauGroup: ";
  ss << (src.usingTableauGroup);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::assembly::operator << (ostream & stream, assembly_t const & rhs)
{
  stream << print(rhs);
  return stream;
}
