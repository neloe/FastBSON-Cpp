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
  TypeInfo default_type<double>()
  {
    return FLOATING;
  }
  
  template <>
  std::string to_string<double>()
  {
    return "double";
  }
  
  template <>
  bool Element::check_convert<double>() const
  {
    return m_type == FLOATING;
  }
}