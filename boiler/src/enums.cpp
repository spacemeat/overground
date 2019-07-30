#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include "ansiTerm.h"
#include "fmt/core.h"
#include "fmt/ostream.h"
#include "utils.h"
#include "boiler.h"


using namespace std;
using namespace humon;
using namespace overground;


string enumDecl = "VULKAN_HPP_INLINE std::string to_string(";
string caseDecl = "::";
string returnDecl = "return ";


constexpr auto enumParserHeaderPreamble = "\
#ifndef ENUMPARSERS_H\n\
#define ENUMPARSERS_H\n\
\n\
#include \"utils.h\"\n\
\n\
#define GLFW_INCLUDE_VULKAN\n\
#include <GLFW/glfw3.h>\n\
#include <vulkan/vulkan.hpp>\n\
\n\
namespace overground\n\
{{\n\
  template<class EnumType>\n\
  EnumType fromString(std::string_view rhs);\n\
\n";

constexpr auto enumParserHeaderPostamble = "\
}}\n\
\n\
#endif // #ifndef ENUMPARSERS_H\n\
";

constexpr auto enumParserCppPreamble = "\
#include \"enumParsers.h\"\n\
\n\
using namespace std;\n\
using namespace overground;\n\
\n";


map<string, vector<pair<string, string>>> enumDefs;

bool endsWith(string_view what, string_view endsWith, size_t & idx)
{
  auto it = find_end(
    what.begin(), what.end(), 
    endsWith.begin(), endsWith.end());
  idx = distance(what.begin(), it);

  return it != what.end() && it + endsWith.size() == what.end();
}


void loadEnumDefinitions(path_t const & path)
{
  logFn();

  auto hpp = loadFileAsString(path);
  auto it = hpp.begin();
  auto searcher = boyer_moore_searcher(
        enumDecl.begin(), enumDecl.end());
  auto cocoSearcher = boyer_moore_searcher(
        caseDecl.begin(), caseDecl.end());
  auto returnSearcher = boyer_moore_searcher(
        returnDecl.begin(), returnDecl.end());

  while (it != hpp.end())
  {
    it = search(it, hpp.end(), searcher);
    
    if (it != hpp.end())
    {
      advance(it, enumDecl.size());

      auto nlit = find(it, hpp.end(), ')');
      string ln(it, nlit);

      if (size_t tokenSize; endsWith(ln, " value", tokenSize))
      {
        string enumName(ln.substr(0, tokenSize));

        if (size_t nameSize; 
          endsWith(enumName, "Flags", nameSize) == false &&
          endsWith(enumName, "FlagsEXT", nameSize) == false &&
          endsWith(enumName, "FlagsKHR", nameSize) == false)
        {
          log(0, fmt::format("{}Reading enum {}{}{}",
            ansi::darkBlue, ansi::lightBlue, enumName, ansi::off));

          vector<pair<string, string>> defs;

          auto nlit = find(it, hpp.end(), '\n');
          it = nlit;
          advance(it, 1);
          nlit = find(it, hpp.end(), '\n');

          while (equal(it, nlit, (" }"sv).begin()) == false)
          {
            it = search(it, nlit, cocoSearcher);
            if (it != nlit)
            {
              advance(it, 2);
              auto coIt = find(it, nlit, ':');
              string eName(it, coIt);
              it = search(coIt, nlit, returnSearcher);
              if (it != nlit)
              {
                advance(it, returnDecl.size());
                auto seIt = find(it, nlit, ';');
                string value(it, seIt);

                log(0, logTags::verb, fmt::format("  {}reading enum name {}{}{}{}, value {}{}{}",
                  ansi::darkYellow, 
                  ansi::darkBlue, eName, ansi::off,
                  ansi::darkYellow,
                  ansi::darkCyan, value, ansi::off));

                defs.push_back(make_pair(eName, value));
              }
            }
            
            it = nlit;
            advance(it, 1);
            nlit = find(it, hpp.end(), '\n');
          }

          enumDefs.emplace(enumName, move(defs));
        }
      }

      it = nlit;
    }
  }
}


ofstream files[2];


static void openFiles(path_t const & dir)
{
  logFn();

  // header
  auto featureFile = "enumParsers-gen.h";
  auto featurePath = path_t(dir).append("inc").append(featureFile);
  log(0, fmt::format("Generating {}{}.{}",
    ansi::lightBlue, featurePath, ansi::off));

  auto & ofs = files[0];
  ofs.open(featurePath);
  ofs << fmt::format(enumParserHeaderPreamble, 
    fmt::arg("featureName", "ENUMPARSERS"));

  // srcs
  auto featureCppFile = "enumParsers-gen.cpp";
  auto featureCppPath = path_t(dir).append("src").append(featureCppFile);
  log(0, fmt::format("Generating {}{}.{}",
    ansi::lightBlue, featureCppPath, ansi::off));

  auto & ofsCpp = files[1];
  ofsCpp.open(featureCppPath);
  ofsCpp << enumParserCppPreamble;
}


static void closeFiles()
{
  logFn();

  auto & ofs = files[0];
  ofs << fmt::format(enumParserHeaderPostamble,
    fmt::arg("featureName", "ENUMPARSERS"));
}


void outputEnumHeader()
{
  logFn();

  auto & ofs = files[0];

  for (auto & [enumName, enumEntry] : enumDefs)
  {
    ofs << fmt::format("\
  template<>\n\
  vk::{enumName} fromString<vk::{enumName}>(std::string_view rhs);\n",
      fmt::arg("enumName", enumName));
  }
}


void outputEnumCpp()
{
  logFn();

  auto & ofs = files[1];

  for (auto & [enumName, enumEntries] : enumDefs)
  {
    ofs << fmt::format("\
template<>\n\
vk::{enumName} overground::fromString<vk::{enumName}>(std::string_view rhs)\n\
{{\n\
  static initializer_list<vk::{enumName}> il = {{\n",
      fmt::arg("enumName", enumName));

    for (auto & [enumValue, _] : enumEntries)
    {
      ofs << fmt::format("\
    vk::{enumName}::{enumValue},\n",
        fmt::arg("enumName", enumName),
        fmt::arg("enumValue", enumValue));
    }    

    ofs << fmt::format("\
  }};\n\
\n\
  for (auto val : il)\n\
  {{\n\
    if (to_string(val) == rhs)\n\
      {{ return val; }}\n\
  }}\n\
\n\
  throw runtime_error(fmt::format(\"Invalid value {{}}{{}}{{}} for {{}}{enumName}{{}}\", ansi::darkBlue, rhs, ansi::off, ansi::lightCyan, ansi::off));\n\
}}\n\n",
      fmt::arg("enumName", enumName));
  }
}

int overground::enumsMain(path_t const & headerPath, path_t const & outputDir)
{
  log(0, fmt::format("\
{}Making boilerplate code from enum definitions in {}.{}\n\
Output base: {}{}{}",
    ansi::lightCyan, headerPath, ansi::off,
    ansi::lightYellow, outputDir, ansi::off));
  
  if (fs::exists(outputDir) == false)
  {
    log(0, fmt::format("{}Creating {}.{}",
      ansi::darkYellow, outputDir, ansi::off));
    fs::create_directory(outputDir);
  }

  auto outuptIncDir = path_t(outputDir).append("/inc");
  if (fs::exists(outuptIncDir) == false)
  {
    log(0, fmt::format("{}Creating {}.{}",
      ansi::darkYellow, outuptIncDir, ansi::off));
    fs::create_directory(outuptIncDir);
  }

  auto outupSrccDir = path_t(outputDir).append("/src");
  if (fs::exists(outupSrccDir) == false)
  {
    log(0, fmt::format("{}Creating {}.{}",
      ansi::darkYellow, outupSrccDir, ansi::off));
    fs::create_directory(outupSrccDir);
  }

  loadEnumDefinitions(headerPath);
  openFiles(outputDir);
  outputEnumHeader();
  outputEnumCpp();
  closeFiles();

  return 0;
}
