/*!
 * \file strings.hpp
 * \author Nathan Eloe
 * \brief string template specializations
 */
#pragma once
#include "../element.h"
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<std::string>();
  template<>
  std::string to_string<std::string>();
  template <>
  bool Element::check_convert<std::string>() const;
  template<>
  unsigned Element::deserialize_bytes<std::string>(const unsigned char* bytes);
  template<>
  void Element::serialize_bson<std::string>(std::ostringstream& oss) const;
  template <>
  std::string Element::_to_std_str<std::string>() const;
}
