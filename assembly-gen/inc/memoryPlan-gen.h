#ifndef memoryPlan_GEN_H
#define memoryPlan_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  namespace memoryPlan
  {
    // memoryType things

    struct memoryType_t
    {
      std::vector<vk::MemoryPropertyFlagBits> memoryProps;
      size_t allocChunkSize;
      bool mappable;
    };

    void importPod(
      humon::HuNode const & src, memoryType_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, memoryType_t & dest);

    void exportPod(memoryType_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      memoryType_t const & src, std::vector<uint8_t> & dest);

    std::string print(memoryType_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, memoryType_t const & src);

    enum class memoryTypeMembers_e : int 
    {
      none = 0,
      memoryProps = 1 << 0,
      allocChunkSize = 1 << 1,
      mappable = 1 << 2,
      all = memoryProps | allocChunkSize | mappable
    };

    inline bool operator == (memoryType_t const & lhs, memoryType_t const & rhs) noexcept
    {
      return
        lhs.memoryProps == rhs.memoryProps &&
        lhs.allocChunkSize == rhs.allocChunkSize &&
        lhs.mappable == rhs.mappable;
    };

    inline bool operator != (memoryType_t const & lhs, memoryType_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct memoryTypeDiffs_t
    {
      memoryTypeMembers_e diffs;
      std::vector<size_t> memoryPropsDiffs;
    };

    inline bool doPodsDiffer(
      memoryType_t const & lhs,
      memoryType_t const & rhs,
      memoryTypeDiffs_t & memoryType) noexcept
    {
      // diff member 'memoryProps':
      {
        auto [mn, mx] = std::minmax(lhs.memoryProps.size(), rhs.memoryProps.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.memoryProps[i] != rhs.memoryProps[i])
          {
            memoryType.diffs |= memoryTypeMembers_e::memoryProps;
            memoryType.memoryPropsDiffs.push_back(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          memoryType.memoryPropsDiffs.push_back(i);
        }
      }
      // diff member 'allocChunkSize':
      if (lhs.allocChunkSize != rhs.allocChunkSize)
        { memoryType.diffs |= memoryTypeMembers_e::allocChunkSize; }
      // diff member 'mappable':
      if (lhs.mappable != rhs.mappable)
        { memoryType.diffs |= memoryTypeMembers_e::mappable; }

      return memoryType.diffs != memoryTypeMembers_e::none;
    };

    // memoryAlloc things

    struct memoryAlloc_t
    {
      std::string name;
      std::vector<memoryType_t> types;
    };

    void importPod(
      humon::HuNode const & src, memoryAlloc_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, memoryAlloc_t & dest);

    void exportPod(memoryAlloc_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      memoryAlloc_t const & src, std::vector<uint8_t> & dest);

    std::string print(memoryAlloc_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, memoryAlloc_t const & src);

    enum class memoryAllocMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      types = 1 << 1,
      all = name | types
    };

    inline bool operator == (memoryAlloc_t const & lhs, memoryAlloc_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.types == rhs.types;
    };

    inline bool operator != (memoryAlloc_t const & lhs, memoryAlloc_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct memoryAllocDiffs_t
    {
      memoryAllocMembers_e diffs;
      std::vector<std::pair<size_t, memoryTypeDiffs_t>> typesDiffs;
    };

    inline bool doPodsDiffer(
      memoryAlloc_t const & lhs,
      memoryAlloc_t const & rhs,
      memoryAllocDiffs_t & memoryAlloc) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { memoryAlloc.diffs |= memoryAllocMembers_e::name; }
      // diff member 'types':
      {
        auto [mn, mx] = std::minmax(lhs.types.size(), rhs.types.size());
        for (size_t i = 0; i < mn; ++i)
        {
          memoryTypeDiffs_t diffsEntry;
          if (doPodsDiffer(lhs.types[i], rhs.types[i], diffsEntry))
          {
            memoryAlloc.diffs |= memoryAllocMembers_e::types;
            memoryAlloc.typesDiffs.push_back({i, diffsEntry});
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          memoryTypeDiffs_t diffsEntry = { .diffs = memoryTypeMembers_e::all };
          memoryAlloc.typesDiffs.push_back({i, diffsEntry});
        }
      }

      return memoryAlloc.diffs != memoryAllocMembers_e::none;
    };

    // memoryPlan things

    struct memoryPlan_t
    {
      stringDict<memoryAlloc_t> allocs;
    };

    void importPod(
      humon::HuNode const & src, memoryPlan_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, memoryPlan_t & dest);

    void exportPod(memoryPlan_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      memoryPlan_t const & src, std::vector<uint8_t> & dest);

    std::string print(memoryPlan_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, memoryPlan_t const & src);

    enum class memoryPlanMembers_e : int 
    {
      none = 0,
      allocs = 1 << 0,
      all = allocs
    };

    inline bool operator == (memoryPlan_t const & lhs, memoryPlan_t const & rhs) noexcept
    {
      return
        lhs.allocs == rhs.allocs;
    };

    inline bool operator != (memoryPlan_t const & lhs, memoryPlan_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct memoryPlanDiffs_t
    {
      memoryPlanMembers_e diffs;
      std::vector<std::pair<std::string, memoryAllocDiffs_t>> allocsDiffs;
    };

    inline bool doPodsDiffer(
      memoryPlan_t const & lhs,
      memoryPlan_t const & rhs,
      memoryPlanDiffs_t & memoryPlan) noexcept
    {
      // diff member 'allocs':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.allocs.keys)
        {
          memoryAllocDiffs_t diffsEntry;
          if (auto it = rhs.allocs.keys().find(lhsKey); it != rhs.allocs.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.allocs[lhsIdx], rhs.allocs[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          memoryPlan.diffs |= memoryPlanMembers_e::allocs;
          memoryPlan.allocsDiffs.push_back({lhsKey, diffsEntry});
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.allocs.keys())
        {
          if (auto it = lhs.allocs.keys.find(rhsKey); it != lhs.allocs.keys.end())
            { continue; }

          memoryAllocDiffs_t diffsEntry = { .diffs = memoryAllocMembers_e::all };
          memoryPlan.allocsDiffs.push_back({rhsKey, diffsEntry});
        }
      }

      return memoryPlan.diffs != memoryPlanMembers_e::none;
    };

  }
}

#endif // #ifndef memoryPlan_GEN_H
