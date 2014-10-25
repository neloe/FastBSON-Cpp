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
 * \file chararrs.cpp
 * \author Nathan Eloe
 * \brief std::array<char,12> template specializations
 */

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <string>
#include <array>
#include <iomanip>

namespace bson
{
  template<>
  TypeInfo default_type<oid>()
  {
    return OID;
  }
  
  template<>
  std::string to_string<oid>()
  {
    return "std::array<unsigned char, 12>";
  }
  
  template<>
  bool Element::check_convert<oid>() const
  {
    return m_type == OID;
  }
  
  template<>
  unsigned Element::deserialize_bytes<oid>(const unsigned char* bytes)
  {
    m_data = std::shared_ptr<oid>(new oid);
    std::memcpy(&(*(std::static_pointer_cast<oid>(m_data)))[0], bytes, OID_SIZE);
    return OID_SIZE;
  }
  
  template<>
  void Element::serialize_bson<oid>(std::ostringstream& oss) const
  {
    _to_stream(oss, *(std::static_pointer_cast<oid>(m_data)));
    return;
  }
  
  template<>
  std::string Element::_to_std_str<oid>() const
  {
    std::ostringstream oss;
    for (int i=0; i<OID_SIZE; i++)
      oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>((*(std::static_pointer_cast<oid>(m_data)))[i]);
    return oss.str();
  }
}