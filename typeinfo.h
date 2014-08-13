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
  const std::string NAMES[] = {"unknown", "floating point number", "string", "document", "array",
                                        "binary data", "undefined", "object ID", "boolean", "datetime",
					"null value", "regular expression", "database pointer",
					"javascript code", "depreicated", "scoped javascript", "int32",
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
  
  class type_error: public std::exception
  {
    public:
      type_error(const TypeInfo & ti, const std::string & ctype) {m_err = "Invalid conversion between C++ type: " + ctype + " and BSON type: " + to_string(ti);}
      virtual const char* what() const noexcept
      {
	return m_err.c_str();
      }
    private:
      std::string m_err;
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