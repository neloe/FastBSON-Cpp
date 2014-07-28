/*!
 * \file vectors.hpp
 * \author Nathan Eloe
 * \brief vector template specializations
 */
#pragma once
#include "../element.h"
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<array>();
  template<>
  std::string to_string<array>();
  template<>
  bool Element::check_convert<array>() const;
  template<>
  unsigned Element::deserialize_bytes<array>(const unsigned char* bytes);
  template<>
  void Element::serialize_bson<array>(std::ostringstream& oss) const;
  template <>
  std::string Element::_to_std_str<array>() const;
}
