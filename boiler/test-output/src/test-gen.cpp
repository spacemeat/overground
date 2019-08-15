#include "test-gen.h"

using namespace overground;
using namespace humon;
using namespace std;


void overground::importPod(
  humon::HuNode const & src, testStr0 & dest)
{
  if (src % "dog")
  {
    auto & src0 = src / "dog";
    float dst0;
    dst0 = (float) src0; // leaf
    dest.dog = std::move(dst0);
  }
  if (src % "cat")
  {
    auto & src0 = src / "cat";
    std::vector<float> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      float dst1;
      dst1 = (float) src1; // leaf
      dst0.push_back(std::move(dst1));
    }
    dest.cat = std::move(dst0);
  }
  if (src % "cow")
  {
    auto & src0 = src / "cow";
    std::pair<float, int> dst0;
    float dst1a;
    {
      auto & src1a = src0 / 0;
      dst1a = (float) src1a; // leaf
    }
    int dst1b;
    {
      auto & src1b = src0 / 1;
      dst1b = (int) src1b; // leaf
    }
    dst0 = std::make_pair(
      std::move(dst1a), std::move(dst1b));
    dest.cow = std::move(dst0);
  }
  if (src % "bee")
  {
    auto & src0 = src / "bee";
    std::array<int, 3> dst0;
    for (size_t i0 = 0; i0 < 3; ++i0)
    {
      auto & src1 = src0 / i0;
      int dst1;
      dst1 = (int) src1; // leaf
      dst0[i0] = std::move(dst1);
    }
    dest.bee = std::move(dst0);
  }
  if (src % "pig")
  {
    auto & src0 = src / "pig";
    std::vector<std::vector<float>> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::vector<float> dst1;
      for (size_t i1 = 0; i1 < src1.size(); ++i1)
      {
        auto & src2 = src1 / i1;
        float dst2;
        dst2 = (float) src2; // leaf
        dst1.push_back(std::move(dst2));
      }
      dst0.push_back(std::move(dst1));
    }
    dest.pig = std::move(dst0);
  }
  if (src % "roo")
  {
    auto & src0 = src / "roo";
    std::vector<std::pair<float, int>> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::pair<float, int> dst1;
      float dst2a;
      {
        auto & src2a = src1 / 0;
        dst2a = (float) src2a; // leaf
      }
      int dst2b;
      {
        auto & src2b = src1 / 1;
        dst2b = (int) src2b; // leaf
      }
      dst1 = std::make_pair(
        std::move(dst2a), std::move(dst2b));
      dst0.push_back(std::move(dst1));
    }
    dest.roo = std::move(dst0);
  }
  if (src % "ant")
  {
    auto & src0 = src / "ant";
    std::pair<std::vector<float>, int> dst0;
    std::vector<float> dst1a;
    {
      auto & src1a = src0 / 0;
      for (size_t i1 = 0; i1 < src1a.size(); ++i1)
      {
        auto & src2 = src1a / i1;
        float dst2;
        dst2 = (float) src2; // leaf
        dst1a.push_back(std::move(dst2));
      }
    }
    int dst1b;
    {
      auto & src1b = src0 / 1;
      dst1b = (int) src1b; // leaf
    }
    dst0 = std::make_pair(
      std::move(dst1a), std::move(dst1b));
    dest.ant = std::move(dst0);
  }
  if (src % "ewe")
  {
    auto & src0 = src / "ewe";
    std::pair<float, std::vector<int>> dst0;
    float dst1a;
    {
      auto & src1a = src0 / 0;
      dst1a = (float) src1a; // leaf
    }
    std::vector<int> dst1b;
    {
      auto & src1b = src0 / 1;
      for (size_t i1 = 0; i1 < src1b.size(); ++i1)
      {
        auto & src2 = src1b / i1;
        int dst2;
        dst2 = (int) src2; // leaf
        dst1b.push_back(std::move(dst2));
      }
    }
    dst0 = std::make_pair(
      std::move(dst1a), std::move(dst1b));
    dest.ewe = std::move(dst0);
  }
  if (src % "eel")
  {
    auto & src0 = src / "eel";
    std::pair<std::vector<float>, std::vector<int>> dst0;
    std::vector<float> dst1a;
    {
      auto & src1a = src0 / 0;
      for (size_t i1 = 0; i1 < src1a.size(); ++i1)
      {
        auto & src2 = src1a / i1;
        float dst2;
        dst2 = (float) src2; // leaf
        dst1a.push_back(std::move(dst2));
      }
    }
    std::vector<int> dst1b;
    {
      auto & src1b = src0 / 1;
      for (size_t i1 = 0; i1 < src1b.size(); ++i1)
      {
        auto & src2 = src1b / i1;
        int dst2;
        dst2 = (int) src2; // leaf
        dst1b.push_back(std::move(dst2));
      }
    }
    dst0 = std::make_pair(
      std::move(dst1a), std::move(dst1b));
    dest.eel = std::move(dst0);
  }
  if (src % "fly")
  {
    auto & src0 = src / "fly";
    std::pair<std::pair<float, int>, std::pair<size_t, std::string>> dst0;
    std::pair<float, int> dst1a;
    {
      auto & src1a = src0 / 0;
      float dst2a;
      {
        auto & src2a = src1a / 0;
        dst2a = (float) src2a; // leaf
      }
      int dst2b;
      {
        auto & src2b = src1a / 1;
        dst2b = (int) src2b; // leaf
      }
      dst1a = std::make_pair(
        std::move(dst2a), std::move(dst2b));
    }
    std::pair<size_t, std::string> dst1b;
    {
      auto & src1b = src0 / 1;
      size_t dst2a;
      {
        auto & src2a = src1b / 0;
        dst2a = (size_t) src2a; // leaf
      }
      std::string dst2b;
      {
        auto & src2b = src1b / 1;
        dst2b = (std::string) src2b; // leaf
      }
      dst1b = std::make_pair(
        std::move(dst2a), std::move(dst2b));
    }
    dst0 = std::make_pair(
      std::move(dst1a), std::move(dst1b));
    dest.fly = std::move(dst0);
  }
  if (src % "boar")
  {
    auto & src0 = src / "boar";
    std::vector<std::array<int, 3>> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::array<int, 3> dst1;
      for (size_t i1 = 0; i1 < 3; ++i1)
      {
        auto & src2 = src1 / i1;
        int dst2;
        dst2 = (int) src2; // leaf
        dst1[i1] = std::move(dst2);
      }
      dst0.push_back(std::move(dst1));
    }
    dest.boar = std::move(dst0);
  }
  if (src % "frog")
  {
    auto & src0 = src / "frog";
    std::array<std::vector<float>, 4> dst0;
    for (size_t i0 = 0; i0 < 4; ++i0)
    {
      auto & src1 = src0 / i0;
      std::vector<float> dst1;
      for (size_t i1 = 0; i1 < src1.size(); ++i1)
      {
        auto & src2 = src1 / i1;
        float dst2;
        dst2 = (float) src2; // leaf
        dst1.push_back(std::move(dst2));
      }
      dst0[i0] = std::move(dst1);
    }
    dest.frog = std::move(dst0);
  }
  if (src % "toad")
  {
    auto & src0 = src / "toad";
    std::pair<std::array<int, 10>, std::array<float, 20>> dst0;
    std::array<int, 10> dst1a;
    {
      auto & src1a = src0 / 0;
      for (size_t i1 = 0; i1 < 10; ++i1)
      {
        auto & src2 = src1a / i1;
        int dst2;
        dst2 = (int) src2; // leaf
        dst1a[i1] = std::move(dst2);
      }
    }
    std::array<float, 20> dst1b;
    {
      auto & src1b = src0 / 1;
      for (size_t i1 = 0; i1 < 20; ++i1)
      {
        auto & src2 = src1b / i1;
        float dst2;
        dst2 = (float) src2; // leaf
        dst1b[i1] = std::move(dst2);
      }
    }
    dst0 = std::make_pair(
      std::move(dst1a), std::move(dst1b));
    dest.toad = std::move(dst0);
  }
  if (src % "fish")
  {
    auto & src0 = src / "fish";
    std::vector<std::pair<std::array<std::vector<float>, 10>, std::pair<std::vector<std::array<std::string, 20>>, std::array<std::vector<long>, 30>>>> dst0;
    for (size_t i0 = 0; i0 < src0.size(); ++i0)
    {
      auto & src1 = src0 / i0;
      std::pair<std::array<std::vector<float>, 10>, std::pair<std::vector<std::array<std::string, 20>>, std::array<std::vector<long>, 30>>> dst1;
      std::array<std::vector<float>, 10> dst2a;
      {
        auto & src2a = src1 / 0;
        for (size_t i2 = 0; i2 < 10; ++i2)
        {
          auto & src3 = src2a / i2;
          std::vector<float> dst3;
          for (size_t i3 = 0; i3 < src3.size(); ++i3)
          {
            auto & src4 = src3 / i3;
            float dst4;
            dst4 = (float) src4; // leaf
            dst3.push_back(std::move(dst4));
          }
          dst2a[i2] = std::move(dst3);
        }
      }
      std::pair<std::vector<std::array<std::string, 20>>, std::array<std::vector<long>, 30>> dst2b;
      {
        auto & src2b = src1 / 1;
        std::vector<std::array<std::string, 20>> dst3a;
        {
          auto & src3a = src2b / 0;
          for (size_t i3 = 0; i3 < src3a.size(); ++i3)
          {
            auto & src4 = src3a / i3;
            std::array<std::string, 20> dst4;
            for (size_t i4 = 0; i4 < 20; ++i4)
            {
              auto & src5 = src4 / i4;
              std::string dst5;
              dst5 = (std::string) src5; // leaf
              dst4[i4] = std::move(dst5);
            }
            dst3a.push_back(std::move(dst4));
          }
        }
        std::array<std::vector<long>, 30> dst3b;
        {
          auto & src3b = src2b / 1;
          for (size_t i3 = 0; i3 < 30; ++i3)
          {
            auto & src4 = src3b / i3;
            std::vector<long> dst4;
            for (size_t i4 = 0; i4 < src4.size(); ++i4)
            {
              auto & src5 = src4 / i4;
              long dst5;
              dst5 = (long) src5; // leaf
              dst4.push_back(std::move(dst5));
            }
            dst3b[i3] = std::move(dst4);
          }
        }
        dst2b = std::make_pair(
          std::move(dst3a), std::move(dst3b));
      }
      dst1 = std::make_pair(
        std::move(dst2a), std::move(dst2b));
      dst0.push_back(std::move(dst1));
    }
    dest.fish = std::move(dst0);
  }
}
void overground::importPod(
std::vector<uint8_t> const & src, testStr0 & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(testStr0 const & src, 
humon::HuNode & dest, int depth)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


void overground::exportPod(
testStr0 const & src, std::vector<uint8_t> & dest)
{
  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
}


std::string overground::print(
testStr0 const & src, int depth)
{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{";
  ss << "\n" << indentIn << "dog: ";
  ss << (src.dog);
  ss << "\n" << indentIn << "cat: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.cat.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.cat[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "cow: ";
  {
    ss << "[";
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.cow.first;
    ss << "\n" << indentIn;
    ss << (src0);
    ss << indentIn;
    depth -= 1;
  }
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    int const & src0 = src.cow.second;
    ss << "\n" << indentIn;
    ss << (src0);
  depth -= 1;
  ss << "\n" << prevIndentIn << "]";
  }
  ss << "\n" << indentIn << "bee: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.bee.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    int const & src0 = src.bee[i0];
    ss << "\n" << indentIn;
    ss << (src0);
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "pig: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.pig.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::vector<float> const & src0 = src.pig[i0];
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      float const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << (src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "roo: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.roo.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::pair<float, int> const & src0 = src.roo[i0];
    {
      ss << "[";
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      float const & src1 = src0.first;
      ss << "\n" << indentIn;
      ss << (src1);
      ss << indentIn;
      depth -= 1;
    }
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      int const & src1 = src0.second;
      ss << "\n" << indentIn;
      ss << (src1);
    depth -= 1;
    ss << "\n" << prevIndentIn << "]";
    }
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "ant: ";
  {
    ss << "[";
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::vector<float> const & src0 = src.ant.first;
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      float const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << (src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
    ss << indentIn;
    depth -= 1;
  }
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    int const & src0 = src.ant.second;
    ss << "\n" << indentIn;
    ss << (src0);
  depth -= 1;
  ss << "\n" << prevIndentIn << "]";
  }
  ss << "\n" << indentIn << "ewe: ";
  {
    ss << "[";
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    float const & src0 = src.ewe.first;
    ss << "\n" << indentIn;
    ss << (src0);
    ss << indentIn;
    depth -= 1;
  }
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::vector<int> const & src0 = src.ewe.second;
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      int const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << (src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
  depth -= 1;
  ss << "\n" << prevIndentIn << "]";
  }
  ss << "\n" << indentIn << "eel: ";
  {
    ss << "[";
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::vector<float> const & src0 = src.eel.first;
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      float const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << (src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
    ss << indentIn;
    depth -= 1;
  }
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::vector<int> const & src0 = src.eel.second;
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      int const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << (src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
  depth -= 1;
  ss << "\n" << prevIndentIn << "]";
  }
  ss << "\n" << indentIn << "fly: ";
  {
    ss << "[";
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::pair<float, int> const & src0 = src.fly.first;
    {
      ss << "[";
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      float const & src1 = src0.first;
      ss << "\n" << indentIn;
      ss << (src1);
      ss << indentIn;
      depth -= 1;
    }
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      int const & src1 = src0.second;
      ss << "\n" << indentIn;
      ss << (src1);
    depth -= 1;
    ss << "\n" << prevIndentIn << "]";
    }
    ss << indentIn;
    depth -= 1;
  }
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::pair<size_t, std::string> const & src0 = src.fly.second;
    {
      ss << "[";
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      size_t const & src1 = src0.first;
      ss << "\n" << indentIn;
      ss << (src1);
      ss << indentIn;
      depth -= 1;
    }
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      std::string const & src1 = src0.second;
      ss << "\n" << indentIn;
      ss << (src1);
    depth -= 1;
    ss << "\n" << prevIndentIn << "]";
    }
  depth -= 1;
  ss << "\n" << prevIndentIn << "]";
  }
  ss << "\n" << indentIn << "boar: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.boar.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::array<int, 3> const & src0 = src.boar[i0];
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      int const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << (src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "frog: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.frog.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::vector<float> const & src0 = src.frog[i0];
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      float const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << (src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << indentIn << "toad: ";
  {
    ss << "[";
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::array<int, 10> const & src0 = src.toad.first;
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      int const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << (src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
    ss << indentIn;
    depth -= 1;
  }
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::array<float, 20> const & src0 = src.toad.second;
    ss << "[";
    for (size_t i1 = 0; i1 < src0.size(); ++i1)
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      float const & src1 = src0[i1];
      ss << "\n" << indentIn;
      ss << (src1);
      depth -= 1;
    }
    ss << "\n" << indentIn << "]";
  depth -= 1;
  ss << "\n" << prevIndentIn << "]";
  }
  ss << "\n" << indentIn << "fish: ";
  ss << "[";
  for (size_t i0 = 0; i0 < src.fish.size(); ++i0)
  {
    depth += 1;
    string prevIndentIn(depth * 2, ' ');
    string indentIn(2 + depth * 2, ' ');
    std::pair<std::array<std::vector<float>, 10>, std::pair<std::vector<std::array<std::string, 20>>, std::array<std::vector<long>, 30>>> const & src0 = src.fish[i0];
    {
      ss << "[";
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      std::array<std::vector<float>, 10> const & src1 = src0.first;
      ss << "[";
      for (size_t i2 = 0; i2 < src1.size(); ++i2)
      {
        depth += 1;
        string prevIndentIn(depth * 2, ' ');
        string indentIn(2 + depth * 2, ' ');
        std::vector<float> const & src2 = src1[i2];
        ss << "[";
        for (size_t i3 = 0; i3 < src2.size(); ++i3)
        {
          depth += 1;
          string prevIndentIn(depth * 2, ' ');
          string indentIn(2 + depth * 2, ' ');
          float const & src3 = src2[i3];
          ss << "\n" << indentIn;
          ss << (src3);
          depth -= 1;
        }
        ss << "\n" << indentIn << "]";
        depth -= 1;
      }
      ss << "\n" << indentIn << "]";
      ss << indentIn;
      depth -= 1;
    }
    {
      depth += 1;
      string prevIndentIn(depth * 2, ' ');
      string indentIn(2 + depth * 2, ' ');
      std::pair<std::vector<std::array<std::string, 20>>, std::array<std::vector<long>, 30>> const & src1 = src0.second;
      {
        ss << "[";
        depth += 1;
        string prevIndentIn(depth * 2, ' ');
        string indentIn(2 + depth * 2, ' ');
        std::vector<std::array<std::string, 20>> const & src2 = src1.first;
        ss << "[";
        for (size_t i3 = 0; i3 < src2.size(); ++i3)
        {
          depth += 1;
          string prevIndentIn(depth * 2, ' ');
          string indentIn(2 + depth * 2, ' ');
          std::array<std::string, 20> const & src3 = src2[i3];
          ss << "[";
          for (size_t i4 = 0; i4 < src3.size(); ++i4)
          {
            depth += 1;
            string prevIndentIn(depth * 2, ' ');
            string indentIn(2 + depth * 2, ' ');
            std::string const & src4 = src3[i4];
            ss << "\n" << indentIn;
            ss << (src4);
            depth -= 1;
          }
          ss << "\n" << indentIn << "]";
          depth -= 1;
        }
        ss << "\n" << indentIn << "]";
        ss << indentIn;
        depth -= 1;
      }
      {
        depth += 1;
        string prevIndentIn(depth * 2, ' ');
        string indentIn(2 + depth * 2, ' ');
        std::array<std::vector<long>, 30> const & src2 = src1.second;
        ss << "[";
        for (size_t i3 = 0; i3 < src2.size(); ++i3)
        {
          depth += 1;
          string prevIndentIn(depth * 2, ' ');
          string indentIn(2 + depth * 2, ' ');
          std::vector<long> const & src3 = src2[i3];
          ss << "[";
          for (size_t i4 = 0; i4 < src3.size(); ++i4)
          {
            depth += 1;
            string prevIndentIn(depth * 2, ' ');
            string indentIn(2 + depth * 2, ' ');
            long const & src4 = src3[i4];
            ss << "\n" << indentIn;
            ss << (src4);
            depth -= 1;
          }
          ss << "\n" << indentIn << "]";
          depth -= 1;
        }
        ss << "\n" << indentIn << "]";
      depth -= 1;
      ss << "\n" << prevIndentIn << "]";
      }
    depth -= 1;
    ss << "\n" << prevIndentIn << "]";
    }
    depth -= 1;
  }
  ss << "\n" << indentIn << "]";
  ss << "\n" << prevIndentIn << "}";
  return ss.str();
}


ostream & overground::operator << (ostream & stream, testStr0 const & rhs)
{
  stream << print(rhs);
  return stream;
}


