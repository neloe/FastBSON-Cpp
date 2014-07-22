/*!
 * \file floats.hpp
 * \author Nathan Eloe
 * \brief floating point template specializations
 */

#pragma once

#include "../typeinfo.h"
#include "convert_utils.h"

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
  
  template<>
  unsigned Element::deserialize_bytes<bool>(const char* bytes)
  {
    m_data = make_void_shared(bytes[0]);
    return 1;
  }
  
  template<>
  void Element::serialize_bson<bool>(std::ostringstream& oss) const
  {
    char truth = 0 + *(std::static_pointer_cast<bool>(m_data));
    oss << truth;
    return;
  }
}