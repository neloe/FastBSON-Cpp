/*!
 * \file pairs.hpp
 * \author Nathan Eloe
 * \brief template specializations or pair type objects
 */

#pragma once

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <memory>

namespace bson 
{
  template<>
  TypeInfo default_type<std::pair<std::string, std::string>>()
  {
    return REGEX;
  }
  
  template<>
  std::string to_string<std::pair<std::string, std::string>>()
  {
    return "std::pair<std::string, std::string>>";
  }
  
  template<>
  bool Element::check_convert<std::pair<std::string, std::string>>() const
  {
    return m_type == REGEX;
  }
  
  template<>
  unsigned Element::deserialize_bytes<std::pair<std::string, std::string>>(const char* bytes)
  {
    int size;
    m_data = std::shared_ptr<std::pair<std::string, std::string>>(new std::pair<std::string, std::string>);
    std::static_pointer_cast<std::pair<std::string, std::string>>(m_data) -> first = std::string(bytes);
    size = (std::static_pointer_cast<std::pair<std::string, std::string>>(m_data) -> first).size() + 1;
    std::static_pointer_cast<std::pair<std::string, std::string>>(m_data) -> second = std::string(bytes + size);
    size += (std::static_pointer_cast<std::pair<std::string, std::string>>(m_data) -> second).size() + 1;
    return size;
  }
  
  template<>
  void Element::serialize_bson<std::pair<std::string, std::string>>(std::ostringstream& oss) const
  {
    oss << std::static_pointer_cast<std::pair<std::string, std::string>>(m_data) -> first << X00
        << std::static_pointer_cast<std::pair<std::string, std::string>>(m_data) -> second << X00;
  }
  
  template<>
  std::string Element::_to_std_str<std::pair<std::string, std::string>>() const
  {
    std::ostringstream oss;
    oss << "regex: [ ";
    oss << std::static_pointer_cast<std::pair<std::string, std::string>>(m_data) -> first << ", "
        << std::static_pointer_cast<std::pair<std::string, std::string>>(m_data) -> second << " ]";
    return oss.str();
  }
}
