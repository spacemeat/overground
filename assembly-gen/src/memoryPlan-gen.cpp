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
  if (src % "chunkSize")
  {
    auto & src0 = src / "chunkSize";
    size_t dst0;
    dst0 = (size_t) src0; // leaf
    dest.chunkSize = std::move(dst0);
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
  ss << "\n" << indentIn << "chunkSize: ";
  ss << (src.chunkSize);
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
  humon::HuNode const & src, usageType_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "memoryProps")
  {
    auto & src0 = src / "memoryProps";
    std::vector<std::vector<vk::MemoryPropertyFlagBits>> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::vector<vk::MemoryPropertyFlagBits> dst1;

      for (size_t i1 = 0; i1 < src1.size(); ++i1)
      {
        auto & src2 = src1 / i1;
        vk::MemoryPropertyFlagBits dst2;
        dst2 = fromString<vk::MemoryPropertyFlagBits>((std::string) src2); // leaf

        dst1.push_back(std::move(dst2));
      }

      dst0.push_back(std::move(dst1));
    }
    dest.memoryProps = std::move(dst0);
  }
}

void overground::memoryPlan::importPod(
std::vector<uint8_t> const & src, usageType_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::memoryPlan::exportPod(usageType_t const & src,
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

void overground::memoryPlan::exportPod(
usageType_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}

std::string overground::memoryPlan::print(
  usageType_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "memoryProps: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.memoryProps.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::vector<vk::MemoryPropertyFlagBits> const & src0 = src.memoryProps[i0];
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      vk::MemoryPropertyFlagBits const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << to_string(src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}

ostream & overground::memoryPlan::operator << (ostream & stream, usageType_t const & rhs)
{
  stream << print(rhs);
  return stream;
}

void overground::memoryPlan::importPod(
  humon::HuNode const & src, memoryPlan_t & dest)
{
  if (src % "maxChunkSize")
  {
    auto & src0 = src / "maxChunkSize";
    size_t dst0;
    dst0 = (size_t) src0; // leaf
    dest.maxChunkSize = std::move(dst0);
  }
  if (src % "minChunksPerHeap")
  {
    auto & src0 = src / "minChunksPerHeap";
    size_t dst0;
    dst0 = (size_t) src0; // leaf
    dest.minChunksPerHeap = std::move(dst0);
  }
  if (src % "allocRetries")
  {
    auto & src0 = src / "allocRetries";
    size_t dst0;
    dst0 = (size_t) src0; // leaf
    dest.allocRetries = std::move(dst0);
  }
  if (src % "stagingSize")
  {
    auto & src0 = src / "stagingSize";
    size_t dst0;
    dst0 = (size_t) src0; // leaf
    dest.stagingSize = std::move(dst0);
  }
  if (src % "memoryTypes")
  {
    auto & src0 = src / "memoryTypes";
    std::vector<memoryType_t> dst0;

    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      memoryType_t dst1;
      importPod(src1, dst1);

      dst0.push_back(std::move(dst1));
    }
    dest.memoryTypes = std::move(dst0);
  }
  if (src % "usageTypes")
  {
    auto & src0 = src / "usageTypes";
    stringDict<usageType_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      auto const & key = src0.keyAt(i0);
      usageType_t dst1;
      importPod(src1, dst1);
      dst0.push_back(key, std::move(dst1));
    }
    dest.usageTypes = std::move(dst0);
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
  ss << "\n" << indentIn << "maxChunkSize: ";
  ss << (src.maxChunkSize);
  ss << "\n" << indentIn << "minChunksPerHeap: ";
  ss << (src.minChunksPerHeap);
  ss << "\n" << indentIn << "allocRetries: ";
  ss << (src.allocRetries);
  ss << "\n" << indentIn << "stagingSize: ";
  ss << (src.stagingSize);
  ss << "\n" << indentIn << "memoryTypes: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.memoryTypes.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    memoryType_t const & src0 = src.memoryTypes[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "usageTypes: ";
  ss << "{";
  for (size_t i0 = 0; i0 < src.usageTypes.size(); ++i0)
  {
    auto const & [key, idx] = src.usageTypes.keys[i0];
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    usageType_t const & src0 = src.usageTypes[idx];
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
