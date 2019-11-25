#include "memoryPlan-gen.h"

using namespace overground;
using namespace overground::memoryPlan;
using namespace humon;
using namespace std;


void overground::memoryPlan::importPod(
  humon::HuNode const & src, memoryType_t & dest)
{
  if (src % "memoryProps")
  {
    auto & src0 = src / "memoryProps";
    std::vector<vk::MemoryPropertyFlagBits> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      vk::MemoryPropertyFlagBits dst1;
      dst1 = fromString<vk::MemoryPropertyFlagBits>((std::string) src1); // leaf

      dst0.push_back(std::move(dst1));
    }
    dest.memoryProps = std::move(dst0);
  }
  if (src % "allocChunkSize")
  {
    auto & src0 = src / "allocChunkSize";
    size_t dst0;
    dst0 = (size_t) src0; // leaf
    dest.allocChunkSize = std::move(dst0);
  }
  if (src % "mappable")
  {
    auto & src0 = src / "mappable";
    bool dst0;
    dst0 = (bool) src0; // leaf
    dest.mappable = std::move(dst0);
  }
}

void overground::memoryPlan::importPod(
std::vector<uint8_t> const & src, memoryType_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::memoryPlan::exportPod(memoryType_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::memoryPlan::exportPod(
memoryType_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::memoryPlan::print(
  memoryType_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "memoryProps: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.memoryProps.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    vk::MemoryPropertyFlagBits const & src0 = src.memoryProps[i0];
    ss << "\n" << indentIn;
    ss << to_string(src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "allocChunkSize: ";
  ss << (src.allocChunkSize);
  ss << "\n" << indentIn << "mappable: ";
  ss << (src.mappable);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::memoryPlan::operator << (ostream & stream, memoryType_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::memoryPlan::importPod(
  humon::HuNode const & src, memoryAlloc_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "types")
  {
    auto & src0 = src / "types";
    std::vector<memoryType_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      memoryType_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.types = std::move(dst0);
  }
}

void overground::memoryPlan::importPod(
std::vector<uint8_t> const & src, memoryAlloc_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::memoryPlan::exportPod(memoryAlloc_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::memoryPlan::exportPod(
memoryAlloc_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::memoryPlan::print(
  memoryAlloc_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "types: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.types.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    memoryType_t const & src0 = src.types[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::memoryPlan::operator << (ostream & stream, memoryAlloc_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::memoryPlan::importPod(
  humon::HuNode const & src, memoryPlan_t & dest)
{
  if (src % "allocs")
  {
    auto & src0 = src / "allocs";
    stringDict<memoryAlloc_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      memoryAlloc_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.allocs = std::move(dst0);
  }
}

void overground::memoryPlan::importPod(
std::vector<uint8_t> const & src, memoryPlan_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::memoryPlan::exportPod(memoryPlan_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::memoryPlan::exportPod(
memoryPlan_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::memoryPlan::print(
  memoryPlan_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "allocs: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.allocs.size(); ++i0)
  {
    auto const & [key, idx] = src.allocs.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    memoryAlloc_t const & src0 = src.allocs[idx];
    ss << indentIn << key << ": ";
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "}";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::memoryPlan::operator << (ostream & stream, memoryPlan_t const & rhs)
{
  stream << print(rhs);
  return stream;
}
