/*!
 * \file chararrs.hpp
 * \author Nathan Eloe
 * \brief Javascript code with scope template specializations
 */

#pragma once

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <string>
#include <memory>

namespace bson
{
  struct jscode_scope
  {
    int m_size;
    std::string m_code;
    Document m_mapping;
  };

  template<>
  TypeInfo default_type<jscode_scope>()
  {
    return JS_SCOPE;
  }
  
  template<>
  std::string to_string<jscode_scope>()
  {
    return "javascript code with scope";
  }
  
  template<>
  bool Element::check_convert<jscode_scope>() const
  {
    return m_type == JS_SCOPE;
  }
  
  template<>
  unsigned Element::deserialize_bytes<jscode_scope>(const char* bytes)
  {
    m_data = std::shared_ptr<jscode_scope>(new jscode_scope);
    Element e;
    int size;
    std::memcpy(&size, bytes, 4);
    std::static_pointer_cast<jscode_scope>(m_data)->m_size = size;
    std::static_pointer_cast<jscode_scope>(m_data)->m_code = std::string(bytes + 4, size);
    size += e.decode(bytes + 5 + size, DOCUMENT);
    e.data(std::static_pointer_cast<jscode_scope>(m_data)->m_mapping);
    return size + 5;
  }
  
  template<>
  void Element::serialize_bson<jscode_scope>(std::ostringstream& oss) const
  {
    std::shared_ptr<jscode_scope> data(std::static_pointer_cast<jscode_scope>(m_data));
    _to_stream(oss, data->m_size);
    _to_stream(oss, data->m_code);
    _to_stream(oss, data->m_mapping);
    return;
  }
  
  template<>
  std::string Element::_to_std_str<jscode_scope>() const
  {
    std::ostringstream oss;
    std::shared_ptr<jscode_scope> data(std::static_pointer_cast<jscode_scope>(m_data));
    Element e(data->m_mapping);
    oss << "js_scope : { size : " << data->m_size << ", code : " << data->m_code << ", mapping : "
        << static_cast<std::string>(e) << " }";
    return oss.str();
  }
}