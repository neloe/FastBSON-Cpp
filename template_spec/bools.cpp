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
 * \file bools.cpp
 * \author Nathan Eloe
 * \brief boolean template specializations
 */


#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"

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
  unsigned Element::deserialize_bytes<bool>(const unsigned char* bytes)
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
  
  template <>
  std::string Element::_to_std_str<bool>() const
  {
    return *(std::static_pointer_cast<bool>(m_data))? "true" : "false";
  }
}