#ifndef UTILS_H
#define UTILS_H

#include <type_traits>
#include <sstream>
#include <iostream>
#include <mutex>

namespace overground
{
  template <class EnumType,
    typename = std::enable_if_t<std::is_enum<EnumType>::value>> 
  inline EnumType operator ~(EnumType rhs)
  {
    using UT = std::underlying_type_t<EnumType>;
    return static_cast<EnumType>(~ static_cast<UT>(rhs));
  }

  template <class EnumType,
    typename = std::enable_if_t<std::is_enum<EnumType>::value>> 
  inline EnumType operator & (EnumType lhs, EnumType rhs)
  {
    using UT = std::underlying_type_t<EnumType>;
    return static_cast<EnumType>(static_cast<UT>(lhs) & static_cast<UT>(rhs));
  }

  template <class EnumType,
    typename = std::enable_if_t<std::is_enum<EnumType>::value>> 
  inline EnumType operator | (EnumType lhs, EnumType rhs)
  {
    using UT = std::underlying_type_t<EnumType>;
    return static_cast<EnumType>(static_cast<UT>(lhs) | static_cast<UT>(rhs));
  }

  template <class EnumType,
    typename = std::enable_if_t<std::is_enum<EnumType>::value>> 
  inline EnumType operator ^ (EnumType lhs, EnumType rhs)
  {
    using UT = std::underlying_type_t<EnumType>;
    return static_cast<EnumType>(static_cast<UT>(lhs) ^ static_cast<UT>(rhs));
  }

  template <class EnumType,
    typename = std::enable_if_t<std::is_enum<EnumType>::value>> 
  inline EnumType & operator &= (EnumType & lhs, EnumType rhs)
  {
    lhs = lhs & rhs;
    return lhs;
  }

  template <class EnumType,
    typename = std::enable_if_t<std::is_enum<EnumType>::value>> 
  inline EnumType & operator |= (EnumType & lhs, EnumType rhs)
  {
    lhs = lhs | rhs;
    return lhs;
  }

  template <class EnumType,
    typename = std::enable_if_t<std::is_enum<EnumType>::value>> 
  inline EnumType & operator ^= (EnumType & lhs, EnumType rhs)
  {
    lhs = lhs ^ rhs;
    return lhs;
  }

  class sout : public std::ostringstream
  {
  public:
    sout() = default;
    ~sout()
    {
      try
      {
        std::lock_guard<std::mutex> lock(mx);
        std::cout << this->str();
      }
      catch(const std::exception& e)
      {
        std::cerr << "Exception in ~sout(): " << e.what() << '\n';
      }
    }

  private:
    static std::mutex mx;
  };
}

#endif // #ifndef UTILS_H
