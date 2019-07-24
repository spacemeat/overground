#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <functional>
#include <cstdlib>
#include "ansiTerm.h"
#include "fmt/core.h"
#include "fmt/ostream.h"
#include "humon.h"
#include "utils.h"
#include "boiler.h"


using namespace std;
using namespace humon;
using namespace overground;


constexpr auto featurePreamble = "\
#ifndef {featureName}_GEN_H\n\
#define {featureName}_GEN_H\n\
\n\
#include <string>\n\
#include <vector>\n\
#include \"utils.h\"\n\
#include \"graphicsUtils.h\"\n\
#include \"enumParsers.h\"\n\
\n\
namespace overground\n\
{{\n\
";

constexpr auto featurePostamble = "\
}}\n\
\n\
#endif // #ifndef {featureName}_GEN_H\n\
";


constexpr auto featureCppPreamble = "\
#include \"{featureHeader}\"\n\
\n\
using namespace overground;\n\
using namespace humon;\n\
using namespace std;\n\
\n\
\n\
";


struct memberTypeDef
{
  string name;
  vector<memberTypeDef> subTypes;
};


ostream & operator << (ostream & s, memberTypeDef const & rhs)
{
  s << rhs.name;
  if (rhs.subTypes.size() > 0)
  {
    s << '<';
    for (int i = 0; i < (int) rhs.subTypes.size(); ++i)
    {
      s << rhs.subTypes[i];
      if (i < (int) rhs.subTypes.size() - 1)
        { s << ", "; }
    }
    s << '>';
  }
  return s;
}

struct memberDef
{
  string name;
  memberTypeDef type;
  string elementType;
  int size;
  string def;
};

struct structDef
{
  string name;
  unordered_map<string, size_t> memberDefsKeys;
  vector<memberDef> memberDefs;
  bool suppressDefinition = false;
};

struct featureDef
{
  string name;
  unordered_map<string, size_t> structDefsKeys;
  vector<structDef> structDefs;
};

map <string, size_t> featuresKeys;
vector<featureDef> features;
map <string, ofstream> featureHeaderFiles;
map <string, ofstream> featureCppFiles;


string resolveStdAliases(string_view type)
{
  stringstream ss;

  if (type == "string") { return "std::string"; }
  if (type == "array") { return "std::array"; }
  if (type == "vector") { return "std::vector"; }
  if (type == "pair") { return "std::pair"; }
  return string(type);
}

memberTypeDef resolveType(string_view member)
{
  memberTypeDef def;
  stack<memberTypeDef *> pdefs;
  pdefs.push(& def);

  string * pname = & def.name;

  for (auto it = begin(member); it != end(member); ++it)
  {
    if ((*it >= 'A' && *it <= 'Z') ||
        (*it >= 'a' && *it <= 'z') ||
        (*it >= '0' && *it <= '9') ||
        *it == ':' || *it == ' ' || *it == '_')
    {
      if (*it == ' ' && pname->size() == 0)
        { continue; }
      (*pname).push_back(*it);
    }
    else
    {
      *pname = resolveStdAliases(*pname);
      if (*it == '<')
      {
        pdefs.top()->subTypes.emplace_back();
        pdefs.push(& pdefs.top()->subTypes.back());
        pname = & pdefs.top()->name;
      }
      else if (*it == ',')
      {
        pdefs.pop();
        pdefs.top()->subTypes.emplace_back();
        pdefs.push(& pdefs.top()->subTypes.back());
        pname = & pdefs.top()->name;
      }
      else if (*it == '>')
      {
        pdefs.pop();
        pname = & pdefs.top()->name;
      }
    }
  }

  *pname = resolveStdAliases(*pname);

  return def;
}


set<string> loadFromString;

void markStringLoads(memberTypeDef const & mtd)
{
  if (auto const vk = "vk::"sv; 
      equal(vk.begin(), vk.end(), mtd.name.begin()))
    { loadFromString.insert(mtd.name); }
  
  for (auto const mtdch: mtd.subTypes)
    { markStringLoads(mtdch); }
}


structDef * findStructDef(string_view rhs)
{
  for (auto & [_, idx] : featuresKeys)
  {
    auto & feature = features[idx];
    for (auto & [structName, idx] : feature.structDefsKeys)
    {
      auto & structDef = feature.structDefs[idx];
      if (structName == rhs)
        { return & structDef; }
    }
  }

  return nullptr;
}

void parseDefsFile(path_t const & path)
{
  logFn();

  auto nodePtr = loadHumonDataFromFile(path);
  auto & node = *nodePtr;

  auto & def = node / "defs";
  for (size_t i = 0; i < def.size(); ++i)
  {
    auto & featureName = def.keyAt(i);
    auto & structCollectionNode = def / featureName;

    if (featureName == "@loadFromString")
    {
      for (size_t j = 0; j < structCollectionNode.size(); ++j)
      {
        loadFromString.emplace(structCollectionNode / j);
      }

      continue; 
    }

    features.emplace_back();
    featureDef & feature = features.back();
    feature.name = featureName;
    featuresKeys.insert_or_assign(featureName, features.size() - 1);

    log(0, fmt::format("Feature {}{}.{}",
      ansi::lightBlue, featureName, ansi::off));

    for (size_t j = 0; j < structCollectionNode.size(); ++j)
    {
      auto & structName = structCollectionNode.keyAt(j);
      auto & structNode = structCollectionNode / structName;

      feature.structDefs.emplace_back();
      structDef & struDef = feature.structDefs.back();
      struDef.name = structName;
      feature.structDefsKeys.insert_or_assign(structName, feature.structDefs.size() - 1);
      log(0, fmt::format("  struct {}{}.{}",
        ansi::lightCyan, structName, ansi::off));

      for (size_t k = 0; k < structNode.size(); ++k)
      {
        struDef.memberDefs.emplace_back();
        memberDef & member = struDef.memberDefs.back();
        member.name = structNode.keyAt(k);
        struDef.memberDefsKeys.insert_or_assign(member.name, struDef.memberDefs.size() - 1);
        log(0, fmt::format("    member {}{}.{}",
          ansi::lightMagenta, member.name, ansi::off));
        
        auto & memberNode = structNode / member.name;
        if (memberNode % "type")
        {
          member.type = resolveType(string(memberNode / "type"));
          markStringLoads(member.type);
        }
        member.def = (memberNode % "def") ? string(memberNode / "def") : "";
      }
    }
  }

  for (auto & lfs : loadFromString)
  {
    log(0, fmt::format("Enum-like value: {}{}{}",
      ansi::lightMagenta, lfs, ansi::off));
  }
}


static void openFiles(path_t const & dir)
{
  logFn();

  for (auto & [featureName, fidx] : featuresKeys)
  {
    // headers
    auto featureFile = featureName + "-gen.h";
    auto featurePath = path_t(dir).append("inc").append(featureFile);
    log(0, fmt::format("Generating {}{}.{}",
      ansi::lightBlue, featurePath, ansi::off));

    auto & ofs = featureHeaderFiles[featureName];
    ofs.open(featurePath);
    ofs << fmt::format(featurePreamble, 
      fmt::arg("featureName", featureName));

    // srcs
    auto featureCppFile = featureName + "-gen.cpp";
    auto featureCppPath = path_t(dir).append("src").append(featureCppFile);
    log(0, fmt::format("Generating {}{}.{}",
      ansi::lightBlue, featureCppPath, ansi::off));

    auto & ofsCpp = featureCppFiles[featureName];
    ofsCpp.open(featureCppPath);
    ofsCpp << fmt::format(featureCppPreamble, 
      fmt::arg("featureName", featureName),
      fmt::arg("featureHeader", featureFile));
  }
}


static void closeFiles()
{
  for (auto & [featureName, _] : featuresKeys)
  {
    auto & ofs = featureHeaderFiles[featureName];

    ofs << fmt::format(featurePostamble,
      fmt::arg("featureName", featureName));
  }
}


void outputStructDefs(structDef const & stru, ofstream & ofs)
{
  logFn();

  if (stru.suppressDefinition)
    { return; }

  auto & structName = stru.name;
  ofs << fmt::format("  struct {}\n  {{\n", structName);

  for (auto & member : stru.memberDefs)
  {
    auto memberType = fmt::format("{}", member.type);
    auto defaultValue = (member.def == "") ? "" : (" = " + member.def);

    ofs << fmt::format("    {} {}{};\n", memberType, member.name, defaultValue);
  }

  ofs << "  };\n\n";

  ofs << fmt::format("\
  void importPod(\n\
    humon::HuNode const & src, {structName} & dest);\n\
\n\
  void importPod(\n\
    std::vector<uint8_t> const & src, {structName} & dest);\n\
\n\
  void exportPod({structName} const & src, \n\
    humon::HuNode & dest, int depth);\n\
\n\
  void exportPod(\n\
    {structName} const & src, std::vector<uint8_t> & dest);\n\
\n\
  std::string print({structName} const & src, int depth = 0);\n\
\n\
  std::ostream & operator << (std::ostream & stream, {structName} const & src);\n\
\n\
\n\
",
    fmt::arg("structName", stru.name));
}

constexpr auto importPreamble = "\
void overground::importPod(\n\
  humon::HuNode const & src, {structName} & dest)\n\
{{\n\
";

void outputImportFromHumon(structDef const & stru, ofstream & ofs)
{
  logFn();

  ofs << fmt::format(importPreamble, 
    fmt::arg("structName", stru.name));

  for (auto & member : stru.memberDefs)
  {
    auto & memberName = member.name;
    ofs << fmt::format("\
  if (src % \"{memberName}\")\n\
  {{\n\
    auto & src0 = src / \"{memberName}\";\n\
    {memberType} dst0;\n",
        fmt::arg("memberName", memberName),
        fmt::arg("memberType", member.type));
    
    // recursive lambda
    const auto fn = [&](memberTypeDef const & mtd, int depth, string_view lvalue, string_view src)->void
    {
      auto fn_int = [&](memberTypeDef const & mtd, int depth, string_view lvalue, string_view src, auto & fn_ref)->void
      {
        bool isRoot = depth == 1;

        if (mtd.name == "std::vector")
        {
          auto & mtda = mtd.subTypes[0];
          ofs << fmt::format("\
{indent}for (size_t i{prevDepth} = 0; i{prevDepth} < {src}.size(); ++i{prevDepth})\n\
{indent}{{\n\
{indent}  auto & src{depth} = {src} / i{prevDepth};\n\
{indent}  {lvalueType} dst{depth};\n",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("lvalueType", mtda),
            fmt::arg("depth", depth),
            fmt::arg("prevDepth", depth - 1),
            fmt::arg("src", src));

          fn_ref(mtd.subTypes[0], depth + 1, fmt::format("dst{}", depth), fmt::format("src{}", depth), fn_ref);

          ofs << fmt::format("\
{indent}  {lvalue}.push_back(std::move(dst{depth}));\n\
{indent}}}\n\
",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("prevDepth", depth - 1),
            fmt::arg("depth", depth),
            fmt::arg("lvalue", lvalue));
        }

        else if (mtd.name == "std::array")
        {
          auto & mtda = mtd.subTypes[0];
          auto len = std::atol(mtd.subTypes[1].name.c_str());
          ofs << fmt::format("\
{indent}for (size_t i{prevDepth} = 0; i{prevDepth} < {len}; ++i{prevDepth})\n\
{indent}{{\n\
{indent}  auto & src{depth} = {src} / i{prevDepth};\n\
{indent}  {lvalueType} dst{depth};\n",
              fmt::arg("indent", string(2 + 2 * depth, ' ')),
              fmt::arg("len", len),
              fmt::arg("lvalueType", mtda),
              fmt::arg("depth", depth),
              fmt::arg("prevDepth", depth - 1),
              fmt::arg("src", src));

            fn_ref(mtd.subTypes[0], depth + 1, fmt::format("dst{}", depth), fmt::format("src{}", depth), fn_ref);

            ofs << fmt::format("\
{indent}  {lvalue}[i{prevDepth}] = std::move(dst{depth});\n\
{indent}}}\n\
",
              fmt::arg("indent", string(2 + 2 * depth, ' ')),
              fmt::arg("prevDepth", depth - 1),
              fmt::arg("depth", depth),
              fmt::arg("lvalue", lvalue));
          }

          else if (mtd.name == "std::pair")
          {
            auto & mtda = mtd.subTypes[0];
            ofs << fmt::format("\
{indent}{lvalueType} dst{depth}a;\n\
{indent}{{\n\
{indent}  auto & src{depth}a = {src} / 0;\n",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("lvalueType", mtda),
            fmt::arg("depth", depth),
            fmt::arg("src", src),
            fmt::arg("prevDepth", depth - 1));

          fn_ref(mtda, depth + 1, fmt::format("dst{}a", depth), fmt::format("src{}a", depth), fn_ref);

          ofs << fmt::format("{indent}}}\n",
            fmt::arg("indent", string(2 + 2 * depth, ' ')));

          auto & mtdb = mtd.subTypes[1];
          ofs << fmt::format("\
{indent}{lvalueType} dst{depth}b;\n\
{indent}{{\n\
{indent}  auto & src{depth}b = {src} / 1;\n",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("lvalueType", mtdb),
            fmt::arg("depth", depth),
            fmt::arg("src", src),
            fmt::arg("prevDepth", depth - 1));

          fn_ref(mtdb, depth + 1, fmt::format("dst{}b", depth), fmt::format("src{}b", depth), fn_ref);

          ofs << fmt::format("{indent}}}\n",
            fmt::arg("indent", string(2 + 2 * depth, ' ')));
          
          ofs << fmt::format("\
{indent}{lvalue} = std::make_pair(\n\
{indent}  std::move(dst{depth}a), std::move(dst{depth}b));\n",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("prevDepth", depth - 1),
            fmt::arg("depth", depth),
            fmt::arg("lvalue", lvalue));
        }

        // if it's not a container type, is it a
        // struct type that is defined in here?
        else if (auto psd = findStructDef(mtd.name);
          psd != nullptr)
        {
          ofs << fmt::format("\
{indent}importPod({src}, {lvalue});\n",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("src", src),
            fmt::arg("lvalue", lvalue));
        }

        // otherwise, treat the node as a simple type, with concessions for values that we define @loadFromString.
        else
        {
          if (loadFromString.find(mtd.name) != loadFromString.end())
          {
            ofs << fmt::format("\
{indent}{lvalue} = fromString<{leafType}>((std::string) {src}); // leaf\n",
              fmt::arg("indent", string(2 + 2 * depth, ' ')),
              fmt::arg("src", src),
              fmt::arg("leafType", mtd.name),
              fmt::arg("lvalue", lvalue));
          }
          else
          {
            ofs << fmt::format("\
{indent}{lvalue} = ({leafType}) {src}; // leaf\n",
              fmt::arg("indent", string(2 + 2 * depth, ' ')),
              fmt::arg("src", src),
              fmt::arg("leafType", mtd.name),
              fmt::arg("lvalue", lvalue));
          }
        }

        if (isRoot)
        {
          ofs << fmt::format("\
    dest.{memberName} = std::move(dst0);\n",
            fmt::arg("memberName", memberName));
        }
      };
      fn_int(mtd, depth, lvalue, src, fn_int);
    };

    fn(member.type, 1, "dst0", "src0");
    ofs << "  }\n";
  }

  ofs << "}\n";
}


void outputImportFromBinary(structDef const & stru, ofstream & ofs)
{
  logFn();

  log(thId, logTags::warn, "This operation has not been implemented yet.");

  ofs << fmt::format("\
void overground::importPod(\n\
std::vector<uint8_t> const & src, {structName} & dest)\n\
{{\n", 
    fmt::arg("structName", stru.name));

  ofs << "\
  // NOTE: This operation has not been implemented yet.\n";

  ofs << fmt::format("}}\n\n\n");
}


void outputExportToHumon(structDef const & stru, ofstream & ofs)
{
  logFn();

  log(0, logTags::warn, "This operation has not been implemented yet.");

  ofs << fmt::format("\
void overground::exportPod({structName} const & src, \n\
humon::HuNode & dest, int depth)\n\
{{\n", 
    fmt::arg("structName", stru.name));

  ofs << "\
  log(0, logTags::warn, \"This operation has not been implemented yet.\");\n\
\n\
  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.\n";

  ofs << fmt::format("}}\n\n\n");
}


void outputExportToBinary(structDef const & stru, ofstream & ofs)
{
  logFn();

  log(thId, logTags::warn, "This operation has not been implemented yet.");

  ofs << fmt::format("\
void overground::exportPod(\n\
{structName} const & src, std::vector<uint8_t> & dest)\n\
{{\n", 
    fmt::arg("structName", stru.name));

  ofs << "\
  log(0, logTags::warn, \"This operation has not been implemented yet.\");\n\
\n\
  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.\n";

  ofs << fmt::format("}}\n\n\n");
}


void outputPrint(structDef const & stru, ofstream & ofs)
{
  logFn();

  ofs << fmt::format("\
std::string overground::print(\n\
{structName} const & src, int depth)\n\
{{\n\
  string prevIndentIn(depth * 2, ' ');\n\
  string indentIn(2 + depth * 2, ' ');\n\
  std::ostringstream ss;\n\
  ss << \"{{\";\n", 
    fmt::arg("structName", stru.name));

  for (auto & member : stru.memberDefs)
  {
    auto & memberName = member.name;

    // recursive lambda
    const auto fn = [&](memberTypeDef const & mtd, string_view memberName, string_view srcName, int depth)->void
    {
      auto fn_int = [&](memberTypeDef const & mtd, string_view memberName, string_view srcName, int depth, auto & fn_ref)->void
      {
        string indentIn = "\"" + string(2 + 2 * depth, ' ') + "\"";
        string prevIndentIn = "\"" + string(0 + 2 * depth, ' ') + "\"";
        string indent (2 + 2 * depth, ' ');

        if (depth == 0)
        {
          ofs << fmt::format("\
{indent}ss << \"\\n\" << indentIn << \"{srcName}: \";\n", 
            fmt::arg("indent", indent),
            fmt::arg("srcName", srcName));
        }
        else if(mtd.subTypes.size() == 0)
        {
          ofs << fmt::format("\
{indent}ss << \"\\n\" << indentIn;\n", 
            fmt::arg("indent", indent));
        }

        // vector | array
        if (mtd.name == "std::vector" ||
            mtd.name == "std::array")
        {
          ofs << fmt::format("\
{indent}ss << \"[\";\n\
{indent}for (size_t i{depth} = 0; i{depth} < {memberName}.size(); ++i{depth})\n\
{indent}{{\n\
{indent}  depth += 1;\n\
{indent}  string prevIndentIn(depth * 2, ' ');\n\
{indent}  string indentIn(2 + depth * 2, ' ');\n\
{indent}  {subType} const & src{depth} = {memberName}[i{depth}];\n",
            fmt::arg("indent", indent),
            fmt::arg("depth", depth),
            fmt::arg("subType", mtd.subTypes[0]),
            fmt::arg("memberName", memberName));

          fn_ref(mtd.subTypes[0], (string_view) fmt::format("src{}", depth), (string_view) fmt::format("src{}", depth), depth + 1, fn_ref);

          ofs << fmt::format("\
{indent}  depth -= 1;\n\
{indent}}}\n\
{indent}ss << \"\\n\" << indentIn << \"]\";\n", 
            fmt::arg("indent", indent));
        }

        // pair
        else if (mtd.name == "std::pair")
        {
          ofs << fmt::format("\
{indent}{{\n\
{indent}  ss << \"[\";\n\
{indent}  depth += 1;\n\
{indent}  string prevIndentIn(depth * 2, ' ');\n\
{indent}  string indentIn(2 + depth * 2, ' ');\n\
{indent}  {subType} const & src{depth} = {memberName}.first;\n",
            fmt::arg("indent", indent),
            fmt::arg("subType", mtd.subTypes[0]),
            fmt::arg("depth", depth),
            fmt::arg("memberName", memberName));

          fn_ref(mtd.subTypes[0], (string_view) fmt::format("src{}", depth), (string_view) fmt::format("src{}", depth), depth + 1, fn_ref);

          ofs << fmt::format("\
{indent}  ss << indentIn;\n\
{indent}  depth -= 1;\n\
{indent}}}\n\
{indent}{{\n\
{indent}  depth += 1;\n\
{indent}  string prevIndentIn(depth * 2, ' ');\n\
{indent}  string indentIn(2 + depth * 2, ' ');\n\
{indent}  {subType} const & src{depth} = {memberName}.second;\n",
            fmt::arg("indent", indent),
            fmt::arg("subType", mtd.subTypes[1]),
            fmt::arg("depth", depth),
            fmt::arg("memberName", memberName));

          fn_ref(mtd.subTypes[1], (string_view) fmt::format("src{}", depth), (string_view) fmt::format("src{}", depth), depth + 1, fn_ref);

          ofs << fmt::format("\
{indent}depth -= 1;\n\
{indent}ss << \"\\n\" << prevIndentIn << \"]\";\n\
{indent}}}\n",
            fmt::arg("indent", indent));
        }

        // nested struct
        else if (auto pstru = findStructDef(mtd.name);
          pstru != nullptr)
        {
          ofs << fmt::format("\
{indent}ss << print({memberName}, depth + 1);\n",
            fmt::arg("indent", indent),
            fmt::arg("memberName", memberName));
        }

        // enumish
        else if (loadFromString.find(mtd.name) !=
          loadFromString.end())
        {
          ofs << fmt::format("\
{indent}ss << to_string({src});\n",
            fmt::arg("indent", indent),
            fmt::arg("src", memberName));
        }

        else
        {
          ofs << fmt::format("\
{indent}ss << ({src});\n",
            fmt::arg("indent", indent),
            fmt::arg("src", memberName));
        }
      };

      fn_int(mtd, memberName, srcName, depth, fn_int);
    };

    fn(member.type, "src." + memberName, memberName, 0);
  }

  ofs << fmt::format("\
  ss << \"\\n\" << prevIndentIn << \"}}\";\n\
  return ss.str();\n\
}}\n\
\n\
\n\
ostream & overground::operator << (ostream & stream, {structType} const & rhs)\n\
{{\n\
  stream << print(rhs);\n\
  return stream;\n\
}}\n\
\n\n",
    fmt::arg("structType", stru.name));
}


int overground::assetsMain(path_t const & defsPath, path_t const & outputDir)
{
  log(0, fmt::format("\
{}Making boilerplate code from definitions in {}.{}\n\
Output base: {}{}{}",
    ansi::lightCyan, defsPath, ansi::off,
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

  parseDefsFile(defsPath);
  openFiles(outputDir);

  for (auto & feature : features)
  {
    auto & featureName = feature.name;
    auto & ofsH = featureHeaderFiles[featureName];
    auto & ofsC = featureCppFiles[featureName];

    for (auto & stru : feature.structDefs)
    {
      outputStructDefs(stru, ofsH);
      outputImportFromHumon(stru, ofsC);
      outputImportFromBinary(stru, ofsC);
      outputExportToHumon(stru, ofsC);
      outputExportToBinary(stru, ofsC);
      outputPrint(stru, ofsC);
    }
  }

  closeFiles();

  return 0;
}
