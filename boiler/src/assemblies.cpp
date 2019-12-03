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


constexpr auto nsPreamble = 
R"(#ifndef {nsName}_GEN_H
#define {nsName}_GEN_H

#include <string>
#include <vector>
#include <optional>
#include <variant>
#include <unordered_set>
#include "utils.h"
#include "graphicsUtils.h"
#include "enumParsers.h"
)";

constexpr auto nsPostamble = 
R"(  }}
}}

#endif // #ifndef {nsName}_GEN_H
)";


constexpr auto nsCppPreamble = 
R"(#include "{nsHeader}"

using namespace overground;
using namespace overground::{nsName};
using namespace humon;
using namespace std;

)";


struct memberTypeDef
{
  string name;
  vector<memberTypeDef> subTypes;
};


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
  vector<string> requiresFeatures;
  string basedOn;
  bool suppressDefinition = false;
};

struct nsDef
{
  string name;
  vector<string> uses;
  unordered_map<string, size_t> structDefsKeys;
  vector<structDef> structDefs;
};

string topNamespace;
map <string, size_t> nssKeys;
vector<nsDef> nss;
map <string, ofstream> nsHeaderFiles;
map <string, ofstream> nsCppFiles;
map <string, ofstream> pluginCppFiles;
map <string, vector<string>, std::less<>> plugins;
ofstream plHeaderFile;

void outputHeaderHeader(string_view nsName);
structDef * findStructDef(string_view rhs);


ostream & operator << (ostream & s, memberTypeDef const & rhs)
{
  if (findStructDef(rhs.name))
    { s << rhs.name << "_t"; }
  else
    { s << rhs.name; }
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


string resolveStdAliases(string_view type)
{
  if (type == "string") { return "std::string"; }
  if (type == "array") { return "std::array"; }
  if (type == "vector") { return "std::vector"; }
  if (type == "pair") { return "std::pair"; }
  if (type == "optional") { return "std::optional"; }
  if (type == "variant") { return "std::variant"; }
  if (type == "unique_ptr") { return "std::unique_ptr"; }
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
      if (*it == '<')
      {
        *pname = resolveStdAliases(*pname);
        pdefs.top()->subTypes.emplace_back();
        pdefs.push(& pdefs.top()->subTypes.back());
        pname = & pdefs.top()->name;
      }
      else if (*it == ',')
      {
        *pname = resolveStdAliases(*pname);
        pdefs.pop();
        pdefs.top()->subTypes.emplace_back();
        pdefs.push(& pdefs.top()->subTypes.back());
        pname = & pdefs.top()->name;
      }
      else if (*it == '>')
      {
          *pname = resolveStdAliases(*pname);
        pdefs.pop();
        pname = & pdefs.top()->name;
      }
    }
  }

  *pname = resolveStdAliases(*pname);

  return def;
}


void resolvePluginMemberType(memberTypeDef & memberParentTypeDef, memberTypeDef & memberChildTypeDef, size_t childIndex)
{
  if (memberParentTypeDef.name == "std::variant" && 
      memberChildTypeDef.name == "plugins")
  {
    auto pluginType = memberChildTypeDef.subTypes[0].name;
    auto it = memberParentTypeDef.subTypes.begin() + childIndex;
    memberParentTypeDef.subTypes.erase(it);

    for (auto & pluginName : plugins[pluginType])
    {
      auto it = memberParentTypeDef.subTypes.begin() + childIndex;
      memberTypeDef newMtd { pluginName, {} };
      memberParentTypeDef.subTypes.insert(it, newMtd);
      childIndex += 1;
    }
  }

  if (memberChildTypeDef.subTypes.size() > 0)
  {
    size_t childChildIndex = 0;
    for (auto & memberChildChildTypeDef : memberChildTypeDef.subTypes)
    {
      resolvePluginMemberType(memberChildTypeDef, memberChildChildTypeDef, childChildIndex);
      childChildIndex += 1;
    }
  }
}


void resolvePluginTypes()
{
  for (auto & ns : nss)
  {
    for (auto & structDef : ns.structDefs)
    {
      for (auto & memberDef : structDef.memberDefs)
      {
        auto & memberParentTypeDef = memberDef.type;

        log(0, logTags::verb, fmt::format("FROM: {}/{}/{}: {}", ns.name, structDef.name, memberDef.name, memberParentTypeDef));

        size_t idx = 0;
        for (auto & memberChildTypeDef : memberParentTypeDef.subTypes)
        {
          resolvePluginMemberType(memberParentTypeDef, memberChildTypeDef, idx);
          idx += 1;
        }

        log(0, logTags::verb, fmt::format("  TO: {}/{}/{}: {}", ns.name, structDef.name, memberDef.name, memberParentTypeDef));
      }
    }
  }
}


set<string> enumFromString;

void markStringLoads(memberTypeDef const & mtd)
{
  if (auto const vk = "vk::"sv; 
      equal(vk.begin(), vk.end(), mtd.name.begin()))
    { enumFromString.insert(mtd.name); }
  
  for (auto const mtdch: mtd.subTypes)
    { markStringLoads(mtdch); }
}


structDef * findStructDef(string_view rhs)
{
  for (auto & [nsName, idx] : nssKeys)
  {
    auto & ns = nss[idx];
    for (auto & [structName, idx] : ns.structDefsKeys)
    {
      auto & structDef = ns.structDefs[idx];
      if (structName == rhs || structName == rhs)
        { return & structDef; }

      string targetStructName = fmt::format("{}::{}", nsName, structName);
      if (targetStructName == rhs)
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

  auto & enumFromStringNode = node / "enumFromString";
  for (size_t i = 0; i < enumFromStringNode.size(); ++i)
  {
    string efs = enumFromStringNode / i;
    enumFromString.insert(efs);
  }

  topNamespace = (string) (node / "topNamespace");

  auto & def = node / "namespaces";
  for (size_t i = 0; i < def.size(); ++i)
  {
    auto & nsName = def.keyAt(i);
    auto & structCollectionNode = def / nsName;

    nss.emplace_back();
    nsDef & ns = nss.back();
    ns.name = nsName;
    nssKeys.insert_or_assign(nsName, nss.size() - 1);

    log(0, fmt::format("Namespace {}{}.{}",
      ansi::lightBlue, nsName, ansi::off));

    for (size_t j = 0; j < structCollectionNode.size(); ++j)
    {
      auto & structName = structCollectionNode.keyAt(j);
      auto & structNode = structCollectionNode / structName;

      if (structName == "uses")
      {
        for (size_t k = 0; k < structNode.size(); ++k)
        {
          auto usesName = (string)(structNode / k);
          ns.uses.push_back(usesName);
        }

        continue;
      }

      ns.structDefs.emplace_back();
      structDef & struDef = ns.structDefs.back();
      struDef.name = structName;
      ns.structDefsKeys.insert_or_assign(structName, ns.structDefs.size() - 1);
      log(0, fmt::format("  struct {}{}.{}",
        ansi::lightCyan, structName, ansi::off));

      for (size_t k = 0; k < structNode.size(); ++k)
      {
        auto const & key = structNode.keyAt(k);
        if (key == "requiresFeatures")
        {
          auto & listNode = structNode / key;
          for (size_t l = 0; l < listNode.size(); ++l)
          {
            struDef.requiresFeatures.emplace_back(string(listNode / l));
          }
        }
        else if (key == "plugin")
        {
          if (auto it = plugins.find(string(structNode / key)); 
              it != plugins.end())
          {
            it->second.push_back(structName);
          }
          else
          {
            plugins.emplace(structNode / key, vector {structName} );
          }
        }
        else
        {
          struDef.memberDefs.emplace_back();
          memberDef & member = struDef.memberDefs.back();
          member.name = key;
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
  }

  resolvePluginTypes();

  for (auto & lfs : enumFromString)
  {
    log(0, fmt::format("Enum-like value: {}{}{}",
      ansi::lightMagenta, lfs, ansi::off));
  }
}


static void openFiles(path_t const & podsDir, path_t const & pluginCentralDir)
{
  logFn();

  for (auto & [nsName, fidx] : nssKeys)
  {
    // headers
    auto nsFile = nsName + "-gen.h";
    auto nsPath = path_t(podsDir).append("inc").append(nsFile);
    log(0, fmt::format("Generating {}{}.{}",
      ansi::lightBlue, nsPath, ansi::off));

    auto & ofs = nsHeaderFiles[nsName];
    ofs.open(nsPath);
    outputHeaderHeader(nsName);

    // srcs
    auto nsCppFile = nsName + "-gen.cpp";
    auto nsCppPath = path_t(podsDir).append("src").append(nsCppFile);
    log(0, fmt::format("Generating {}{}.{}",
      ansi::lightBlue, nsCppPath, ansi::off));

    auto & ofsCpp = nsCppFiles[nsName];
    ofsCpp.open(nsCppPath);
    ofsCpp << fmt::format(nsCppPreamble, 
      fmt::arg("nsName", nsName),
      fmt::arg("nsHeader", nsFile));
  }

  // pluginzz
  auto pluginHeaderPath = path_t(pluginCentralDir).append("inc").append("plugins-gen.h");
  log(0, fmt::format("Generating {}{}.{}",
    ansi::lightBlue, pluginHeaderPath, ansi::off));
  plHeaderFile.open(pluginHeaderPath);

  for (auto & [pluginTypeName, _] : plugins)
  {
    auto pluginCentralCppFile = pluginTypeName + "-gen.cpp";
    auto pluginCentralPath = path_t(pluginCentralDir).append("src").append(pluginCentralCppFile);
    log(0, fmt::format("Generating {}{}.{}",
      ansi::lightBlue, pluginCentralPath, ansi::off));

    auto & ofsCpp = pluginCppFiles[pluginTypeName];
    ofsCpp.open(pluginCentralPath);
  }
}


static void closeFiles()
{
  for (auto & [nsName, _] : nssKeys)
  {
    auto & ofs = nsHeaderFiles[nsName];

    ofs << fmt::format(nsPostamble,
      fmt::arg("nsName", nsName));
  }
}


void outputHeaderHeader(string_view nsName)
{
  auto & ofs = nsHeaderFiles[(string)nsName];
  ofs << fmt::format(nsPreamble, 
    fmt::arg("nsName", nsName));
  
  auto & ns = nss[nssKeys[(string)nsName]];
  for (auto const & usingNs: ns.uses)
  {
    ofs << fmt::format(
R"(#include "{usingNs}-gen.h"
)", 
      fmt::arg("usingNs", usingNs));
  }

  ofs << fmt::format(
R"(
namespace {topNamespace}
{{
  namespace {nsName}
  {{
)",
    fmt::arg("topNamespace", topNamespace),fmt::arg("nsName", nsName)); 
}


void outputStructDefs(structDef const & stru, ofstream & ofs)
{
  logFn();

  if (stru.suppressDefinition)
    { return; }

  auto & structName = stru.name;

  ofs << fmt::format(
R"(    // {} things

)", structName);

  ofs << fmt::format(
R"(    struct {}_t
    {{
)", structName);

  for (auto & member : stru.memberDefs)
  {
    auto memberType = fmt::format("{}", member.type);
    auto defaultValue = (member.def == "") ? "" : (fmt::format(" = ({}){}", memberType, member.def));

    ofs << fmt::format(
R"(      {} {}{};
)", memberType, member.name, defaultValue);
  }

  ofs << "    };\n";

  ofs << fmt::format(
R"(
    void importPod(
      humon::HuNode const & src, {structName}_t & dest);

    void importPod(
      std::vector<uint8_t> const & src, {structName}_t & dest);

    void exportPod({structName}_t const & src, 
      humon::HuNode & dest, int depth);

    void exportPod(
      {structName}_t const & src, std::vector<uint8_t> & dest);

    std::string print({structName}_t const & src, int depth = 0);

    std::ostream & operator << (std::ostream & stream, {structName}_t const & src);

    enum class {structName}Members_e : int 
    {{
      none = 0,
)",
    fmt::arg("structName", stru.name));

  int i = 0;
  for (auto & member : stru.memberDefs)
  {
    ofs << fmt::format("      {} = 1 << {},\n", member.name, i);
    i += 1;
  }

  ofs << R"(      all = )";
  bool tail = false;
  for (auto & member : stru.memberDefs)
  {
    if (tail)
      { ofs << " | "; }

    tail = true;
    ofs << member.name;
  }

  ofs << fmt::format(
R"(
    }};

    inline bool operator == ({structName}_t const & lhs, {structName}_t const & rhs) noexcept
    {{
      return
)", 
    fmt::arg("structName", structName));

  bool first = true;
  for (auto & member : stru.memberDefs)
  {
    if (first)
    {
      first = false;
      ofs << fmt::format(
R"(        lhs.{memberName} == rhs.{memberName})",
      fmt::arg("memberName", member.name));
    }
    else
    {
      ofs << fmt::format(
R"( &&
        lhs.{memberName} == rhs.{memberName})",
      fmt::arg("memberName", member.name));
    }
  }

  ofs << fmt::format(
R"(;
    }};

    inline bool operator != ({structName}_t const & lhs, {structName}_t const & rhs) noexcept
    {{
      return ! (lhs == rhs);
    }};

    struct {structName}Diffs_t
    {{
      {structName}Members_e diffs;
)",
    fmt::arg("structName", stru.name));
  
  for (auto & member : stru.memberDefs)
  {
    if (findStructDef(member.type.name) != nullptr)
    {
      ofs << fmt::format(
R"(      {memberType}Diffs_t {memberName};
)",
        fmt::arg("structName", stru.name),
        fmt::arg("memberType", member.type.name),
        fmt::arg("memberName", member.name));
    }
    else if (member.type.name == "std::array" || member.type.name == "std::vector")
    {
      if (findStructDef(member.type.subTypes[0].name))
      {
        ofs << fmt::format(
R"(      std::unordered_map<size_t, {memberSubType}Diffs_t> {memberName}Diffs;
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberSubType", member.type.subTypes[0].name),
          fmt::arg("memberName", member.name));
      }
      else if (member.type.subTypes[0].name == "std::unique_ptr")
      {
        if (findStructDef(member.type.subTypes[0].subTypes[0].name))
        {
          ofs << fmt::format(
  R"(      std::unordered_map<std::string, {memberSubType}Diffs_t> {memberName}Diffs;
  )",
            fmt::arg("structName", stru.name),
            fmt::arg("memberSubType", member.type.subTypes[0].subTypes[0].name),
            fmt::arg("memberName", member.name));
        }
      }
      else
      {
        ofs << fmt::format(
R"(      std::unordered_set<size_t> {memberName}Diffs;
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberName", member.name));
      }
    }
    else if (member.type.name == "stringDict")
    {
      if (findStructDef(member.type.subTypes[0].name))
      {
        ofs << fmt::format(
R"(      std::unordered_map<std::string, {memberSubType}Diffs_t> {memberName}Diffs;
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberSubType", member.type.subTypes[0].name),
          fmt::arg("memberName", member.name));
      }
      else if (member.type.subTypes[0].name == "std::unique_ptr")
      {
        if (findStructDef(member.type.subTypes[0].subTypes[0].name))
        {
          ofs << fmt::format(
  R"(      std::unordered_map<std::string, {memberSubType}Diffs_t> {memberName}Diffs;
  )",
            fmt::arg("structName", stru.name),
            fmt::arg("memberSubType", member.type.subTypes[0].subTypes[0].name),
            fmt::arg("memberName", member.name));
        }
      }
      else
      {
        ofs << fmt::format(
R"(      std::unordered_set<std::string> {memberName}Diffs;
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberName", member.name));
      }
    }
  }

  ofs << fmt::format(
R"(    }};

    inline bool doPodsDiffer(
      {structName}_t const & lhs,
      {structName}_t const & rhs,
      {structName}Diffs_t & {structName}) noexcept
    {{
)",
    fmt::arg("structName", stru.name));
  
  for (auto & member : stru.memberDefs)
  {
    ofs << fmt::format(
R"(      // diff member '{memberName}':
)",
      fmt::arg("memberName", member.name));

    if (member.type.name == "std::array")
    {
      ofs << fmt::format(
R"(      for (size_t i = 0; i < lhs.{memberName}.size(); ++i)
      {{
)",
        fmt::arg("structName", stru.name),
        fmt::arg("memberName", member.name));

      if (findStructDef(member.type.subTypes[0].name))
      {
        ofs << fmt::format(
R"(        {memberSubType}Diffs_t diffsEntry;
        if (doPodsDiffer(lhs.{memberName}[i], rhs.{memberName}[i], diffsEntry))
        {{
          {structName}.diffs |= {structName}Members_e::{memberName};
          {structName}.{memberName}Diffs.insert_or_assign(i, diffsEntry);
        }}
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberSubType", member.type.subTypes[0].name),
          fmt::arg("memberName", member.name));
      }
      else
      {
        ofs << fmt::format(
R"(        if (lhs.{memberName}[i] != rhs.{memberName}[i])
        {{
          {structName}.diffs |= {structName}Members_e::{memberName};
          {structName}.{memberName}Diffs.insert(i);
        }}
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberName", member.name));
      }

      ofs << 
R"(      }
)";
    }
    else if (member.type.name == "std::vector")
    {
      if (findStructDef(member.type.subTypes[0].name))
      {
        ofs << fmt::format(
R"(      {{
        auto [mn, mx] = std::minmax(lhs.{memberName}.size(), rhs.{memberName}.size());
        for (size_t i = 0; i < mn; ++i)
        {{
          {memberSubType}Diffs_t diffsEntry;
          if (doPodsDiffer(lhs.{memberName}[i], rhs.{memberName}[i], diffsEntry))
          {{
            {structName}.diffs |= {structName}Members_e::{memberName};
            {structName}.{memberName}Diffs.insert_or_assign(i, diffsEntry);
          }}
        }}
        for (size_t i = mn; i < mx; ++i)
        {{
          {memberSubType}Diffs_t diffsEntry = {{ .diffs = {memberSubType}Members_e::all }};
          {structName}.{memberName}Diffs.insert_or_assign(i, diffsEntry);
        }}
      }}
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberSubType", member.type.subTypes[0].name),
          fmt::arg("memberName", member.name));
      }
      else if (member.type.subTypes[0].name == "std::variant")
      {
        ofs << fmt::format(
R"(      {{
        auto [mn, mx] = std::minmax(lhs.{memberName}.size(), rhs.{memberName}.size());
        for (size_t i = 0; i < mn; ++i)
        {{
          if (lhs.{memberName}[i] != rhs.{memberName}[i])
          {{
            {structName}.diffs |= {structName}Members_e::{memberName};
            {structName}.{memberName}Diffs.insert(i);
          }}
        }}
        for (size_t i = mn; i < mx; ++i)
        {{
          {structName}.{memberName}Diffs.insert(i);
        }}
      }}
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberSubType", member.type.subTypes[0].name),
          fmt::arg("memberName", member.name));
      }
      else if (member.type.subTypes[0].name == "std::unique_ptr")
      {
        if (findStructDef(member.type.subTypes[0].subTypes[0].name))
        {
          ofs << fmt::format(
  R"(      {{
          auto [mn, mx] = std::minmax(lhs.{memberName}.size(), rhs.{memberName}.size());
          for (size_t i = 0; i < mn; ++i)
          {{
            {memberSubType}Diffs_t diffsEntry;
            if (! lhs.{memberName}[i] || ! rhs.{memberName}[i] ||
                doPodsDiffer(* lhs.{memberName}[i], * rhs.{memberName}[i], diffsEntry))
            {{
              {structName}.diffs |= {structName}Members_e::{memberName};
              {structName}.{memberName}Diffs.insert_or_assign(i, diffsEntry);
            }}
          }}
          for (size_t i = mn; i < mx; ++i)
          {{
            {memberSubType}Diffs_t diffsEntry = {{ .diffs = {memberSubType}Members_e::all }};
            {structName}.{memberName}Diffs.insert_or_assign(i, diffsEntry);
          }}
        }}
  )",
            fmt::arg("structName", stru.name),
            fmt::arg("memberSubType", member.type.subTypes[0].name),
            fmt::arg("memberName", member.name));
        }
      }
      else
      {
        ofs << fmt::format(
R"(      {{
        auto [mn, mx] = std::minmax(lhs.{memberName}.size(), rhs.{memberName}.size());
        for (size_t i = 0; i < mn; ++i)
        {{
          if (lhs.{memberName}[i] != rhs.{memberName}[i])
          {{
            {structName}.diffs |= {structName}Members_e::{memberName};
            {structName}.{memberName}Diffs.insert(i);
          }}
        }}
        for (size_t i = mn; i < mx; ++i)
        {{
          {structName}.{memberName}Diffs.insert(i);
        }}
      }}
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberName", member.name));
      }
    }
    else if (member.type.name == "stringDict")
    {
      if (findStructDef(member.type.subTypes[0].name))
      {
        ofs << fmt::format(
R"(      {{
        for (auto const & [lhsKey, lhsIdx] : lhs.{memberName}.keys)
        {{
          {memberSubType}Diffs_t diffsEntry;
          if (auto it = rhs.{memberName}.keys().find(lhsKey); it != rhs.{memberName}.keys().end())
          {{
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                doPodsDiffer(lhs.{memberName}[lhsIdx], rhs.{memberName}[rhsIdx], diffsEntry) == false)
              {{ continue; }}
          }}
          {structName}.diffs |= {structName}Members_e::{memberName};
          {structName}.{memberName}Diffs.insert_or_assign(lhsKey, diffsEntry);
        }}
        for (auto const & [rhsKey, rhsIdx] : rhs.{memberName}.keys())
        {{
          if (auto it = lhs.{memberName}.keys.find(rhsKey); it != lhs.{memberName}.keys.end())
            {{ continue; }}

          {memberSubType}Diffs_t diffsEntry = {{ .diffs = {memberSubType}Members_e::all }};
          {structName}.{memberName}Diffs.insert_or_assign(rhsKey, diffsEntry);
        }}
      }}
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberSubType", member.type.subTypes[0].name),
          fmt::arg("memberName", member.name));
      }
      else if (member.type.subTypes[0].name == "std::unique_ptr")
      {
        if (findStructDef(member.type.subTypes[0].subTypes[0].name))
        {
          ofs << fmt::format(
  R"(      {{
        for (auto const & [lhsKey, lhsIdx] : lhs.{memberName}.keys)
        {{
          {memberSubType}Diffs_t diffsEntry;
          if (auto it = rhs.{memberName}.keys().find(lhsKey); it != rhs.{memberName}.keys().end())
          {{
            auto const & [rhsKey, rhsIdx] = *it;
            if  ( lhsIdx == rhsIdx &&
                  ( lhs.{memberName}[lhsIdx] == nullptr && rhs.{memberName}[lhsIdx] == nullptr ||
                    ( lhs.{memberName}[lhsIdx] != nullptr && rhs.{memberName}[lhsIdx] != nullptr &&
                      doPodsDiffer(* lhs.{memberName}[lhsIdx], * rhs.{memberName}[rhsIdx], diffsEntry) == false
                    )
                  )
                )
                  {{ continue; }}
          }}
          {structName}.diffs |= {structName}Members_e::{memberName};
          {structName}.{memberName}Diffs.insert_or_assign(lhsKey, diffsEntry);
        }}
        for (auto const & [rhsKey, rhsIdx] : rhs.{memberName}.keys())
        {{
          if (auto it = lhs.{memberName}.keys.find(rhsKey); it != lhs.{memberName}.keys.end())
            {{ continue; }}

          {memberSubType}Diffs_t diffsEntry = {{ .diffs = {memberSubType}Members_e::all }};
          {structName}.{memberName}Diffs.insert_or_assign(rhsKey, diffsEntry);
        }}
      }}
  )",
            fmt::arg("structName", stru.name),
            fmt::arg("memberSubType", member.type.subTypes[0].name),
            fmt::arg("memberName", member.name));
        }
      }
      else
      {
        ofs << fmt::format(
R"(      {{
        for (auto const & [lhsKey, lhsIdx] : lhs.{memberName}.keys)
        {{
          if (auto it = rhs.{memberName}.keys().find(lhsKey); it != rhs.{memberName}.keys().end())
          {{
            auto const & [rhsKey, rhsIdx] = *it;
            if (lhsIdx == rhsIdx &&
                lhs.{memberName}[lhsIdx] == rhs.{memberName}[rhsIdx])
              {{ continue; }}
          }}
          {structName}.diffs |= {structName}Members_e::{memberName};
          {structName}.{memberName}Diffs.insert(lhsKey);
        }}
        for (auto const & [rhsKey, rhsIdx] : rhs.{memberName}.keys())
        {{
          if (auto it = lhs.{memberName}.keys.find(rhsKey); it != lhs.{memberName}.keys.end())
            {{ continue; }}
          {structName}.{memberName}Diffs.insert(rhsKey);
        }}
      }}
)",
          fmt::arg("structName", stru.name),
          fmt::arg("memberName", member.name));
      }
    }
    else if (findStructDef(member.type.name) != nullptr)
    {
      ofs << fmt::format(
R"(      if (doPodsDiffer(lhs.{memberName}, rhs.{memberName}, {structName}.{memberName}))
        {{ {structName}.diffs |= {structName}Members_e::{memberName}; }}
)",
        fmt::arg("structName", stru.name),
        fmt::arg("memberName", member.name));
    }
    else
    {
      ofs << fmt::format(
R"(      if (lhs.{memberName} != rhs.{memberName})
        {{ {structName}.diffs |= {structName}Members_e::{memberName}; }}
)",
        fmt::arg("structName", stru.name),
        fmt::arg("memberName", member.name));
    }
  }

  ofs << fmt::format(
R"(
      return {structName}.diffs != {structName}Members_e::none;
    }};

)",
    fmt::arg("structName", stru.name));
}


void outputPluginDefs(ofstream & ofs)
{
  ofs << 
R"(#ifndef PLUGINS_GEN_H
#define PLUGINS_GEN_H


#include <string_view>
)";

  for (auto & [pluginName, pluginTypes] : plugins)
  {
    for (auto & pluginType : pluginTypes)
    {
      ofs << fmt::format(
R"(#include "{}.{}.h"
)", pluginName, pluginType);
    }
  }

  ofs << 
R"(
namespace overground
{
)";

  for (auto & [pluginName, pluginTypes] : plugins)
  {
    ofs << fmt::format(
R"(  enum class {pluginName}PluginTypes_e
  {{
)",
      fmt::arg("pluginName", pluginName));

    for (auto & pluginType : pluginTypes)
    {
      ofs << fmt::format(
R"(    {},
)",
        fmt::arg("pluginType", pluginType));
    }

    ofs << fmt::format(
R"(  }};

  constexpr std::string_view {pluginName}PluginTypes[] = 
  {{
)",
      fmt::arg("pluginName", pluginName));

    for (auto & pluginType : pluginTypes)
    {
      ofs << fmt::format(
R"(    "{}"sv,
)",
        fmt::arg("pluginType", pluginType));
    }

    ofs << fmt::format(
R"(  }};

)");
  }

  ofs << 
R"(}

#endif // #ifndef PLUGINS_GEN_H
)";
}


constexpr auto importPreamble = R"(
void overground::{nsName}::importPod(
  humon::HuNode const & src, {structName}_t & dest)
{{
)";

void outputImportFromHumon(string_view nsName, structDef const & stru, ofstream & ofs)
{
  logFn();

  ofs << fmt::format(importPreamble, 
    fmt::arg("structName", stru.name),
    fmt::arg("nsName", nsName));

  for (auto & member : stru.memberDefs)
  {
    auto & memberName = member.name;
    ofs << fmt::format(
R"(  if (src % "{memberName}")
  {{
    auto & src0 = src / "{memberName}";
    {memberType} dst0;
)",
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
          ofs << fmt::format(
R"(
{indent}for (size_t i{prevDepth} = 0; i{prevDepth} < {src}.size(); ++i{prevDepth})
{indent}{{
{indent}  auto & src{depth} = {src} / i{prevDepth};
{indent}  {lvalueType} dst{depth};
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("lvalueType", mtda),
            fmt::arg("depth", depth),
            fmt::arg("prevDepth", depth - 1),
            fmt::arg("src", src));

          fn_ref(mtd.subTypes[0], depth + 1, fmt::format("dst{}", depth), fmt::format("src{}", depth), fn_ref);

          ofs << fmt::format(
R"(
{indent}  {lvalue}.push_back(std::move(dst{depth}));
{indent}}}
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("prevDepth", depth - 1),
            fmt::arg("depth", depth),
            fmt::arg("lvalue", lvalue));
        }

        else if (mtd.name == "std::array")
        {
          auto & mtda = mtd.subTypes[0];
          auto len = std::atol(mtd.subTypes[1].name.c_str());
          ofs << fmt::format(
R"({indent}for (size_t i{prevDepth} = 0; i{prevDepth} < {len}; ++i{prevDepth})
{indent}{{
{indent}  auto & src{depth} = {src} / i{prevDepth};
{indent}  {lvalueType} dst{depth};
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("len", len),
            fmt::arg("lvalueType", mtda),
            fmt::arg("depth", depth),
            fmt::arg("prevDepth", depth - 1),
            fmt::arg("src", src));

          fn_ref(mtd.subTypes[0], depth + 1, fmt::format("dst{}", depth), fmt::format("src{}", depth), fn_ref);

          ofs << fmt::format(
R"({indent}  {lvalue}[i{prevDepth}] = std::move(dst{depth});
{indent}}}
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("prevDepth", depth - 1),
            fmt::arg("depth", depth),
            fmt::arg("lvalue", lvalue));
        }

        else if (mtd.name == "stringDict")
        {
          auto & mtda = mtd.subTypes[0];
          ofs << fmt::format(
R"({indent}for (size_t i{prevDepth} = 0; i{prevDepth} < {src}.size(); ++i{prevDepth})
{indent}{{
{indent}  auto & src{depth} = {src} / i{prevDepth};
{indent}  auto const & key = {src}.keyAt(i{prevDepth});
{indent}  {lvalueType} dst{depth};
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("lvalueType", mtda),
            fmt::arg("depth", depth),
            fmt::arg("prevDepth", depth - 1),
            fmt::arg("src", src));

          fn_ref(mtd.subTypes[0], depth + 1, fmt::format("dst{}", depth), fmt::format("src{}", depth), fn_ref);

          ofs << fmt::format(
R"({indent}  {lvalue}.push_back(key, std::move(dst{depth}));
{indent}}}
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("prevDepth", depth - 1),
            fmt::arg("depth", depth),
            fmt::arg("lvalue", lvalue));
        }

        else if (mtd.name == "std::pair")
        {
          auto & mtda = mtd.subTypes[0];
          ofs << fmt::format(
R"({indent}{lvalueType} dst{depth}a;
{indent}{{
{indent}  auto & src{depth}a = {src} / 0;
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("lvalueType", mtda),
            fmt::arg("depth", depth),
            fmt::arg("src", src),
            fmt::arg("prevDepth", depth - 1));

          fn_ref(mtda, depth + 1, fmt::format("dst{}a", depth), fmt::format("src{}a", depth), fn_ref);

          ofs << fmt::format("{indent}}}\n",
            fmt::arg("indent", string(2 + 2 * depth, ' ')));

          auto & mtdb = mtd.subTypes[1];
          ofs << fmt::format(
R"({indent}{lvalueType} dst{depth}b;
{indent}{{
{indent}  auto & src{depth}b = {src} / 1;
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("lvalueType", mtdb),
            fmt::arg("depth", depth),
            fmt::arg("src", src),
            fmt::arg("prevDepth", depth - 1));

          fn_ref(mtdb, depth + 1, fmt::format("dst{}b", depth), fmt::format("src{}b", depth), fn_ref);

          ofs << fmt::format(
R"({indent}}}
{indent}{lvalue} = std::make_pair(
{indent}  std::move(dst{depth}a), std::move(dst{depth}b));
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("prevDepth", depth - 1),
            fmt::arg("depth", depth),
            fmt::arg("lvalue", lvalue));
        }

        else if (mtd.name == "std::unique_ptr")
        {

        }

        else if (mtd.name == "std::optional")
        {
          ofs << fmt::format(
R"({indent}{lvalueType} dst{depth};
{indent}{{
{indent}  auto & src{depth} = {src};
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("lvalueType", mtd.subTypes[0]),
            fmt::arg("depth", depth),
            fmt::arg("src", src));

          fn_ref(mtd.subTypes[0], depth + 1, fmt::format("dst{}", depth), fmt::format("src{}", depth), fn_ref);

          ofs << fmt::format(
R"({indent}}}
{indent}{lvalue}.emplace(std::move(dst{depth}));
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("depth", depth),
            fmt::arg("lvalue", lvalue));
        }

        else if (mtd.name == "std::variant")
        {
          ofs << fmt::format(
R"({indent}{{
{indent}  auto & src{depth} = {src};
{indent}  if (src{depth} % "type")
{indent}  {{
{indent}    std::string const & typ = src{depth} / "type";
{indent}    if (typ == "") {{ throw std::runtime_error("objects of variant type require a \"type\" key."); }}
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("depth", depth),
            fmt::arg("src", src));
          
          // foreach subtype in mtd.subTypes
          //   ofs << "if (typ == \"cmdBindPipeline_t\") {"
          //   fn_ref("cmdBindPipeline_t", ....);
          //   ofs << "}"
          for (auto & subType : mtd.subTypes)
          {
            string subTypeNu = fmt::format("{}", subType);
            if (subTypeNu[subTypeNu.size() - 2] == '_' &&
                subTypeNu[subTypeNu.size() - 1] == 't')
              { subTypeNu.resize(subTypeNu.size() - 2); }

            ofs << fmt::format(
R"({indent}    else if (typ == "{subTypeNu}")
{indent}    {{
{indent}      {subType} dst{depth};
)",
              fmt::arg("indent", string(2 + 2 * depth, ' ')),
              fmt::arg("depth", depth),
              fmt::arg("subTypeNu", subTypeNu),
              fmt::arg("subType", subType));

            fn_ref(subType, depth + 3, fmt::format("dst{}", depth), 
              fmt::format("src{}", depth), fn_ref);

          ofs << fmt::format(
R"({indent}      {lvalue}.emplace<{subType}>(std::move(dst{depth}));
{indent}    }}
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("depth", depth),
            fmt::arg("subType", subType),
            fmt::arg("lvalue", lvalue));
          }

          ofs << fmt::format(
R"(
{indent}  }}
{indent}  else {{ throw std::runtime_error("objects of variant type require a \"kind\" key."); }}
{indent}}}
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')));
        }
        // if it's not a container type, is it a
        // struct type that is defined in here?
        else if (auto psd = findStructDef(mtd.name);
          psd != nullptr)
        {
          ofs << fmt::format(
R"({indent}importPod({src}, {lvalue});
)",
            fmt::arg("indent", string(2 + 2 * depth, ' ')),
            fmt::arg("src", src),
            fmt::arg("lvalue", lvalue));
        }

        // otherwise, treat the node as a simple type, with concessions for values that we define @enumFromString.
        else
        {
          if (enumFromString.find(mtd.name) != enumFromString.end())
          {
            ofs << fmt::format(
R"({indent}{lvalue} = fromString<{leafType}>((std::string) {src}); // leaf
)",
              fmt::arg("indent", string(2 + 2 * depth, ' ')),
              fmt::arg("src", src),
              fmt::arg("leafType", mtd.name),
              fmt::arg("lvalue", lvalue));
          }
          else
          {
            ofs << fmt::format(
R"({indent}{lvalue} = ({leafType}) {src}; // leaf
)",
              fmt::arg("indent", string(2 + 2 * depth, ' ')),
              fmt::arg("src", src),
              fmt::arg("leafType", mtd.name),
              fmt::arg("lvalue", lvalue));
          }
        }

        if (isRoot)
        {
          ofs << fmt::format(
R"(    dest.{memberName} = std::move(dst0);
)",
            fmt::arg("memberName", memberName));
        }
      };
      fn_int(mtd, depth, lvalue, src, fn_int);
    };

    fn(member.type, 1, "dst0", "src0");
    ofs << "  }\n";
  }

  ofs << "}\n\n";
}


void outputImportFromBinary(string_view nsName, structDef const & stru, ofstream & ofs)
{
  logFn();

  log(thId, logTags::warn, "This operation has not been implemented yet.");

  ofs << fmt::format(
R"(void overground::{nsName}::importPod(
std::vector<uint8_t> const & src, {structName}_t & dest)
{{
)", 
    fmt::arg("structName", stru.name),
    fmt::arg("nsName", nsName));

  ofs << 
R"(  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
)";

  ofs << fmt::format("}}\n\n");
}


void outputExportToHumon(string_view nsName, structDef const & stru, ofstream & ofs)
{
  logFn();

  log(0, logTags::warn, "This operation has not been implemented yet.");

  ofs << fmt::format(
R"(void overground::{nsName}::exportPod({structName}_t const & src,
humon::HuNode & dest, int depth)
{{
)", 
    fmt::arg("structName", stru.name),
    fmt::arg("nsName", nsName));

  ofs << 
R"(  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
)";

  ofs << fmt::format("}}\n\n");
}


void outputExportToBinary(string_view nsName, structDef const & stru, ofstream & ofs)
{
  logFn();

  log(thId, logTags::warn, "This operation has not been implemented yet.");

  ofs << fmt::format(
R"(void overground::{nsName}::exportPod(
{structName}_t const & src, std::vector<uint8_t> & dest)
{{
)", 
    fmt::arg("structName", stru.name),
    fmt::arg("nsName", nsName));

  ofs << 
R"(  log(0, logTags::warn, "This operation has not been implemented yet.");

  // NOTE: This operation has not been implemented yet. If you need it, find boiler/src/assets.cpp, and good luck.
)";

  ofs << fmt::format("}}\n\n");
}


void outputPrint(string_view nsName, structDef const & stru, ofstream & ofs)
{
  logFn();

  ofs << fmt::format(
R"(std::string overground::{nsName}::print(
  {structName}_t const & src, int depth)
{{
  string prevIndentIn(depth * 2, ' ');
  string indentIn(2 + depth * 2, ' ');
  std::ostringstream ss;
  ss << "{{";
)", 
    fmt::arg("structName", stru.name),
    fmt::arg("nsName", nsName));

  for (auto & member : stru.memberDefs)
  {
    auto & memberName = member.name;

    // recursive lambda
    const auto fn = [&](memberTypeDef const & mtd, string_view memberName, string_view memberParentType, string_view srcName, int depth)->void
    {
      auto fn_int = [&](memberTypeDef const & mtd, string_view memberName, string_view memberParentType, string_view srcName, int depth, auto & fn_ref)->void
      {
        string indentIn = "\"" + string(2 + 2 * depth, ' ') + "\"";
        string prevIndentIn = "\"" + string(0 + 2 * depth, ' ') + "\"";
        string indent (2 + 2 * depth, ' ');

        if (depth == 0)
        {
          ofs << fmt::format(
R"({indent}ss << "\n" << indentIn << "{srcName}: ";
)", 
            fmt::arg("indent", indent),
            fmt::arg("srcName", srcName));
        }
        else if(mtd.subTypes.size() == 0 &&
          memberParentType != "std::optional")
        {
          ofs << fmt::format(
R"({indent}ss << "\n" << indentIn;
)", 
            fmt::arg("indent", indent));
        }

        // vector | array
        if (mtd.name == "std::vector" ||
            mtd.name == "std::array")
        {
          ofs << fmt::format(
R"({indent}ss << "[";
{indent}for (size_t i{depth} = 0; i{depth} < {memberName}.size(); ++i{depth})
{indent}{{
{indent}  depth += 1;
{indent}  string prevIndentIn(depth * 2, ' ');
{indent}  string indentIn(2 + depth * 2, ' ');
{indent}  {subType} const & src{depth} = {memberName}[i{depth}];
)",
            fmt::arg("indent", indent),
            fmt::arg("depth", depth),
            fmt::arg("subType", mtd.subTypes[0]),
            fmt::arg("memberName", memberName));

          fn_ref(
            mtd.subTypes[0],
            (string_view) fmt::format("src{}", depth), 
            mtd.name,
            (string_view) fmt::format("src{}", depth), 
            depth + 1, 
            fn_ref);

          ofs << fmt::format(
R"({indent}  depth -= 1;
{indent}}}
{indent}ss << "\n" << indentIn << "]";
)", 
            fmt::arg("indent", indent));
        }

        // stringDict
        else if (mtd.name == "stringDict")
        {
          ofs << fmt::format(
R"({indent}ss << "{{";
{indent}for (size_t i{depth} = 0; i{depth} < {memberName}.size(); ++i{depth})
{indent}{{
{indent}  auto const & [key, idx] = {memberName}.keys[i{depth}];
{indent}  depth += 1;
{indent}  string prevIndentIn(depth * 2, ' ');
{indent}  string indentIn(2 + depth * 2, ' ');
{indent}  {subType} const & src{depth} = {memberName}[idx];
{indent}  ss << indentIn << key << ": ";
)",
            fmt::arg("indent", indent),
            fmt::arg("depth", depth),
            fmt::arg("subType", mtd.subTypes[0]),
            fmt::arg("memberName", memberName));

          fn_ref(
            mtd.subTypes[0],
            (string_view) fmt::format("src{}", depth), 
            mtd.name,
            (string_view) fmt::format("src{}", depth), 
            depth + 1, 
            fn_ref);

          ofs << fmt::format(
R"({indent}  depth -= 1;
{indent}}}
{indent}ss << "\n" << indentIn << "}}";
)", 
            fmt::arg("indent", indent));
        }

        // pair
        else if (mtd.name == "std::pair")
        {
          ofs << fmt::format(
R"(
{indent}{{
{indent}  ss << "[";
{indent}  depth += 1;
{indent}  string prevIndentIn(depth * 2, ' ');
{indent}  string indentIn(2 + depth * 2, ' ');
{indent}  {subType} const & src{depth} = {memberName}.first;
)",
            fmt::arg("indent", indent),
            fmt::arg("subType", mtd.subTypes[0]),
            fmt::arg("depth", depth),
            fmt::arg("memberName", memberName));

          fn_ref(
            mtd.subTypes[0], 
            (string_view) fmt::format("src{}", depth), 
            mtd.name,
            (string_view) fmt::format("src{}", depth), 
            depth + 1,
            fn_ref);

          ofs << fmt::format(
R"(
{indent}  ss << indentIn;
{indent}  depth -= 1;
{indent}}}
{indent}{{
{indent}  depth += 1;
{indent}  string prevIndentIn(depth * 2, ' ');
{indent}  string indentIn(2 + depth * 2, ' ');
{indent}  {subType} const & src{depth} = {memberName}.second;
)",
            fmt::arg("indent", indent),
            fmt::arg("subType", mtd.subTypes[1]),
            fmt::arg("depth", depth),
            fmt::arg("memberName", memberName));

          fn_ref(
            mtd.subTypes[1], 
            (string_view) fmt::format("src{}", depth), 
            mtd.name,
            (string_view) fmt::format("src{}", depth), 
            depth + 1, 
            fn_ref);

          ofs << fmt::format(
R"(
{indent}depth -= 1;
{indent}ss << "\n" << prevIndentIn << "]";
{indent}}}
)",
            fmt::arg("indent", indent));
        }

        // optional
        else if (mtd.name == "std::optional")
        {
          ofs << fmt::format(
R"(
{indent}if ((bool) {memberName})
{indent}{{
{indent}  {subType} const & src{depth} = * {memberName};
)",
            fmt::arg("indent", indent),
            fmt::arg("subType", mtd.subTypes[0]),
            fmt::arg("depth", depth),
            fmt::arg("memberName", memberName));

          fn_ref(
            mtd.subTypes[0], 
            (string_view) fmt::format("src{}", depth), 
            mtd.name,
            (string_view) fmt::format("src{}", depth), 
            depth + 1, 
            fn_ref);

          ofs << fmt::format(
            
R"({indent}}}
{indent}else
{indent}  {{ ss << "<undefined>"; }}
)",
            fmt::arg("indent", indent));
        }

        // variant
        else if (mtd.name == "std::variant")
        {
          ofs << fmt::format(
R"(
{indent}if ({memberName}.valueless_by_exception())
{indent}  {{ ss << "bad state\n"; }}
)",
            fmt::arg("indent", indent),
            fmt::arg("memberName", memberName));

          for (auto & subType : mtd.subTypes)
          {
            ofs << fmt::format(
R"({indent}else if (std::holds_alternative<{subType}>({memberName}))
{indent}{{
{indent}  {subType} const & src{depth} = std::get<{subType}>({memberName});
)",
            fmt::arg("indent", indent),
            fmt::arg("subType", subType),
            fmt::arg("depth", depth),
            fmt::arg("memberName", memberName));

          fn_ref(
            subType, 
            (string_view) fmt::format("src{}", depth), 
            mtd.name,
            (string_view) fmt::format("src{}", depth), 
            depth + 1, 
            fn_ref);

            ofs << fmt::format(
R"({indent}}}
)",
              fmt::arg("indent", indent));
          }

          ofs << fmt::format(
R"({indent}else {{ ss << "(unknown variant)\n"; }}
)",
            fmt::arg("indent", indent));
        }

        // nested struct
        else if (auto pstru = findStructDef(mtd.name);
          pstru != nullptr)
        {
          ofs << fmt::format(
R"({indent}ss << print({memberName}, depth + 1);
)",
            fmt::arg("indent", indent),
            fmt::arg("memberName", memberName));
        }

        // enumish
        else if (enumFromString.find(mtd.name) !=
          enumFromString.end())
        {
          ofs << fmt::format(
R"({indent}ss << to_string({src});
)",
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

      fn_int(mtd, memberName, memberParentType, srcName, depth, fn_int);
    };

    fn(member.type, "src." + memberName, "", memberName, 0);
  }

  ofs << fmt::format(
R"(  ss << "\n" << prevIndentIn << "}}";
  return ss.str();
}}

ostream & overground::{nsName}::operator << (ostream & stream, {structType}_t const & rhs)
{{
  stream << print(rhs);
  return stream;
}}
)",
    fmt::arg("structType", stru.name),
    fmt::arg("nsName", nsName));
}


string capitalize(string_view rhs)
{
  string st(rhs);
  st[0] = st[0] - 32;
  return st;
}


void outputPluginCentralStation(string_view nsName, string_view pluginType, string_view pluginTypeLower, string_view pluginTypeUpper, ofstream & ofs)
{
  // "objects", "object", "Object"

  auto & pluginNames = plugins.find(pluginType)->second;

  logFn();

  ofs << fmt::format(
R"(// This is a generated file. Do not modify this. You'll lose it all one day and will be sad. It's generated by the boilermaker process from files contained in ../plugins/.

#include "{basePluginType}.h"
)",
    fmt::arg("basePluginType", pluginTypeLower));

  for (auto & pluginName : pluginNames)
  {
    ofs << fmt::format(
R"(#include "{basePluginType}.{pluginName}.h"
)",
      fmt::arg("basePluginType", pluginType),
      fmt::arg("pluginName", pluginName));
  }

  if (pluginType == "objects")
  {
    ofs << fmt::format(
  R"(
  using namespace std;
  using namespace overground;


  std::unique_ptr<{baseClassName}> make{baseClassName}({nsName}::{podName}_t const & desc)
  {{
  if (desc.data.has_value() &&
      desc.data->valueless_by_exception() == false)
  {{
      auto typeIdx = desc.data->index();
      switch(typeIdx)
      {{
  )",
      fmt::arg("baseClassName", pluginTypeUpper),
      fmt::arg("nsName", nsName),
      fmt::arg("podName", pluginTypeLower));
  }
  else
  {
    ofs << fmt::format(
  R"(
using namespace std;
using namespace overground;


std::unique_ptr<{baseClassName}> make{baseClassName}({nsName}::{podName}_t const & desc)
{{
  if (desc.data.valueless_by_exception() == false)
  {{
    auto typeIdx = desc.data.index();
    switch(typeIdx)
    {{
)",
      fmt::arg("baseClassName", pluginTypeUpper),
      fmt::arg("nsName", nsName),
      fmt::arg("podName", pluginTypeLower));
  }
  
  size_t pluginIdx = 0;
  for (auto & pluginName : pluginNames)
  {
    ofs << fmt::format(
R"(    case {pluginIdx}: // {pluginName}
      return std::make_unique<{pluginName}>(desc);
)",
      fmt::arg("pluginIdx", pluginIdx),
      fmt::arg("pluginName", capitalize(pluginName)));
    pluginIdx += 1;
  }

  ofs << fmt::format(
R"(    }}
  }}

  return std::make_unique<{baseClassName}>(desc);
}}
)",
    fmt::arg("baseClassName", pluginTypeUpper));  
}


int overground::assetsMain(path_t const & defsPath, path_t const & outputPodsDir, path_t const & outputPluginsDir)
{
  log(0, fmt::format("\
{}Making boilerplate code from definitions in {}.{}\n\
Output base: {}{}{}",
    ansi::lightCyan, defsPath, ansi::off,
    ansi::lightYellow, outputPodsDir, ansi::off));
  
  if (fs::exists(outputPodsDir) == false)
  {
    log(0, fmt::format("{}Creating {}.{}",
      ansi::darkYellow, outputPodsDir, ansi::off));
    fs::create_directory(outputPodsDir);
  }

  auto outuptIncDir = path_t(outputPodsDir).append("/inc");
  if (fs::exists(outuptIncDir) == false)
  {
    log(0, fmt::format("{}Creating {}.{}",
      ansi::darkYellow, outuptIncDir, ansi::off));
    fs::create_directory(outuptIncDir);
  }

  auto outupSrccDir = path_t(outputPodsDir).append("/src");
  if (fs::exists(outupSrccDir) == false)
  {
    log(0, fmt::format("{}Creating {}.{}",
      ansi::darkYellow, outupSrccDir, ansi::off));
    fs::create_directory(outupSrccDir);
  }

  parseDefsFile(defsPath);
  openFiles(outputPodsDir, outputPluginsDir);  

  for (auto & ns : nss)
  {
    auto & nsName = ns.name;
    auto & ofsH = nsHeaderFiles[nsName];
    auto & ofsC = nsCppFiles[nsName];

    for (auto & stru : ns.structDefs)
    {
      outputStructDefs(stru, ofsH);
      outputImportFromHumon(nsName, stru, ofsC);
      outputImportFromBinary(nsName, stru, ofsC);
      outputExportToHumon(nsName, stru, ofsC);
      outputExportToBinary(nsName, stru, ofsC);
      outputPrint(nsName, stru, ofsC);
    }
  }

  outputPluginDefs(plHeaderFile);
  
  outputPluginCentralStation("asset", "assets", "asset", "Asset", pluginCppFiles["assets"]);
  outputPluginCentralStation("tableau", "features", "feature", "Feature", pluginCppFiles["features"]);
  outputPluginCentralStation("tableau", "objects", "object", "Object", pluginCppFiles["objects"]);

  closeFiles();

  return 0;
}
