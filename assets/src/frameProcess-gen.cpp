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
  // NOTE: This operation has not been implemented yet.
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
  // NOTE: This operation has not been implemented yet.
}


std::string overground::print(
framePhase_t const & src, int depth)
{
  std::ostringstream ss;
  ss << "{\n";
    ss << "    " << "name: ";
    ss << (src.name) << "\n";
    ss << "    " << "kind: ";
    ss << (src.kind) << "\n";
    ss << "    " << "ref: ";
    ss << (src.ref) << "\n";
  ss << "}\n";
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
  // NOTE: This operation has not been implemented yet.
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
  // NOTE: This operation has not been implemented yet.
}


std::string overground::print(
frameProcess_t const & src, int depth)
{
  std::ostringstream ss;
  ss << "{\n";
    ss << "    " << "name: ";
    ss << (src.name) << "\n";
    ss << "    " << "phases: ";
    ss << "[\n";
    for (size_t i1 = 0; i1 < src.phases.size(); ++i1)
    {
      framePhase_t const & src1 = src.phases[i1];
      ss << "    ";
      ss << print(src1, 3);
    }
    ss << "  " << "]\n";
  ss << "}\n";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, frameProcess_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


