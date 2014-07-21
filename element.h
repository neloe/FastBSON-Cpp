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
      void data(T& t) const {t = data();}
      
    private:
      std::shared_ptr<void> m_data;
      TypeInfo m_type;
      
      template <typename T>
      bool check_convert() const;
      
      template <typename T>
      void type_check() const;
  };

}

#include "element.hpp"