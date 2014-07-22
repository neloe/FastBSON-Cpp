/*!
 * \file element.hpp
 * \author Nathan Eloe
 * \brief Implementation of the BSON element class
 */

#pragma once

#include "element.h"
#include "typeinfo.h"
#include <memory>

namespace bson
{
  // Constructors
  template <typename T>
  Element::Element(const T& data, const TypeInfo & type): m_type(type)
  {
    if (!m_type)
      m_type = default_type<T>();
    type_check<T>();
    m_data = std::static_pointer_cast<void>(std::make_shared<T> (data));
  }
  
  template <typename T>
  const T& Element::data() const
  {
    type_check<T>();
    return *(std::static_pointer_cast<T>(m_data));
  }
  
  template <typename T>
  void Element::type_check() const
  {
    if (!check_convert<T>())
      throw type_error<T>(m_type);
  }
  
  unsigned Element::from_bytes(const char* bytes, const TypeInfo & type)
  {
    unsigned num_bytes = -1;
    m_type = type;
    switch (m_type)
    {
      case INT64: case DATETIME: case TIMESTAMP:
	num_bytes = deserialize_bytes<long>(bytes);
	break;
      case INT32:
	num_bytes = deserialize_bytes<int>(bytes);
	break;
      case STRING: case JS: case DEPRECATED:
	num_bytes = deserialize_bytes<std::string>(bytes);
	break;
      case BOOL:
	num_bytes = deserialize_bytes<bool>(bytes);
	break;
      case FLOATING:
	num_bytes = deserialize_bytes<double>(bytes);
	break;
    }
    return num_bytes;
  }
}