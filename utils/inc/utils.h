#ifndef UTILS_H
#define UTILS_H

#include <type_traits>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <mutex>
#include <experimental/filesystem>
#include "ansiTerm.h"
#include "humon.h"
#include "logger.h"

namespace overground
{
  using version_t = std::array<int, 3>;
  constexpr auto engineName = "overground";
  constexpr version_t engineVersion = { 0, 0, 0 };

  constexpr auto assetFileExtension = ".ass";

  namespace fs = std::experimental::filesystem;
  using fileTime_t = std::experimental::filesystem::file_time_type;
  using path_t = std::experimental::filesystem::path;


  /**/
  // Enum class bitwise ops
  // ~
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  constexpr inline EnumType operator ~(EnumType rhs)
  {
    using UT = std::underlying_type_t<EnumType>;
    return static_cast<EnumType>(~ static_cast<UT>(rhs));
  }

  template <class EnumType, class NumType,
    typename = std::enable_if_t
    <
      std::is_enum<EnumType>::value &&
      std::is_integral<NumType>::value
    >>
  constexpr inline EnumType operator ~(NumType rhs)
  {
    return ~ static_cast<EnumType>(rhs);
  } 

  // &
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  constexpr inline EnumType operator & (EnumType lhs, EnumType rhs)
  {
    using UT = std::underlying_type_t<EnumType>;
    return static_cast<EnumType>(static_cast<UT>(lhs) & static_cast<UT>(rhs));
  }

  template <class EnumType, class NumType,
    typename = std::enable_if_t
    <
      std::is_enum<EnumType>::value &&
      std::is_integral<NumType>::value
    >>
  constexpr inline EnumType operator & (EnumType lhs, NumType rhs)
  {
    return lhs & static_cast<EnumType>(rhs);
  }

  // |
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  constexpr inline EnumType operator | (EnumType lhs, EnumType rhs)
  {
    using UT = std::underlying_type_t<EnumType>;
    return static_cast<EnumType>(static_cast<UT>(lhs) | static_cast<UT>(rhs));
  }

  template <class EnumType, class NumType,
    typename = std::enable_if_t
    <
      std::is_enum<EnumType>::value &&
      std::is_integral<NumType>::value
    >>
  constexpr inline EnumType operator | (EnumType lhs, NumType rhs)
  {
    return lhs | static_cast<EnumType>(rhs);
  }

  // ^
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  constexpr inline EnumType operator ^ (EnumType lhs, EnumType rhs)
  {
    using UT = std::underlying_type_t<EnumType>;
    return static_cast<EnumType>(static_cast<UT>(lhs) ^ static_cast<UT>(rhs));
  }

  template <class EnumType, class NumType,
    typename = std::enable_if_t
    <
      std::is_enum<EnumType>::value &&
      std::is_integral<NumType>::value
    >>
  constexpr inline EnumType operator ^ (EnumType lhs, NumType rhs)
  {
    return lhs ^ static_cast<EnumType>(rhs);
  }

  // ==
  template <class EnumType, class NumType,
    typename = std::enable_if_t
    <
      std::is_enum<EnumType>::value &&
      std::is_integral<NumType>::value
    >>
  constexpr inline bool operator == (EnumType lhs, NumType rhs)
  {
    return lhs == static_cast<EnumType>(rhs);
  }

  // !=
  template <class EnumType, class NumType,
    typename = std::enable_if_t
    <
      std::is_enum<EnumType>::value &&
      std::is_integral<NumType>::value
    >>
  constexpr inline bool operator != (EnumType lhs, NumType rhs)
  {
    return lhs != static_cast<EnumType>(rhs);
  }

  // &=
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  constexpr inline EnumType & operator &= (EnumType & lhs, EnumType rhs)
  {
    lhs = lhs & rhs;
    return lhs;
  }

  template <class EnumType, class NumType,
    typename = std::enable_if_t
    <
      std::is_enum<EnumType>::value &&
      std::is_integral<NumType>::value
    >>
  constexpr inline EnumType & operator &= (EnumType & lhs, NumType rhs)
  {
    lhs = lhs & rhs;
    return lhs;
  }

  // |=
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  constexpr inline EnumType & operator |= (EnumType & lhs, EnumType rhs)
  {
    lhs = lhs | rhs;
    return lhs;
  }

  template <class EnumType, class NumType,
    typename = std::enable_if_t
    <
      std::is_enum<EnumType>::value &&
      std::is_integral<NumType>::value
    >>
  constexpr inline EnumType & operator |= (EnumType & lhs, NumType rhs)
  {
    lhs = lhs | rhs;
    return lhs;
  }

  // ^=
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  constexpr inline EnumType & operator ^= (EnumType & lhs, EnumType rhs)
  {
    lhs = lhs ^ rhs;
    return lhs;
  }

  template <class EnumType, class NumType,
    typename = std::enable_if_t
    <
      std::is_enum<EnumType>::value &&
      std::is_integral<NumType>::value
    >>
  constexpr inline EnumType & operator ^= (EnumType & lhs, NumType rhs)
  {
    lhs = lhs ^ rhs;
    return lhs;
  }

  path_t findFile(std::string_view filename, std::string_view baseDir);

  std::string loadFileAsString(path_t const & path);
  std::vector<char> loadFileAsBinary(path_t const & path);

  humon::nodePtr_t loadHumonDataFromFile(path_t const & path);

  template<class T>
  std::string join(T const & vec, 
    std::string_view delim = ", ",
    std::string_view form = "{}",
    std::string_view orElse = "")
  {
    if (std::size(vec) == 0)
      { return std::string(orElse); }

    std::stringstream st;
    st << fmt::format(form, * std::begin(vec));

    for (auto it = std::next(std::begin(vec));
         it != std::end(vec); ++ it)
    {
      st << delim;
      st << fmt::format(form, *it);
    }

    return st.str();
  }


#define CHK(call) \
  {  \
    auto res = call;  \
    if (res != vk::Result::eSuccess)  \
    { throw std::runtime_error(fmt::format("{} failed", #call)); } \
  }
}

#endif // #ifndef UTILS_H
