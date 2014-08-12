/*!
 * \file bools.hpp
 * \author Nathan Eloe
 * \brief boolean template specializations
 */
#pragma once
#include "../element.h"
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<bool>();
  template <>
  std::string to_string<bool>();
  template <>
  bool Element::check_convert<bool>() const;
  template<>
  unsigned Element::deserialize_bytes<bool>(const unsigned char* bytes);
  template<>
  void Element::serialize_bson<bool>(std::ostringstream& oss) const;
  template <>
  std::string Element::_to_std_str<bool>() const;
}
