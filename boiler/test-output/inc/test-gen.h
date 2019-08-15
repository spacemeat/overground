#ifndef test_GEN_H
#define test_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"

namespace overground
{
  struct testStr0
  {
    float dog;
    std::vector<float> cat;
    std::pair<float, int> cow;
    std::array<int, 3> bee;
    std::vector<std::vector<float>> pig;
    std::vector<std::pair<float, int>> roo;
    std::pair<std::vector<float>, int> ant;
    std::pair<float, std::vector<int>> ewe;
    std::pair<std::vector<float>, std::vector<int>> eel;
    std::pair<std::pair<float, int>, std::pair<size_t, std::string>> fly;
    std::vector<std::array<int, 3>> boar;
    std::array<std::vector<float>, 4> frog;
    std::pair<std::array<int, 10>, std::array<float, 20>> toad;
    std::vector<std::pair<std::array<std::vector<float>, 10>, std::pair<std::vector<std::array<std::string, 20>>, std::array<std::vector<long>, 30>>>> fish;
  };

  void importPod(
    humon::HuNode const & src, testStr0 & dest);

  void importPod(
    std::vector<uint8_t> const & src, testStr0 & dest);

  void exportPod(testStr0 const & src, 
    humon::HuNode & dest, int depth);

  void exportPod(
    testStr0 const & src, std::vector<uint8_t> & dest);

  std::string print(testStr0 const & src, int depth = 0);

  std::ostream & operator << (std::ostream & stream, testStr0 const & src);


}

#endif // #ifndef test_GEN_H
