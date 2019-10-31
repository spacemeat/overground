#ifndef assembly_GEN_H
#define assembly_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"
#include "config-gen.h"
#include "renderPlan-gen.h"
#include "asset-gen.h"
#include "material-gen.h"
#include "model-gen.h"
#include "tableau-gen.h"

namespace overground
{
  namespace assembly
  {
    // assembly things

    struct assembly_t
    {
      stringDict<config::config_t> configs;
      stringDict<renderPlan::renderPlan_t> renderPlans;
      stringDict<asset::asset_t> assets;
      stringDict<material::material_t> materials;
      stringDict<model::model_t> models;
      stringDict<tableau::tableau_t> tableaux;
      stringDict<std::vector<std::string>> tableauGroups;
      std::string usingConfig;
      std::string usingTableauGroup;
    };

    void importPod(
      humon::HuNode const & src, assembly_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, assembly_t & dest);

    void exportPod(assembly_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      assembly_t const & src, std::vector<uint8_t> & dest);

    std::string print(assembly_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, assembly_t const & src);

    enum class assemblyMembers_e : int 
    {
      none = 0,
      configs = 1 << 0,
      renderPlans = 1 << 1,
      assets = 1 << 2,
      materials = 1 << 3,
      models = 1 << 4,
      tableaux = 1 << 5,
      tableauGroups = 1 << 6,
      usingConfig = 1 << 7,
      usingTableauGroup = 1 << 8,
      all = configs | renderPlans | assets | materials | models | tableaux | tableauGroups | usingConfig | usingTableauGroup
    };

    inline bool operator == (assembly_t const & lhs, assembly_t const & rhs) noexcept
    {
      return
        lhs.configs == rhs.configs &&
        lhs.renderPlans == rhs.renderPlans &&
        lhs.assets == rhs.assets &&
        lhs.materials == rhs.materials &&
        lhs.models == rhs.models &&
        lhs.tableaux == rhs.tableaux &&
        lhs.tableauGroups == rhs.tableauGroups &&
        lhs.usingConfig == rhs.usingConfig &&
        lhs.usingTableauGroup == rhs.usingTableauGroup;
    };

    inline bool operator != (assembly_t const & lhs, assembly_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct assemblyDiffs_t
    {
      assemblyMembers_e diffs;
      std::vector<std::pair<std::string, config::configDiffs_t>> configsDiffs;
      std::vector<std::pair<std::string, renderPlan::renderPlanDiffs_t>> renderPlansDiffs;
      std::vector<std::pair<std::string, asset::assetDiffs_t>> assetsDiffs;
      std::vector<std::pair<std::string, material::materialDiffs_t>> materialsDiffs;
      std::vector<std::pair<std::string, model::modelDiffs_t>> modelsDiffs;
      std::vector<std::pair<std::string, tableau::tableauDiffs_t>> tableauxDiffs;
      std::vector<std::string> tableauGroupsDiffs;
    };

    inline bool doPodsDiffer(
      assembly_t const & lhs,
      assembly_t const & rhs,
      assemblyDiffs_t & assembly) noexcept
    {
      // diff member 'configs':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.configs.keys)
        {
          config::configDiffs_t diffsEntry;
          if (auto it = rhs.configs.keys().find(lhsKey); it != rhs.configs.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.configs[lhsIdx], rhs.configs[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          assembly.diffs |= assemblyMembers_e::configs;
          assembly.configsDiffs.push_back({lhsKey, diffsEntry});
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.configs.keys())
        {
          if (auto it = lhs.configs.keys.find(rhsKey); it != lhs.configs.keys.end())
            { continue; }

          config::configDiffs_t diffsEntry = { .diffs = config::configMembers_e::all };
          assembly.configsDiffs.push_back({rhsKey, diffsEntry});
        }
      }
      // diff member 'renderPlans':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.renderPlans.keys)
        {
          renderPlan::renderPlanDiffs_t diffsEntry;
          if (auto it = rhs.renderPlans.keys().find(lhsKey); it != rhs.renderPlans.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.renderPlans[lhsIdx], rhs.renderPlans[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          assembly.diffs |= assemblyMembers_e::renderPlans;
          assembly.renderPlansDiffs.push_back({lhsKey, diffsEntry});
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.renderPlans.keys())
        {
          if (auto it = lhs.renderPlans.keys.find(rhsKey); it != lhs.renderPlans.keys.end())
            { continue; }

          renderPlan::renderPlanDiffs_t diffsEntry = { .diffs = renderPlan::renderPlanMembers_e::all };
          assembly.renderPlansDiffs.push_back({rhsKey, diffsEntry});
        }
      }
      // diff member 'assets':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.assets.keys)
        {
          asset::assetDiffs_t diffsEntry;
          if (auto it = rhs.assets.keys().find(lhsKey); it != rhs.assets.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.assets[lhsIdx], rhs.assets[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          assembly.diffs |= assemblyMembers_e::assets;
          assembly.assetsDiffs.push_back({lhsKey, diffsEntry});
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.assets.keys())
        {
          if (auto it = lhs.assets.keys.find(rhsKey); it != lhs.assets.keys.end())
            { continue; }

          asset::assetDiffs_t diffsEntry = { .diffs = asset::assetMembers_e::all };
          assembly.assetsDiffs.push_back({rhsKey, diffsEntry});
        }
      }
      // diff member 'materials':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.materials.keys)
        {
          material::materialDiffs_t diffsEntry;
          if (auto it = rhs.materials.keys().find(lhsKey); it != rhs.materials.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.materials[lhsIdx], rhs.materials[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          assembly.diffs |= assemblyMembers_e::materials;
          assembly.materialsDiffs.push_back({lhsKey, diffsEntry});
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.materials.keys())
        {
          if (auto it = lhs.materials.keys.find(rhsKey); it != lhs.materials.keys.end())
            { continue; }

          material::materialDiffs_t diffsEntry = { .diffs = material::materialMembers_e::all };
          assembly.materialsDiffs.push_back({rhsKey, diffsEntry});
        }
      }
      // diff member 'models':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.models.keys)
        {
          model::modelDiffs_t diffsEntry;
          if (auto it = rhs.models.keys().find(lhsKey); it != rhs.models.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.models[lhsIdx], rhs.models[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          assembly.diffs |= assemblyMembers_e::models;
          assembly.modelsDiffs.push_back({lhsKey, diffsEntry});
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.models.keys())
        {
          if (auto it = lhs.models.keys.find(rhsKey); it != lhs.models.keys.end())
            { continue; }

          model::modelDiffs_t diffsEntry = { .diffs = model::modelMembers_e::all };
          assembly.modelsDiffs.push_back({rhsKey, diffsEntry});
        }
      }
      // diff member 'tableaux':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.tableaux.keys)
        {
          tableau::tableauDiffs_t diffsEntry;
          if (auto it = rhs.tableaux.keys().find(lhsKey); it != rhs.tableaux.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.tableaux[lhsIdx], rhs.tableaux[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          assembly.diffs |= assemblyMembers_e::tableaux;
          assembly.tableauxDiffs.push_back({lhsKey, diffsEntry});
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.tableaux.keys())
        {
          if (auto it = lhs.tableaux.keys.find(rhsKey); it != lhs.tableaux.keys.end())
            { continue; }

          tableau::tableauDiffs_t diffsEntry = { .diffs = tableau::tableauMembers_e::all };
          assembly.tableauxDiffs.push_back({rhsKey, diffsEntry});
        }
      }
      // diff member 'tableauGroups':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.tableauGroups.keys)
        {
          if (auto it = rhs.tableauGroups.keys().find(lhsKey); it != rhs.tableauGroups.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                lhs.tableauGroups[lhsIdx] == rhs.tableauGroups[rhsIdx])
              { continue; }
          }
          assembly.diffs |= assemblyMembers_e::tableauGroups;
          assembly.tableauGroupsDiffs.push_back(lhsKey);
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.tableauGroups.keys())
        {
          if (auto it = keys.find(rhsKey); it != keys.end())
            { continue; }
          assembly.tableauGroupsDiffs.push_back(rhsKey);
        }
      }
      // diff member 'usingConfig':
      if (lhs.usingConfig != rhs.usingConfig)
        { assembly.diffs |= assemblyMembers_e::usingConfig; }
      // diff member 'usingTableauGroup':
      if (lhs.usingTableauGroup != rhs.usingTableauGroup)
        { assembly.diffs |= assemblyMembers_e::usingTableauGroup; }

      return assembly.diffs != assemblyMembers_e::none;
    };

  }
}

#endif // #ifndef assembly_GEN_H
