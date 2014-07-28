/*!
 * \file binary.hpp
 * \author Nathan Eloe
 * \brief binary template specializations
 */
#pragma once
#include "../element.h"
#include <string>
namespace bson
{
  template<>
  TypeInfo default_type<binary>();
  template<>
  std::string to_string<binary>();
  template<>
  bool Element::check_convert<binary>() const;
  template<>
  unsigned Element::deserialize_bytes<binary>(const char* bytes);
  template<>
  void Element::serialize_bson<binary>(std::ostringstream& oss) const;
  template<>
  std::string Element::_to_std_str<binary>() const;
}
