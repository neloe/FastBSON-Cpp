/*!
 * \file floats.hpp
 * \author Nathan Eloe
 * \brief Double precision numbers template specializations
 */
#pragma once
#include "../element.h"
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<double>();
  template <>
  std::string to_string<double>();
  template <>
  bool Element::check_convert<double>() const;
  template<>
  unsigned Element::deserialize_bytes<double>(const unsigned char* bytes);
  template<>
  void Element::serialize_bson<double>(std::ostringstream& oss) const;
  template <>
  std::string Element::_to_std_str<double>() const;
}
