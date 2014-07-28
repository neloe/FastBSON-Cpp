/*!
 * \file document.hpp
 * \author Nathan Eloe
 * \brief Document template specializations
 */
#pragma once
#include "../element.h"
#include "../document.h"
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<Document>();
  template<>
  std::string to_string<Document>();
  template<>
  bool Element::check_convert<Document>() const;
  template<>
  unsigned Element::deserialize_bytes<Document>(const char* bytes);
  template<>
  void Element::serialize_bson<Document>(std::ostringstream& oss) const;
  template <>
  std::string Element::_to_std_str<Document>() const;
}