/*!
 * 
 */

#pragma once

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <string>
#include <vector>

namespace bson 
{
  template<>
  TypeInfo default_type<std::vector<Element>>()
  {
    return ARRAY;
  }
  
  template<>
  std::string to_string<std::vector<Element>>()
  {
    return "std::vector<bson::Element>";
  }
  
  template<>
  bool Element::check_convert<std::vector<Element>>() const
  {
    return m_type == ARRAY;
  }
  
  template<>
  unsigned Element::deserialize_bytes<std::vector<Element>>(const char* bytes)
  {
    TypeInfo ti;
    Element e;
    int32_t size, consumed = 4, added;
    memcpy(&size, bytes, 4);
    std::unique_ptr<char> str(new char[size]);
    std::memcpy(str.get(), bytes, size);
    char* iter = str.get() + 4;
    size --;
    m_data = std::shared_ptr<std::vector<Element>>(new std::vector<Element>);
    while (consumed < size)
    {
      ti = static_cast<TypeInfo>(*(iter++));
      std::string index(iter); //ignore this, we know it will be the index;
      iter += index.size() + 1;
      added = e.decode(iter, ti);
      iter += added;
      consumed += (added + index.size() + 2);
      std::static_pointer_cast<std::vector<Element>>(m_data) -> push_back(e);
    }
    return consumed + 1;
  }
  
  template<>
  void Element::serialize_bson<std::vector<Element>>(std::ostringstream& oss) const
  {
    int size = std::static_pointer_cast<std::vector<Element>>(m_data) -> size();
    int index = 0;
    std::ostringstream data_ser;
    for (const Element & e: *(std::static_pointer_cast<std::vector<Element>>(m_data)))
    {
      data_ser << to_char(e.m_type) << itos(index++) << X00;
      e.encode(data_ser);
    }
    _to_stream(oss, static_cast<int>(5 + data_ser.tellp()));
    oss << data_ser.str() << X00;
    return;
  }
  
  template <>
  std::string Element::_to_std_str<std::vector<Element>>() const
  {
    std::ostringstream oss;
    int size = std::static_pointer_cast<std::vector<Element>>(m_data) -> size();
    oss << "[ ";
    if (size > 0)
      oss << static_cast<std::string>((*(std::static_pointer_cast<std::vector<Element>>(m_data)))[0]);
    for (int i=0; i < size; i++)
    {
      oss << ", " << static_cast<std::string>((*(std::static_pointer_cast<std::vector<Element>>(m_data)))[i]);
    }
    oss << " ]";
    return oss.str();
  }
}