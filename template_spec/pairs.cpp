/*!
 * \file pairs.cpp
 * \author Nathan Eloe
 * \brief template specializations or pair type objects
 */

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <memory>

namespace bson 
{
  //regexes
  template<>
  TypeInfo default_type<regex>()
  {
    return REGEX;
  }
  
  template<>
  std::string to_string<regex>()
  {
    return "regex>";
  }
  
  template<>
  bool Element::check_convert<regex>() const
  {
    return m_type == REGEX;
  }
  
  template<>
  unsigned Element::deserialize_bytes<regex>(const char* bytes)
  {
    int size;
    m_data = std::shared_ptr<regex>(new regex);
    std::static_pointer_cast<regex>(m_data) -> first = std::string(bytes);
    size = (std::static_pointer_cast<regex>(m_data) -> first).size() + 1;
    std::static_pointer_cast<regex>(m_data) -> second = std::string(bytes + size);
    size += (std::static_pointer_cast<regex>(m_data) -> second).size() + 1;
    return size;
  }
  
  template<>
  void Element::serialize_bson<regex>(std::ostringstream& oss) const
  {
    _to_stream(oss, std::static_pointer_cast<regex>(m_data) -> first);
    _to_stream(oss, std::static_pointer_cast<regex>(m_data) -> second);
    return;
  }
  
  template<>
  std::string Element::_to_std_str<regex>() const
  {
    std::ostringstream oss;
    oss << "regex: [ ";
    oss << std::static_pointer_cast<regex>(m_data) -> first << ", "
        << std::static_pointer_cast<regex>(m_data) -> second << " ]";
    return oss.str();
  }
  
  // dbpointers
  template<>
  TypeInfo default_type<dbptr>()
  {
    return DBPTR;
  }
  
  template<>
  std::string to_string<dbptr>()
  {
    return "dbptr>";
  }
  
  template<>
  bool Element::check_convert<dbptr>() const
  {
    return m_type == DBPTR;
  }
  
  template<>
  unsigned Element::deserialize_bytes<dbptr>(const char* bytes)
  {
    int size;
    int strsize;
    memcpy(&strsize, bytes, 4);
    size += 4;
    m_data = std::shared_ptr<dbptr>(new dbptr);
    std::static_pointer_cast<dbptr>(m_data) -> first = std::string(bytes + size, strsize);
    size += strsize + 1;
    std::memcpy(&((std::static_pointer_cast<dbptr>(m_data) -> second)[0]), bytes + size, DB_PTR_SIZE);
    return size + DB_PTR_SIZE;
  }
  
  template<>
  void Element::serialize_bson<dbptr>(std::ostringstream& oss) const
  {
    _to_stream(oss, std::static_pointer_cast<dbptr>(m_data) -> first.size());
    oss << std::static_pointer_cast<dbptr>(m_data) -> first << X00;
    for (const char c: std::static_pointer_cast<dbptr>(m_data) -> second)
      oss << c;
    oss << X00;
    return;
  }
  
  template<>
  std::string Element::_to_std_str<dbptr>() const
  {
    std::ostringstream oss;
    oss << "dbptr: [ ";
    oss << std::static_pointer_cast<dbptr>(m_data) -> first << ", ";
    for (const char c: std::static_pointer_cast<dbptr>(m_data) -> second)
      oss << c;
    oss << " ]";
    return oss.str();
  }
}
