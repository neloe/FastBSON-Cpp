/*
  Copyright (c) Nathan Eloe, 2014
  This file is part of FastBSON-Cpp.

  FastBSON-Cpp is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FastBSON-Cpp is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with FastBSON-Cpp.  If not, see <http://www.gnu.org/licenses/>.
*/
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
                                 "timestamp", "int64"
                                };
    enum TypeInfo {_UNKNOWN = 0, FLOATING = 1, STRING, DOCUMENT, ARRAY, BINARY, UNDEF, OID, BOOL, DATETIME,
                   NIL, REGEX, DBPTR, JS, DEPRECATED, JS_SCOPE, INT32, TIMESTAMP, INT64,
                   MINKEY = 0xFF, MAXKEY = 0x7F
                  };

    /*!
     * \brief converts a type name to a string (for exceptions)
     * \pre Specialized for any and all types
     * \post None
     * \return the name of the type as a string
     */
    template <typename T>
    std::string to_string();

    /*!
     * \brief determines the default type for type T
     * \pre Specialized for types
     * \post None
     * \return the typeinfo that type T should default to.
     */
    template <typename T>
    TypeInfo default_type();

    inline char to_char (const TypeInfo &ti)
    {
        return static_cast<char> ((int)ti);
    }

    inline std::string to_string (const TypeInfo &ti)
    {
        return (ti == 0xFF ? "max key" : (ti == 0x7F ? "min key" : NAMES[ti]));
    }

    class type_error: public std::exception
    {
      public:
        type_error (const TypeInfo &ti, const std::string &ctype): m_err ("Invalid conversion between C++ type: " + ctype + " and BSON type: " + to_string (ti)) {}
        virtual const char *what() const noexcept
        {
            return m_err.c_str();
        }
      private:
        std::string m_err;
    };

    class type_UNKNOWN: public std::exception
    {
      public:
        virtual const char *what() const noexcept
        {
            return "_UNKNOWN type not implemented";
        }
    };



}