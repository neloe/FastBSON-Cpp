/*!
 * \file ints.hpp
 * \author Nathan Eloe
 * \brief integer and long template specializations
 */
#pragma once
#include "../element.h"
#include <string>

namespace bson
{
  //long integers
  template<>
  TypeInfo default_type<long>();
  template <>
  std::string to_string<long>();
  template <>
  bool Element::check_convert<long>() const;
  template<>
  unsigned Element::deserialize_bytes<long>(const char* bytes);
  template<>
  void Element::serialize_bson<long>(std::ostringstream& oss) const;
  template <>
  std::string Element::_to_std_str<long>() const;
  //integers
  template<>
  TypeInfo default_type<int>();
  template<>
  std::string to_string<int>();
  template <>
  bool Element::check_convert<int>() const;
  template<>
  TypeInfo default_type<short>();
  template<>
  std::string to_string<short>();
  template <>
  bool Element::check_convert<short>() const;
  template<>
  unsigned Element::deserialize_bytes<int>(const char* bytes);
  template<>
  void Element::serialize_bson<int>(std::ostringstream& oss) const;
  template <>
  std::string Element::_to_std_str<int>() const;
}