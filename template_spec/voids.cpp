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
 * \file voids.hpp
 * \author Nathan Eloe
 * \brief void template specializations
 */

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"

namespace bson
{
    template<>
    TypeInfo default_type<void>()
    {
        return NIL;
    }

    template <>
    std::string to_string<void>()
    {
        return "void";
    }

    template <>
    bool Element::check_convert<void>() const
    {
        return m_type == NIL || m_type == MINKEY || m_type == MAXKEY || m_type == UNDEF;
    }

    template<>
    unsigned Element::deserialize_bytes<void> (const unsigned char *bytes)
    {
        return 0;
    }

    template<>
    void Element::serialize_bson<void> (std::ostringstream &oss) const
    {
        return;
    }

    template <>
    std::string Element::_to_std_str<void>() const
    {
        return "";
    }
}