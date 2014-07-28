/*!
 * \file typeinfo.h
 * \author Nathan Eloe
 * \brief Enumeration to keep track of types for bson
 */

#pragma once

#include <exception>
#include <string>
#include <boost/concept_check.hpp>

namespace bson
{
  const std::string NAMES[] = {"unknown", "floating point number", "string", "document", "array",
                                        "binary data", "undefined", "object ID", "boolean", "datetime",
					"null value", "regular expression", "database pointer",
					"javascript code", "depreicated", "scoped javascript", "int 32",
					"timestamp", "int64"};
  enum TypeInfo {_UNKNOWN=0, FLOATING=1, STRING, DOCUMENT, ARRAY, BINARY, UNDEF, OID, BOOL, DATETIME,
                 NIL, REGEX, DBPTR, JS, DEPRECATED, JS_SCOPE, INT32, TIMESTAMP, INT64, 
		 MINKEY=0xFF, MAXKEY=0x7F
  };
  
  inline char to_char(const TypeInfo & ti)
  {
    return static_cast<char>((int)ti);
  }
  
  //forward declaration
  template <class T>
  std::string to_string();
  
  inline std::string to_string(const TypeInfo & ti)
  {
    return (ti == 0xFF?"max key": (ti == 0x7F?"min key": NAMES[ti]));
  }
  
  template <class T>
  class type_error: public std::exception
  {
    public:
      type_error(const TypeInfo & ti): m_ti(ti) {}
      virtual const char* what() const noexcept
      {
	std::string err = "Invalid conversion from C++ type: " + to_string<T>() + " to BSON type: " + to_string(m_ti);
	return err.c_str();
      }
    private:
      TypeInfo m_ti;
  };
  
  class type_UNKNOWN: public std::exception
  {
    public:
      virtual const char* what() const noexcept
      {
	return "_UNKNOWN type not implemented";
      }
  };

  
  
}