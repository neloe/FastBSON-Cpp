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
 * \file chararrs.hpp
 * \author Nathan Eloe
 * \brief std::array<char, 12> template specializations
 */
#pragma once
#include "../element.h"
#include <array>
#include <string>

namespace bson
{
  template<>
  TypeInfo default_type<oid>();
  template<>
  std::string to_string<oid>();
  template<>
  bool Element::check_convert<oid>() const;
  template<>
  unsigned Element::deserialize_bytes<oid>(const unsigned char* bytes);
  template<>
  void Element::serialize_bson<oid>(std::ostringstream& oss) const;
  template<>
  std::string Element::_to_std_str<oid>() const;
}
