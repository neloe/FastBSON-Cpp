/*!
 * \file voids.hpp
 * \author Nathan Eloe
 * \brief iboid template specializations
 */
#pragma once
#include "../element.h"
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<void>();
  template <>
  std::string to_string<void>();
  template <>
  bool Element::check_convert<void>() const;
  template<>
  unsigned Element::deserialize_bytes<void>(const char* bytes);
  template<>
  void Element::serialize_bson<void>(std::ostringstream& oss) const;
  template <>
  std::string Element::_to_std_str<void>() const;
}
