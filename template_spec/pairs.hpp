/*!
 * \file pairs.hpp
 * \author Nathan Eloe
 * \brief std::pair<std::string, std::string> template specializations
 */
#pragma once
#include "../element.h"
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<regex>();
  template<>
  std::string to_string<regex>();
  template<>
  bool Element::check_convert<regex>() const;
  template<>
  unsigned Element::deserialize_bytes<regex>(const char* bytes);
  template<>
  void Element::serialize_bson<regex>(std::ostringstream& oss) const;
  template<>
  std::string Element::_to_std_str<regex>() const;
  template<>
  TypeInfo default_type<dbptr>();
  template<>
  std::string to_string<dbptr>();
  template<>
  bool Element::check_convert<dbptr>() const;
  template<>
  unsigned Element::deserialize_bytes<dbptr>(const char* bytes);
  template<>
  void Element::serialize_bson<dbptr>(std::ostringstream& oss) const;
  template<>
  std::string Element::_to_std_str<dbptr>() const;
}
