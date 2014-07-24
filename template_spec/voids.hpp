/*!
 * \file voids.hpp
 * \author Nathan Eloe
 * \brief void template specializations
 */

#pragma once

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"

namespace bson
{
  template<>
  TypeInfo default_type<void>()
  {
    return NIL;
  }
  
  template <>
  std::string to_string<void>()
  {
    return "void";
  }
  
  template <>
  bool Element::check_convert<void>() const
  {
    return m_type == NIL || m_type == MINKEY || m_type == MAXKEY || m_type == UNDEF;
  }
  
  template<>
  unsigned Element::deserialize_bytes<void>(const char* bytes)
  {
    return 0;
  }
  
  template<>
  void Element::serialize_bson<void>(std::ostringstream& oss) const
  {
    return;
  }
  
  template <>
  std::string Element::_to_std_str<void>() const
  {
    return "";
  }
}