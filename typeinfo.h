/*!
 * \file typeinfo.h
 * \author Nathan Eloe
 * \brief Enumeration to keep track of types for bson
 */

#pragma once

#include <exception>
#include <string>

namespace bson
{
  enum TypeInfo {_UNKNOWN=0, FLOATING=1, STRING, DOCUMENT, ARRAY, BINARY, UNDEF, OID, BOOL, DATETIME,
                 NIL, REGEX, DBPTR, JS, DEPRECATED, JS_SCOPE, INT32, TIMESTAMP, INT64, 
		 MINKEY=0xFF, MAXKEY=0x7F
  };
  
  std::string toString(const TypeInfo & ti);
  
  template <typename T>
  std::string toString();
  
  template <typename T>
  TypeInfo default_type();
  
  template <class T>
  class type_error: public std::exception
  {
    public:
      type_error(const TypeInfo & ti): m_ti(ti) {}
      virtual const char* what() const noexcept
      {
	std::string err = "Invalid conversion from C++ type: " + toString<T>() + " to BSON type: " + toString(m_ti);
	return err.c_str();
      }
    private:
      TypeInfo m_ti;
  };
  

}

#include "typeinfo.hpp"