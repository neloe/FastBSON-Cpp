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
  template <class T>
  void _to_bytes(char* bytes, const T& data)
  {
    std::memcpy(bytes, &data, sizeof(T));
    return;
  }
  
  template <class T>
  std::shared_ptr<void> make_void_shared(const T& data)
  {
    return std::static_pointer_cast<void>(std::make_shared<T>(data));
  }
  
  template <class T>
  T _from_bytes(const char* bytes)
  {
    T* dataptr = new T;
    std::memcpy(dataptr, bytes, sizeof(T));
    T data = *dataptr;
    delete dataptr;
    return data;
  }
  
  template <class T>
  void _to_stream(std::ostringstream& ss, const T& v)
  {
    char* it = (char*)(&v);
    for (int i=0; i<sizeof(T); ++i, ++it)
      ss << *it;
  }
  
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