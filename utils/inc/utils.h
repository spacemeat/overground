#ifndef UTILS_H
#define UTILS_H

#include <type_traits>
#include <sstream>
#include <iostream>
#include <mutex>
#include "ansiTerm.h"

namespace overground
{
  using version_t = std::array<int, 3>;
  constexpr auto engineName = "overground";
  constexpr version_t engineVersion = { 0, 0, 0 };

  // Enum class bitwise ops
  // ~
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  inline EnumType operator ~(EnumType rhs)
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
  inline EnumType operator ~(NumType rhs)
  {
    return ~ static_cast<EnumType>(rhs);
  } 

  // &
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  inline EnumType operator & (EnumType lhs, EnumType rhs)
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
  inline EnumType operator & (EnumType lhs, NumType rhs)
  {
    return lhs & static_cast<EnumType>(rhs);
  }

  // |
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  inline EnumType operator | (EnumType lhs, EnumType rhs)
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
  inline EnumType operator | (EnumType lhs, NumType rhs)
  {
    return lhs | static_cast<EnumType>(rhs);
  }

  // ^
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  inline EnumType operator ^ (EnumType lhs, EnumType rhs)
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
  inline EnumType operator ^ (EnumType lhs, NumType rhs)
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
  inline bool operator == (EnumType lhs, NumType rhs)
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
  inline bool operator != (EnumType lhs, NumType rhs)
  {
    return lhs != static_cast<EnumType>(rhs);
  }

  // &=
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  inline EnumType & operator &= (EnumType & lhs, EnumType rhs)
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
  inline EnumType & operator &= (EnumType & lhs, NumType rhs)
  {
    lhs = lhs & rhs;
    return lhs;
  }

  // |=
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  inline EnumType & operator |= (EnumType & lhs, EnumType rhs)
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
  inline EnumType & operator |= (EnumType & lhs, NumType rhs)
  {
    lhs = lhs | rhs;
    return lhs;
  }

  // ^=
  template <class EnumType,
    typename = std::enable_if_t
    < std::is_enum<EnumType>::value> > 
  inline EnumType & operator ^= (EnumType & lhs, EnumType rhs)
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
  inline EnumType & operator ^= (EnumType & lhs, NumType rhs)
  {
    lhs = lhs ^ rhs;
    return lhs;
  }


  class sout : public std::ostringstream
  {
  public:
    sout(bool doIt = true) : doIt(doIt) { }
    ~sout()
    {
      if (doIt)
      {
        try
        {
          std::lock_guard<std::mutex> lock(mx);
          std::cout << this->str();
          std::cout.flush();
        }
        catch(const std::exception& e)
        {
          std::cerr << "Exception in ~sout(): " << e.what() << '\n';
        }
      }
    }

  private:
    bool doIt;
    static std::mutex mx;
  };


  class ss : public std::ostringstream
  {
  public:
    struct endtoken { enum Value { }; };
    static endtoken end;

    ss() = default;
    ~ss() = default;

    operator char const *()
    {
      return str().c_str();
    }
  };

  std::string operator << (std::ostream & lhs, ss::endtoken rhs);


#define CHK(call) \
  {  \
    auto res = call;  \
    if (res != vk::Result::eSuccess)  \
    { throw std::runtime_error(ss {}  \
      << #call << " failed: "  \
      << ss::end); } \
  }
}

#endif // #ifndef UTILS_H
