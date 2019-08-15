#ifndef framePlan_GEN_H
#define framePlan_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  struct framePhase_t
  {
    FramePhaseKinds kind;
    std::string name;
    std::optional<std::string> computePassName;
    std::optional<std::string> renderPassName;
    std::optional<int> subpass;
    std::optional<std::string> arg;
  };

  void importPod(
    humon::HuNode const & src, framePhase_t & dest);

  void importPod(
    std::vector<uint8_t> const & src, framePhase_t & dest);

  void exportPod(framePhase_t const & src, 
    humon::HuNode & dest, int depth);

  void exportPod(
    framePhase_t const & src, std::vector<uint8_t> & dest);

  std::string print(framePhase_t const & src, int depth = 0);

  std::ostream & operator << (std::ostream & stream, framePhase_t const & src);


  struct framePlan_t
  {
    std::string name;
    std::vector<framePhase_t> phases;
  };

  void importPod(
    humon::HuNode const & src, framePlan_t & dest);

  void importPod(
    std::vector<uint8_t> const & src, framePlan_t & dest);

  void exportPod(framePlan_t const & src, 
    humon::HuNode & dest, int depth);

  void exportPod(
    framePlan_t const & src, std::vector<uint8_t> & dest);

  std::string print(framePlan_t const & src, int depth = 0);

  std::ostream & operator << (std::ostream & stream, framePlan_t const & src);


}

#endif // #ifndef framePlan_GEN_H
