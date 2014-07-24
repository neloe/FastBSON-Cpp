/*!
 * \file floats.hpp
 * \author Nathan Eloe
 * \brief floating point template specializations
 */

#pragma once

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"

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
  
  template<>
  unsigned Element::deserialize_bytes<double>(const char* bytes)
  {
    m_data = make_void_shared(_from_bytes<double>(bytes));
    return 8;
  }
  
  template<>
  void Element::serialize_bson<double>(std::ostringstream& oss) const
  {
    char num[8];
    _to_bytes(num, *(std::static_pointer_cast<double>(m_data)));
    oss << num[0] << num[1] << num[2] << num[3] << num[4] << num[5] << num[6] << num[7];
    return;
  }
  
  template <>
  std::string Element::_to_std_str<double>() const
  {
    std::ostringstream oss;
    oss << *(std::static_pointer_cast<double>(m_data));
    return oss.str();
  }
}