/*!
 * \file chararrs.hpp
 * \author Nathan Eloe
 * \brief std::array<char,12> template specializations
 */

#pragma once

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <string>
#include <array>

namespace bson
{
  template<>
  TypeInfo default_type<std::array<char, OID_SIZE>>()
  {
    return OID;
  }
  
  template<>
  std::string to_string<std::array<char, OID_SIZE>>()
  {
    return "std::array<char, OID_SIZE>";
  }
  
  template<>
  bool Element::check_convert<std::array<char, OID_SIZE>>() const
  {
    return m_type == OID;
  }
  
  template<>
  unsigned Element::deserialize_bytes<std::array<char, OID_SIZE>>(const char* bytes)
  {
    m_data = std::shared_ptr<std::array<char, OID_SIZE>>(new std::array<char, OID_SIZE>);
    std::memcpy(&(*(std::static_pointer_cast<std::array<char, OID_SIZE>>(m_data)))[0], bytes, OID_SIZE);
    return 0;
  }
  
  template<>
  void Element::serialize_bson<std::array<char, OID_SIZE>>(std::ostringstream& oss) const
  {
    for (const char& c: *(std::static_pointer_cast<std::array<char, OID_SIZE>>(m_data)))
      oss << c;
    return;
  }
  
  template<>
  std::string Element::_to_std_str<std::array<char, OID_SIZE>>() const
  {
    std::ostringstream oss;
    serialize_bson<std::array<char, OID_SIZE>>(oss);
    return oss.str();
  }
}