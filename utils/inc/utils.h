#ifndef UTILS_H
#define UTILS_H

#include <type_traits>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <mutex>
#include <filesystem>

#include "ansiTerm.h"
#include "humon.h"
#include "logger.h"
//#include "objRef.h"
#include "stringDict.h"

namespace overground
{
  void initGlobals();

  using version_t = std::array<int, 3>;
  constexpr auto engineName = "overground";
  constexpr version_t engineVersion = { 0, 0, 0 };

  constexpr auto assetFileExtension = ".ass";

  namespace fs = std::filesystem;
  using fileTime_t = std::filesystem::file_time_type;
  using path_t = std::filesystem::path;

  constexpr size_t cacheLineSizeDestructive = 128;
  constexpr size_t cacheLineSizeConstructive = 64;

  // TODO: Use the system-specific call like
  // sysconf(_SC_PAGE_SIZE)
  constexpr size_t pageLineSize = 512;

  /*
  template <class RetObj>
  struct RetVal
  {
    std::optional<RetObj> obj_;

    operator bool() { return obj_.has_value(); }
    std::optional<RetObj> & obj() const & noexcept { return obj_; }
    std::optional<RetObj> && obj() const && noexcept { return obj_; }
  };
  */

  template <class T, class U>
  class FlagRaiiser // requires U be convertible to T
  {
  public:
    FlagRaiiser(T & flag, U value)
    : flag(flag), value(value)
    { }

    ~FlagRaiiser()
    {
      flag = value;
    }

    T & flag;
    U value;
  };


  class Asset;

  enum class FramePhaseKinds
  {
    frameMaintenance,
    graphicsStructure,  // joins on all GPU ops - for when we hae to change vulkan objects, for instance.

    acquireImage,
    
    beginComputePass,
    endComputePass,

    beginRenderPass,
    beginSubpass,
    endRenderPass,

    submitCommands,
    present,

    nonBarrierJobQueue,
    barrierJobQueue
  };


  enum class BufferStrategy
  {
    /*  randomTableaux - 
          One buffer per tableau, each storing all of that tableau's assets, with no consideration given to resource overlap between buffers.
    */
    randomTableaux,

    /*  lifoTableaux - 
          One buffer per tableau, but anywhere we can use the asset in a previous tableau in any group, we will do so. This implies a stack-based tableau progression, where the newest tableau added is the first removed. Minimal buffer usage on disk, no buffer swapping in vram, but rigid tableau progression.
    */
    lifoTableaux,

    /*  randomGroup -
          One buffer per group, with no consideration given to resource overlap between groups. Changing groups means blowing out the buffer and slam-homing the new one.
    */
    randomGroup
  };


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

#define logFn() { log(thId, logTags::fn, fmt::format("{}{}{}:", ansi::darkYellow, __PRETTY_FUNCTION__, ansi::off)); }



#define CHK(call) \
  {  \
    auto res = call;  \
    if (res != vk::Result::eSuccess)  \
    { throw std::runtime_error(fmt::format("{} failed", #call)); } \
  }

  enum class DataObjectKindFlags
  {
    none =            0,
    config =          1 <<   0,
    renderPass =      1 <<   1,
    framePlan =       1 <<   2,
  };
}

#endif // #ifndef UTILS_H
