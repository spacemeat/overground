#ifndef memoryPlan_GEN_H
#define memoryPlan_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <unordered_set>
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
      size_t chunkSize;
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
      chunkSize = 1 << 1,
      mappable = 1 << 2,
      all = memoryProps | chunkSize | mappable
    };

    inline bool operator == (memoryType_t const & lhs, memoryType_t const & rhs) noexcept
    {
      return
        lhs.memoryProps == rhs.memoryProps &&
        lhs.chunkSize == rhs.chunkSize &&
        lhs.mappable == rhs.mappable;
    };

    inline bool operator != (memoryType_t const & lhs, memoryType_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct memoryTypeDiffs_t
    {
      memoryTypeMembers_e diffs;
      std::unordered_set<size_t> memoryPropsDiffs;
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
            memoryType.memoryPropsDiffs.insert(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          memoryType.memoryPropsDiffs.insert(i);
        }
      }
      // diff member 'chunkSize':
      if (lhs.chunkSize != rhs.chunkSize)
        { memoryType.diffs |= memoryTypeMembers_e::chunkSize; }
      // diff member 'mappable':
      if (lhs.mappable != rhs.mappable)
        { memoryType.diffs |= memoryTypeMembers_e::mappable; }

      return memoryType.diffs != memoryTypeMembers_e::none;
    };

    // usageType things

    struct usageType_t
    {
      std::string name;
      std::vector<std::vector<vk::MemoryPropertyFlagBits>> memoryProps;
    };

    void importPod(
      humon::HuNode const & src, usageType_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, usageType_t & dest);

    void exportPod(usageType_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      usageType_t const & src, std::vector<uint8_t> & dest);

    std::string print(usageType_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, usageType_t const & src);

    enum class usageTypeMembers_e : int 
    {
      none = 0,
      name = 1 << 0,
      memoryProps = 1 << 1,
      all = name | memoryProps
    };

    inline bool operator == (usageType_t const & lhs, usageType_t const & rhs) noexcept
    {
      return
        lhs.name == rhs.name &&
        lhs.memoryProps == rhs.memoryProps;
    };

    inline bool operator != (usageType_t const & lhs, usageType_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct usageTypeDiffs_t
    {
      usageTypeMembers_e diffs;
      std::unordered_set<size_t> memoryPropsDiffs;
    };

    inline bool doPodsDiffer(
      usageType_t const & lhs,
      usageType_t const & rhs,
      usageTypeDiffs_t & usageType) noexcept
    {
      // diff member 'name':
      if (lhs.name != rhs.name)
        { usageType.diffs |= usageTypeMembers_e::name; }
      // diff member 'memoryProps':
      {
        auto [mn, mx] = std::minmax(lhs.memoryProps.size(), rhs.memoryProps.size());
        for (size_t i = 0; i < mn; ++i)
        {
          if (lhs.memoryProps[i] != rhs.memoryProps[i])
          {
            usageType.diffs |= usageTypeMembers_e::memoryProps;
            usageType.memoryPropsDiffs.insert(i);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          usageType.memoryPropsDiffs.insert(i);
        }
      }

      return usageType.diffs != usageTypeMembers_e::none;
    };

    // memoryPlan things

    struct memoryPlan_t
    {
      size_t maxChunkSize;
      size_t minChunksPerHeap;
      size_t allocRetries;
      size_t stagingSize;
      std::vector<memoryType_t> memoryTypes;
      stringDict<usageType_t> usageTypes;
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
      maxChunkSize = 1 << 0,
      minChunksPerHeap = 1 << 1,
      allocRetries = 1 << 2,
      stagingSize = 1 << 3,
      memoryTypes = 1 << 4,
      usageTypes = 1 << 5,
      all = maxChunkSize | minChunksPerHeap | allocRetries | stagingSize | memoryTypes | usageTypes
    };

    inline bool operator == (memoryPlan_t const & lhs, memoryPlan_t const & rhs) noexcept
    {
      return
        lhs.maxChunkSize == rhs.maxChunkSize &&
        lhs.minChunksPerHeap == rhs.minChunksPerHeap &&
        lhs.allocRetries == rhs.allocRetries &&
        lhs.stagingSize == rhs.stagingSize &&
        lhs.memoryTypes == rhs.memoryTypes &&
        lhs.usageTypes == rhs.usageTypes;
    };

    inline bool operator != (memoryPlan_t const & lhs, memoryPlan_t const & rhs) noexcept
    {
      return ! (lhs == rhs);
    };

    struct memoryPlanDiffs_t
    {
      memoryPlanMembers_e diffs;
      std::unordered_map<size_t, memoryTypeDiffs_t> memoryTypesDiffs;
      std::unordered_map<std::string, usageTypeDiffs_t> usageTypesDiffs;
    };

    inline bool doPodsDiffer(
      memoryPlan_t const & lhs,
      memoryPlan_t const & rhs,
      memoryPlanDiffs_t & memoryPlan) noexcept
    {
      // diff member 'maxChunkSize':
      if (lhs.maxChunkSize != rhs.maxChunkSize)
        { memoryPlan.diffs |= memoryPlanMembers_e::maxChunkSize; }
      // diff member 'minChunksPerHeap':
      if (lhs.minChunksPerHeap != rhs.minChunksPerHeap)
        { memoryPlan.diffs |= memoryPlanMembers_e::minChunksPerHeap; }
      // diff member 'allocRetries':
      if (lhs.allocRetries != rhs.allocRetries)
        { memoryPlan.diffs |= memoryPlanMembers_e::allocRetries; }
      // diff member 'stagingSize':
      if (lhs.stagingSize != rhs.stagingSize)
        { memoryPlan.diffs |= memoryPlanMembers_e::stagingSize; }
      // diff member 'memoryTypes':
      {
        auto [mn, mx] = std::minmax(lhs.memoryTypes.size(), rhs.memoryTypes.size());
        for (size_t i = 0; i < mn; ++i)
        {
          memoryTypeDiffs_t diffsEntry;
          if (doPodsDiffer(lhs.memoryTypes[i], rhs.memoryTypes[i], diffsEntry))
          {
            memoryPlan.diffs |= memoryPlanMembers_e::memoryTypes;
            memoryPlan.memoryTypesDiffs.insert_or_assign(i, diffsEntry);
          }
        }
        for (size_t i = mn; i < mx; ++i)
        {
          memoryTypeDiffs_t diffsEntry = { .diffs = memoryTypeMembers_e::all };
          memoryPlan.memoryTypesDiffs.insert_or_assign(i, diffsEntry);
        }
      }
      // diff member 'usageTypes':
      {
        for (auto const & [lhsKey, lhsIdx] : lhs.usageTypes.keys)
        {
          usageTypeDiffs_t diffsEntry;
          if (auto it = rhs.usageTypes.keys().find(lhsKey); it != rhs.usageTypes.keys().end())
          {
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.usageTypes[lhsIdx], rhs.usageTypes[rhsIdx], diffsEntry) == false)
              { continue; }
          }
          memoryPlan.diffs |= memoryPlanMembers_e::usageTypes;
          memoryPlan.usageTypesDiffs.insert_or_assign(lhsKey, diffsEntry);
        }
        for (auto const & [rhsKey, rhsIdx] : rhs.usageTypes.keys())
        {
          if (auto it = lhs.usageTypes.keys.find(rhsKey); it != lhs.usageTypes.keys.end())
            { continue; }

          usageTypeDiffs_t diffsEntry = { .diffs = usageTypeMembers_e::all };
          memoryPlan.usageTypesDiffs.insert_or_assign(rhsKey, diffsEntry);
        }
      }

      return memoryPlan.diffs != memoryPlanMembers_e::none;
    };

  }
}

#endif // #ifndef memoryPlan_GEN_H
