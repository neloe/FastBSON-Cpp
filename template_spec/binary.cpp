/*!
 * \file binary.cpp
 * \author Nathan Eloe
 * \brief binary template specializations
 */


#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <string>
#include <memory>

namespace bson
{
  template<>
  TypeInfo default_type<binary>()
  {
    return BINARY;
  }
  
  template<>
  std::string to_string<binary>()
  {
    return "std::pair<char, std::string>";
  }
  
  template<>
  bool Element::check_convert<binary>() const
  {
    return m_type == BINARY;
  }
  
  template<>
  unsigned Element::deserialize_bytes<binary>(const unsigned char* bytes)
  {
    binary data;
    int size;
    std::memcpy(&size, bytes, 4);
    data.first = bytes[5];
    data.second = std::string((char*)bytes + 5, size);
    m_data = make_void_shared(data);
    return size + 5;
  }
  
  template<>
  void Element::serialize_bson<binary>(std::ostringstream& oss) const
  {
    std::shared_ptr<binary> data(std::static_pointer_cast<binary>(m_data));
    _to_stream(oss, static_cast<int>(data->second.size()));
    oss << data -> first;
    for (int i=0; i<data->second.size(); i++) //Have to avoid that stupid  null at the end of the string
      oss << data->second[i];
    return;
  }
  
  template<>
  std::string Element::_to_std_str<binary>() const
  {
    std::ostringstream oss;
    std::shared_ptr<binary> data(std::static_pointer_cast<binary>(m_data));
    oss << "binary : { size : " << data->second.size() << ", type : "
        << data -> first << ", bytes : " << data -> second << " }";
    return oss.str();
  }
}