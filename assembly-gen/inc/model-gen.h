#ifndef model_GEN_H
#define model_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  namespace model
  {
    // submodel things

    struct submodel_t
    {
      std::string name;
      std::string material;
      std::vector<string> tags;
    };

    void importPod(
      humon::HuNode const & src, submodel_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, submodel_t & dest);

    void exportPod(submodel_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      submodel_t const & src, std::vector<uint8_t> & dest);

    std::string print(submodel_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, submodel_t const & src);

    enum class submodelMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      material = 1 << 1,
      tags = 1 << 2,
      all = name | material | tags
    };

    inline bool operator == (submodel_t const & lhs, submodel_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.material == rhs.material &&
        lhs.tags == rhs.tags;
    };

    inline bool operator != (submodel_t const & lhs, submodel_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct submodelDiffs_t
    {
      submodelMembers_e diffs;
      std::vector<size_t> tagsDiffs;
    };

    inline bool doPodsDiffer(
      submodel_t const & lhs,
      submodel_t const & rhs,
      submodelDiffs_t & submodel) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { submodel.diffs |= submodelMembers_e::name; }
      // diff member 'material':
      if (lhs.material != rhs.material)
        { submodel.diffs |= submodelMembers_e::material; }
      // diff member 'tags':
      {
        auto [mn, mx] = std::minmax(lhs.tags.size(), rhs.tags.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.tags[i] != rhs.tags[i])
          {
            submodel.diffs |= submodelMembers_e::tags;
            submodel.tagsDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          submodel.tagsDiffs.push_back(i);
        }
      }

      return submodel.diffs != submodelMembers_e::none;
    };

    // model things

    struct model_t
    {
      std::string name;
      std::string mesh;
      stringDict<submodel_t> submodels;
    };

    void importPod(
      humon::HuNode const & src, model_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, model_t & dest);

    void exportPod(model_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      model_t const & src, std::vector<uint8_t> & dest);

    std::string print(model_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, model_t const & src);

    enum class modelMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      mesh = 1 << 1,
      submodels = 1 << 2,
      all = name | mesh | submodels
    };

    inline bool operator == (model_t const & lhs, model_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.mesh == rhs.mesh &&
        lhs.submodels == rhs.submodels;
    };

    inline bool operator != (model_t const & lhs, model_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct modelDiffs_t
    {
      modelMembers_e diffs;
      std::vector<std::pair<std::string, submodelDiffs_t>> submodelsDiffs;
    };

    inline bool doPodsDiffer(
      model_t const & lhs,
      model_t const & rhs,
      modelDiffs_t & model) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { model.diffs |= modelMembers_e::name; }
      // diff member 'mesh':
      if (lhs.mesh != rhs.mesh)
        { model.diffs |= modelMembers_e::mesh; }
      // diff member 'submodels':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.submodels.keys)
        {
          submodelDiffs_t diffsEntry;
          if (auto it = rhs.submodels.keys().find(lhsKey); it != rhs.submodels.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.submodels[lhsIdx], rhs.submodels[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          model.diffs |= modelMembers_e::submodels;
          model.submodelsDiffs.push_back({lhsKey, diffsEntry});
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.submodels.keys())
        {
          if (auto it = lhs.submodels.keys.find(rhsKey); it != lhs.submodels.keys.end())
            { continue; }

          submodelDiffs_t diffsEntry = { .diffs = submodelMembers_e::all };
          model.submodelsDiffs.push_back({rhsKey, diffsEntry});
        }
      }

      return model.diffs != modelMembers_e::none;
    };

  }
}

#endif // #ifndef model_GEN_H
