/*!
 * \file bools.cpp
 * \author Nathan Eloe
 * \brief boolean template specializations
 */


#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"

namespace bson
{
  template<>
  TypeInfo default_type<bool>()
  {
    return BOOL;
  }
  
  template <>
  std::string to_string<bool>()
  {
    return "bool";
  }
  
  template <>
  bool Element::check_convert<bool>() const
  {
    return m_type == BOOL;
  }
  
  template<>
  unsigned Element::deserialize_bytes<bool>(const unsigned char* bytes)
  {
    m_data = make_void_shared(bytes[0]);
    return 1;
  }
  
  template<>
  void Element::serialize_bson<bool>(std::ostringstream& oss) const
  {
    char truth = 0 + *(std::static_pointer_cast<bool>(m_data));
    oss << truth;
    return;
  }
  
  template <>
  std::string Element::_to_std_str<bool>() const
  {
    return *(std::static_pointer_cast<bool>(m_data))? "true" : "false";
  }
}