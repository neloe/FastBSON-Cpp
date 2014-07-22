/*!
 * \file element.h
 * \author Nathan Eloe
 * \brief Declaration of a BSON element
 */

#pragma once

#include "typeinfo.h"
#include <sstream>
#include <memory>

namespace bson
{

  class Element
  {
    public:
      Element(): m_data(nullptr), m_type(_UNKNOWN) {}
      
      unsigned from_bytes(const char* data, const TypeInfo & m_type);
      
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
      
      template<typename T>
      unsigned deserialize_bytes(const char* bytes);
      
      template<typename T>
      void serialize_bson(std::ostringstream& oss) const;
  };

  template <typename T>
  std::string to_string();
  
  template <typename T>
  TypeInfo default_type();
  
}

#include "template_spec/floats.hpp"
#include "template_spec/strings.hpp"
#include "template_spec/ints.hpp"
#include "template_spec/bools.hpp"
#include "element.hpp"