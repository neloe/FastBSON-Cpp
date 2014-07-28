/*!
 * \file element.hpp
 * \author Nathan Eloe
 * \brief Implementation of the BSON element class
 */

#pragma once
#include "element.h"
#include "typeinfo.h"
#include <memory>
#include <vector>

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
}