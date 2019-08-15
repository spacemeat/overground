#include "framePlan-gen.h"

using namespace overground;
using namespace humon;
using namespace std;


void overground::importPod(
  humon::HuNode const & src, framePhase_t & dest)
{
  if (src % "kind")
  {
    auto & src0 = src / "kind";
    FramePhaseKinds dst0;
    dst0 = fromString<FramePhaseKinds>((std::string) src0); // leaf
    dest.kind = std::move(dst0);
  }
  if (src % "name")
  {
    auto & src0 = src / "name";
    std::string dst0;
    dst0 = (std::string) src0; // leaf
    dest.name = std::move(dst0);
  }
  if (src % "computePassName")
  {
    auto & src0 = src / "computePassName";
    std::optional<std::string> dst0;
    std::string dst1;
    {
      auto & src1 = src0;
      dst1 = (std::string) src1; // leaf
    }
    dst0.emplace(std::move(dst1));
    dest.computePassName = std::move(dst0);
  }
  if (src % "renderPassName")
  {
    auto & src0 = src / "renderPassName";
    std::optional<std::string> dst0;
    std::string dst1;
    {
      auto & src1 = src0;
      dst1 = (std::string) src1; // leaf
    }
    dst0.emplace(std::move(dst1));
    dest.renderPassName = std::move(dst0);
  }
  if (src % "subpass")
  {
    auto & src0 = src / "subpass";
    std::optional<int> dst0;
    int dst1;
    {
      auto & src1 = src0;
      dst1 = (int) src1; // leaf
    }
    dst0.emplace(std::move(dst1));
    dest.subpass = std::move(dst0);
  }
  if (src % "arg")
  {
    auto & src0 = src / "arg";
    std::optional<std::string> dst0;
    std::string dst1;
    {
      auto & src1 = src0;
      dst1 = (std::string) src1; // leaf
    }
    dst0.emplace(std::move(dst1));
    dest.arg = std::move(dst0);
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
  ss << "\n" << indentIn << "kind: ";
  ss << to_string(src.kind);
  ss << "\n" << indentIn << "name: ";
  ss << (src.name);
  ss << "\n" << indentIn << "computePassName: ";
  if ((bool) src.computePassName)
  {
    std::string const & src0 = * src.computePassName;
    ss << (src0);
  }
  else
    { ss << "<undefined>"; }
  ss << "\n" << indentIn << "renderPassName: ";
  if ((bool) src.renderPassName)
  {
    std::string const & src0 = * src.renderPassName;
    ss << (src0);
  }
  else
    { ss << "<undefined>"; }
  ss << "\n" << indentIn << "subpass: ";
  if ((bool) src.subpass)
  {
    int const & src0 = * src.subpass;
    ss << (src0);
  }
  else
    { ss << "<undefined>"; }
  ss << "\n" << indentIn << "arg: ";
  if ((bool) src.arg)
  {
    std::string const & src0 = * src.arg;
    ss << (src0);
  }
  else
    { ss << "<undefined>"; }
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, framePhase_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


void overground::importPod(
  humon::HuNode const & src, framePlan_t & dest)
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
std::vector<uint8_t> const & src, framePlan_t & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(framePlan_t const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
framePlan_t const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
framePlan_t const & src, int depth)
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


ostream & overground::operator << (ostream & stream, framePlan_t const & rhs)
{
  stream << print(rhs);
  return stream;
}


