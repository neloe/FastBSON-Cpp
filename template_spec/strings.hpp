/*!
 * \file strings.hpp
 * \author Nathan Eloe
 * \brief string template specializations
 */

#pragma once

#include "../typeinfo.h"
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<std::string>()
  {
    return STRING;
  }
  
  template<>
  std::string to_string<std::string>()
  {
    return "std::string";
  }
  
  template <>
  bool Element::check_convert<std::string>() const
  {
    return m_type == STRING || m_type == JS || m_type == DEPRECATED;
  }
  
}