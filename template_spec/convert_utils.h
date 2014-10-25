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
 * \file convert_utils.h
 * \author Nathan Eloe
 * \brief Implementation of conversion utility functions
 */

#pragma once

#include "../element.h"
#include <cstring>
#include <memory>
#include <iostream>

namespace bson
{
  /*!
   * \brief converts a value directly to its byte representation
   * \pre the bytes array has at least sizeof(T) bytes allocated
   * \post copies the bytes contained in data to the bytes array
   */
  template <class T>
  inline void _to_bytes(unsigned char* bytes, const T& data)
  {
    std::memcpy(bytes, &data, sizeof(T));
    return;
  }
  
  /*!
   * \brief creates a void shared pointer from the provided data
   * \pre None
   * \post None
   * \return a shared void pointer pointing at the data
   */
  template <class T>
  inline std::shared_ptr<void> make_void_shared(const T& data)
  {
    return std::static_pointer_cast<void>(std::make_shared<T>(data));
  }
  
  /*!
   * \brief converts a byte array to type T (direct copying)
   * \pre bytes has at least sizeof(T) spaces allocated)
   * \post None
   * \return the data that is the bytes in the array, but as type T
   */
  template <class T>
  T _from_bytes(const unsigned char* bytes)
  {
    T data;
    std::memcpy(&data, bytes, sizeof(T));
    return data;
  }
  
  /*!
   * \brief inserts the bytes of the NTCA v in into the stream
   * \pre v must be null terminated
   * \post the byte representation of object v is inserted into the stream
   */
  inline void _to_stream(std::ostringstream& ss, const char* v)
  {
    ss << v << X00;
  }
  inline void _to_stream(std::ostringstream& ss, const unsigned char* v)
  {
    ss << v << X00;
  }
  
  /*!
   * \brief inserts the bytes of object v in into the stream
   * \pre None
   * \post the byte representation of object v is inserted into the stream
   */
  template <class T>
  void _to_stream(std::ostringstream& ss, const T& v)
  {
    char* it = (char*)(&v);
    for (int i=0; i<sizeof(T); ++i, ++it)
      ss << *it;
  }
  
  template <>
  inline void _to_stream(std::ostringstream& ss, const std::string & v)
  {
    _to_stream(ss, static_cast<u_int32_t>(v.size()) + 1); //the +1 handles the null at the end
    _to_stream(ss, v.c_str());
  }
  
  template <int ARRSIZE>
  inline void _to_stream(std::ostringstream& ss, const std::array<char, ARRSIZE> & v)
  {
    for (const char c: v)
      ss << v;
    return;
  }
  
  /*!
   * \brief outputs the bson contained in the stream to the screen (for debug)
   * \pre None
   * \post the byte representation of stream is output to the screen
   */
  inline void printbson(std::ostringstream& ss)
  {
    for (int i=0; i<ss.tellp(); i++)
    {
      char ch = ss.str()[i];
      if (isalpha(ch) || ch == '$' || ch == '.')
	std::cout << ch;
      else
	std::cout << std::hex << static_cast<int>(ch);
      std::cout << " ";
    }
    std::cout << std::endl;
  }
  
  /*!
   * \brief converts integers to strings
   * \pre None
   * \post None
   * \return the string representation of the integer
   */
  inline std::string itos(const int& a)
  {
    std::ostringstream oss;
    oss << a;
    return oss.str();
  }
}
