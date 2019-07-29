#ifndef frameProcess_GEN_H
#define frameProcess_GEN_H

#include <string>
#include <vector>
#include <optional>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  struct framePhase_t
  {
    std::string name;
    std::string kind;
    std::string ref;
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


  struct frameProcess_t
  {
    std::string name;
    std::vector<framePhase_t> phases;
  };

  void importPod(
    humon::HuNode const & src, frameProcess_t & dest);

  void importPod(
    std::vector<uint8_t> const & src, frameProcess_t & dest);

  void exportPod(frameProcess_t const & src, 
    humon::HuNode & dest, int depth);

  void exportPod(
    frameProcess_t const & src, std::vector<uint8_t> & dest);

  std::string print(frameProcess_t const & src, int depth = 0);

  std::ostream & operator << (std::ostream & stream, frameProcess_t const & src);


}

#endif // #ifndef frameProcess_GEN_H
