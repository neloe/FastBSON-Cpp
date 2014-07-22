/*!
 * \file floats.hpp
 * \author Nathan Eloe
 * \brief Document template specializations
 */

#pragma once
#include "../document.h"
#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <cstring>
namespace bson 
{
  //Element specific extension functions
  template<>
  TypeInfo default_type<Document>()
  {
    return DOCUMENT;
  }
  
  template<>
  std::string to_string<Document>()
  {
    return "bson::Document";
  }
  
  template<>
  bool Element::check_convert<Document>() const
  {
    return m_type == DOCUMENT;
  }
  
  template<>
  unsigned Element::deserialize_bytes<Document>(const char* bytes)
  {
    int32_t size;
    memcpy(&size, bytes, 4);
    char* str = new char[size];
    std::memcpy(str, bytes, size);
    char* iter = str + 4;
    int consumed = 4;
    int added;
    TypeInfo ti;
    while (consumed < size)
    {
      Element e;
      ti = static_cast<TypeInfo>(iter[0]);
      iter ++;
      std::string name(iter);
      iter += name.size() + 1;
      added = e.from_bytes(iter, ti);
      iter += added;
      consumed += added + name.size() + 1;
      (*(std::static_pointer_cast<Document>(m_data))).add(name, e);
    }
    
    delete[] str;
    return 0;
  }
  
  template<>
  void Element::serialize_bson<Document>(std::ostringstream& oss) const
  {
    std::string serialized;
    std::ostringstream data_ser;
    for (const std::pair<std::string, Element> & p: (*(std::static_pointer_cast<Document>(m_data))).m_data)
    {
      data_ser << to_char(p.second.m_type) << p.first << '\0';
      p.second.to_sstream(data_ser);
    }
    oss << static_cast<int>(data_ser.str().size()) + 5 << data_ser.str() << '\0';
    return;
  }
}