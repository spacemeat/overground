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
    // model things

    struct model_t
    {
      std::string name;
      std::string mesh;
      std::vector<std::optional<std::string>> materials;
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
      materials = 1 << 2,
      all = name | mesh | materials
    };

    inline bool operator == (model_t const & lhs, model_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.mesh == rhs.mesh &&
        lhs.materials == rhs.materials;
    };

    inline bool operator != (model_t const & lhs, model_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct modelDiffs_t
    {
      modelMembers_e diffs;
      std::vector<size_t> materialsDiffs;
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
      // diff member 'materials':
      {
        auto [mn, mx] = std::minmax(lhs.materials.size(), rhs.materials.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.materials[i] != rhs.materials[i])
          {
            model.diffs |= modelMembers_e::materials;
            model.materialsDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          model.materialsDiffs.push_back(i);
        }
      }

      return model.diffs != modelMembers_e::none;
    };

  }
}

#endif // #ifndef model_GEN_H
