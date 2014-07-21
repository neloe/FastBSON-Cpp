/*!
 * \file floats.hpp
 * \author Nathan Eloe
 * \brief floating point template specializations
 */

#pragma once

#include "../typeinfo.h"

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
}