/*!
 * \file floats.hpp
 * \author Nathan Eloe
 * \brief integer template specializations
 */

#pragma once

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"

namespace bson
{
  //ints
  template<>
  TypeInfo default_type<long>()
  {
    return INT64;
  }
  
  template <>
  std::string to_string<long>()
  {
    return "long";
  }
  
  template <>
  bool Element::check_convert<long>() const
  {
    return m_type == INT64 || m_type == DATETIME || m_type == TIMESTAMP;
  }
  
  template<>
  unsigned Element::deserialize_bytes<long>(const char* bytes)
  {
    m_data = make_void_shared(_from_bytes<long>(bytes));
    return 8;
  }
  
  template<>
  void Element::serialize_bson<long>(std::ostringstream& oss) const
  {
    _to_stream(oss, *(std::static_pointer_cast<long>(m_data)));
    return;
  }
  
  template <>
  std::string Element::_to_std_str<long>() const
  {
    std::ostringstream oss;
    oss << *(std::static_pointer_cast<long>(m_data));
    return oss.str();
  }
  
  //Assumption: int maps to a 32 bit integer.  There probably needs to be a better way to do this (preprocessor?)
  template<>
  TypeInfo default_type<int>()
  {
    return INT32;
  }
  
  template<>
  std::string to_string<int>()
  {
    return "int";
  }
  
  template <>
  bool Element::check_convert<int>() const
  {
    return m_type == INT32;
  }
  //And... shorts.  Which will map to an int32
  template<>
  TypeInfo default_type<short>()
  {
    return INT32;
  }
  
  template<>
  std::string to_string<short>()
  {
    return "short";
  }
  
  template <>
  bool Element::check_convert<short>() const
  {
    return m_type == INT32;
  }
    template<>
  unsigned Element::deserialize_bytes<int>(const char* bytes)
  {
    m_data = make_void_shared(_from_bytes<int>(bytes));
    return 8;
  }
  
  template<>
  void Element::serialize_bson<int>(std::ostringstream& oss) const
  {
    _to_stream(oss, *(std::static_pointer_cast<int>(m_data)));
    return;
  }
  
  template <>
  std::string Element::_to_std_str<int>() const
  {
    std::ostringstream oss;
    oss << *(std::static_pointer_cast<int>(m_data));
    return oss.str();
  }
}