/*!
 * \file floats.hpp
 * \author Nathan Eloe
 * \brief floating point template specializations
 */

#pragma once

#include "../typeinfo.h"

namespace bson
{
  template<>
  TypeInfo default_type<bool>()
  {
    return BOOL;
  }
  
  template <>
  std::string to_string<bool>()
  {
    return "bool";
  }
  
  template <>
  bool Element::check_convert<bool>() const
  {
    return m_type == BOOL;
  }
}