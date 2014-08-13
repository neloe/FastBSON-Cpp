/*!
 * \file jsscope.cpp
 * \author Nathan Eloe
 * \brief Javascript code with scope template specializations
 */

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <string>
#include <memory>

namespace bson
{

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
  unsigned Element::deserialize_bytes<jscode_scope>(const unsigned char* bytes)
  {
    m_data = std::shared_ptr<jscode_scope>(new jscode_scope);
    std::shared_ptr<jscode_scope> data(std::static_pointer_cast<jscode_scope>(m_data));
    Element e;
    int size;
    std::memcpy(&size, bytes + 4, 4);
    data->first = std::string((char*)bytes + 8, size - 1);
    size += 8;
    size += e.decode(bytes + size, DOCUMENT);
    e.data(data->second);
    return size;
  }
  
  template<>
  void Element::serialize_bson<jscode_scope>(std::ostringstream& oss) const
  {
    std::shared_ptr<jscode_scope> data(std::static_pointer_cast<jscode_scope>(m_data));
    std::ostringstream temp;
    _to_stream(temp, data -> first);
    //_to_stream(temp, data -> second);
    Element::encode(temp, data->second);
    _to_stream(oss, static_cast<int>(temp.tellp()) + 4);
    oss << temp.str();
    return;
  }
  
  template<>
  std::string Element::_to_std_str<jscode_scope>() const
  {
    std::ostringstream oss;
    std::shared_ptr<jscode_scope> data(std::static_pointer_cast<jscode_scope>(m_data));
    Element e(data->second);
    oss << "js_scope : { code : " << data->first << ", mapping : "
        << static_cast<std::string>(e) << " }";
    return oss.str();
  }
}