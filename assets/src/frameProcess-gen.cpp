#include "frameProcess-gen.h"

using namespace overground;
using namespace humon;
using namespace std;


void overground::importPod(
  humon::HuNode const & src, framePhase_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "kind")
  {
    auto & src0 = src / "kind";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.kind = std::move(dst0);
  }
  if (src % "ref")
  {
    auto & src0 = src / "ref";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.ref = std::move(dst0);
  }
}
void overground::importPod(
std::vector<uint8_t> const & src, framePhase_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(framePhase_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
framePhase_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
framePhase_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "kind: ";
  ss << (src.kind);
  ss << "\n" << indentIn << "ref: ";
  ss << (src.ref);
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, framePhase_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


void overground::importPod(
  humon::HuNode const & src, frameProcess_t & dest)
{
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "phases")
  {
    auto & src0 = src / "phases";
    std::vector<framePhase_t> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      framePhase_t dst1;
      importPod(src1, dst1);
      dst0.push_back(std::move(dst1));
    }
    dest.phases = std::move(dst0);
  }
}
void overground::importPod(
std::vector<uint8_t> const & src, frameProcess_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(frameProcess_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
frameProcess_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
frameProcess_t const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "phases: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.phases.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    framePhase_t const & src0 = src.phases[i0];
    ss << "\n" << indentIn;
    ss << print(src0, depth + 1);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, frameProcess_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


