/*!
 * \file convert_utils.h
 * \author Nathan Eloe
 * \brief Implementation of conversion utility functions
 */

#pragma once

#include <cstring>
#include <memory>
#include <boost/concept_check.hpp>

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
}