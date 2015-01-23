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
 * \file strings.cpp
 * \author Nathan Eloe
 * \brief string template specializations
 */

#include "../typeinfo.h"
#include "convert_utils.h"
#include <string>
#include <memory>
#include <cstring>
#include "../element.h"
#include <iostream>

namespace bson
{
    template<>
    TypeInfo default_type<std::string>()
    {
        return STRING;
    }

    template<>
    std::string to_string<std::string>()
    {
        return "std::string";
    }

    template <>
    bool Element::check_convert<std::string>() const
    {
        return m_type == STRING || m_type == JS || m_type == DEPRECATED;
    }

    template<>
    unsigned Element::deserialize_bytes<std::string> (const unsigned char *bytes)
    {
        int32_t size;
        memcpy (&size, bytes, 4);
        m_data = make_void_shared (std::string ((char *) (bytes + 4), size - 1)); // -1 is to avoid the trailing NULL
        return size + 4;
    }

    template<>
    void Element::serialize_bson<std::string> (std::ostringstream &oss) const
    {
        _to_stream (oss, * (std::static_pointer_cast<std::string> (m_data)));
        return;
    }

    template <>
    std::string Element::_to_std_str<std::string>() const
    {
        //Wrap this bad boy in quotes so that we match json
        return "\"" + * (std::static_pointer_cast<std::string> (m_data)) + "\"";
    }
}