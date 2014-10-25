/*
  Copyright (c) Nathan Eloe, 2014
  This file is part of FastBSON-Cpp.

  FastBSON-Cpp is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FastBSON-Cpp is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with FastBSON-Cpp.  If not, see <http://www.gnu.org/licenses/>.
*/
/*!
 * \file floats.cpp
 * \author Nathan Eloe
 * \brief integer template specializations
 */

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
  unsigned Element::deserialize_bytes<long>(const unsigned char* bytes)
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
  unsigned Element::deserialize_bytes<int>(const unsigned char* bytes)
  {
    m_data = make_void_shared(_from_bytes<int>(bytes));
    return 4;
  }
  
  template<>
  void Element::serialize_bson<int>(std::ostringstream& oss) const
  {
    _to_stream(oss, static_cast<int>(*(std::static_pointer_cast<short>(m_data))));
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