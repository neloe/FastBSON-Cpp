/*!
 * \file element.h
 * \author Nathan Eloe
 * \brief Declaration of a BSON element
 */

#pragma once

#include "typeinfo.h"
#include <memory>

namespace bson
{

  class Element
  {
    public:
      Element(): m_data(nullptr), m_type(_UNKNOWN) {}
      
      template <typename T>
      Element(const T& data, const TypeInfo & type = _UNKNOWN);
      
      template <typename T>
      const T& data() const;
      template <typename T>
      void data(T& t) const {t = data<T>();}
      
    private:
      std::shared_ptr<void> m_data;
      TypeInfo m_type;
      
      template <typename T>
      bool check_convert() const;
      
      template <typename T>
      void type_check() const;
  };

  template <typename T>
  std::string to_string();
  
  template <typename T>
  TypeInfo default_type();
  
}

#include "element.hpp"
#include "template_spec/floats.hpp"
#include "template_spec/strings.hpp"