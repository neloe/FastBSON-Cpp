/*!
 * \file typeinfo.hpp
 * \author Nathan Eloe
 * \brief Implementation of functions relating to typeinfo
 */

#pragma once

#include <string>
#include "element.h"

namespace bson
{
  std::string toString(const TypeInfo & ti)
  {
    static const std::string NAMES[] = {"unknown", "floating point number", "string", "document", "array",
                                        "binary data", "undefined", "object ID", "boolean", "datetime",
					"null value", "regular expression", "database pointer",
					"javascript code", "depreicated", "scoped javascript", "int 32",
					"timestamp", "int64"};
    return (ti == 0xFF?"max key": (ti == 0x7F?"min key": NAMES[ti]));
  }
  
  //type traits name functions
  template <>
  std::string toString<double>()
  {
    return "double";
  }
  
  //Default type functions
  template<>
  TypeInfo default_type<double>()
  {
    return FLOATING;
  }
}