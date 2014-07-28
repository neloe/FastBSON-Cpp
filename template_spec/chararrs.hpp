/*!
 * \file chararrs.hpp
 * \author Nathan Eloe
 * \brief std::array<char, 12> template specializations
 */
#pragma once
#include "../element.h"
#include <array>
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<oid>();
  template<>
  std::string to_string<oid>();
  template<>
  bool Element::check_convert<oid>() const;
  template<>
  unsigned Element::deserialize_bytes<oid>(const char* bytes);
  template<>
  void Element::serialize_bson<oid>(std::ostringstream& oss) const;
  template<>
  std::string Element::_to_std_str<oid>() const;
}
