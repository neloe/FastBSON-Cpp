/*!
 * \file convert_utils.h
 * \author Nathan Eloe
 * \brief Implementation of conversion utility functions
 */

#pragma once

#include <cstring>
#include <memory>
#include <boost/concept_check.hpp>
#include <iostream>

namespace bson
{
  /*!
   * \brief converts a value directly to its byte representation
   * \pre the bytes array has at least sizeof(T) bytes allocated
   * \post copies the bytes contained in data to the bytes array
   */
  template <class T>
  void _to_bytes(char* bytes, const T& data)
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
  std::shared_ptr<void> make_void_shared(const T& data)
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
  T _from_bytes(const char* bytes)
  {
    T* dataptr = new T;
    std::memcpy(dataptr, bytes, sizeof(T));
    T data = *dataptr;
    delete dataptr;
    return data;
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
  
  /*!
   * \brief outputs the bson contained in the stream to the screen (for debug)
   * \pre None
   * \post the byte representation of stream is output to the screen
   */
  void printbson(std::ostringstream& ss)
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
}