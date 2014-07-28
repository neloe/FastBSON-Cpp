/*!
 * \file jsscope.hpp
 * \author Nathan Eloe
 * \brief javascript code template specializations
 */
#pragma once
#include "../element.h"
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<jscode_scope>();
  template<>
  std::string to_string<jscode_scope>();
  template<>
  bool Element::check_convert<jscode_scope>() const;
  template<>
  unsigned Element::deserialize_bytes<jscode_scope>(const char* bytes);
  template<>
  void Element::serialize_bson<jscode_scope>(std::ostringstream& oss) const;
  template<>
  std::string Element::_to_std_str<jscode_scope>() const;
}
