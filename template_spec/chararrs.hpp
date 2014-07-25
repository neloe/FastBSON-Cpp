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
  TypeInfo default_type<oid>()
  {
    return OID;
  }
  
  template<>
  std::string to_string<oid>()
  {
    return "oid";
  }
  
  template<>
  bool Element::check_convert<oid>() const
  {
    return m_type == OID;
  }
  
  template<>
  unsigned Element::deserialize_bytes<oid>(const char* bytes)
  {
    m_data = std::shared_ptr<oid>(new oid);
    std::memcpy(&(*(std::static_pointer_cast<oid>(m_data)))[0], bytes, OID_SIZE);
    return 0;
  }
  
  template<>
  void Element::serialize_bson<oid>(std::ostringstream& oss) const
  {
    for (const char& c: *(std::static_pointer_cast<oid>(m_data)))
      oss << c;
    return;
  }
  
  template<>
  std::string Element::_to_std_str<oid>() const
  {
    std::ostringstream oss;
    serialize_bson<oid>(oss);
    return oss.str();
  }
}