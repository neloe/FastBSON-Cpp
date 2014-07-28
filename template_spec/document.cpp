/*!
 * \file document.cpp
 * \author Nathan Eloe
 * \brief Document template specializations
 */

#include "../document.h"
#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <cstring>
#include <iostream>

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
  unsigned Element::deserialize_bytes<Document>(const unsigned char* bytes)
  {
    Document d;
    TypeInfo ti;
    Element e;
    int32_t size, consumed = 4;
    memcpy(&size, bytes, 4);
    size --;
    m_data = std::shared_ptr<Document>(new Document);
    while (consumed < size - 1)
    {
      ti = static_cast<TypeInfo>(*(bytes + consumed));
      std::string name((char*)bytes + (++consumed));
      consumed += name.size() + 1;
      consumed  += e.decode(bytes + consumed, ti);
      std::static_pointer_cast<Document>(m_data)->add(name, e);
    }
    return consumed + 1;
  }
  
  template<>
  void Element::serialize_bson<Document>(std::ostringstream& oss) const
  {
    std::ostringstream data_ser;
    for (const std::pair<std::string, Element> & p: (*(std::static_pointer_cast<Document>(m_data))).m_data)
    {
      data_ser << to_char(p.second.m_type) << p.first << X00;
      p.second.encode(data_ser);
    }
    _to_stream(oss, static_cast<int>(5 + data_ser.tellp()));
    oss << data_ser.str() << X00;
    return;
  }
  
  template <>
  std::string Element::_to_std_str<Document>() const
  {
    std::ostringstream oss;
    bool first = true;
    oss << "{ ";
    for (const std::pair<std::string, Element>& p: std::static_pointer_cast<Document>(m_data)->m_data)
    {
      if (!first)
      {
	oss << ", ";
	first = false;
      }
      oss << p.first << " : " << static_cast<std::string>(p.second);
    }
    oss << " }";
    return oss.str();
  }
}
