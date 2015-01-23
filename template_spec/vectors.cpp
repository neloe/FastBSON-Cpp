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
 * \file vectors.hpp
 * \author Nathan Eloe
 * \brief array template specializations
 */

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <string>
#include <vector>

namespace bson
{
    template<>
    TypeInfo default_type<array>()
    {
        return ARRAY;
    }

    template<>
    std::string to_string<array>()
    {
        return "std::vector<bson::Element>";
    }

    template<>
    bool Element::check_convert<array>() const
    {
        return m_type == ARRAY;
    }

    template<>
    unsigned Element::deserialize_bytes<array> (const unsigned char *bytes)
    {
        Document d;
        TypeInfo ti;
        Element e;
        int32_t size, consumed = 4;
        memcpy (&size, bytes, 4);
        size --;
        m_data = std::shared_ptr<array> (new array);
        while (consumed < size)
        {
            ti = static_cast<TypeInfo> (* (bytes + consumed));
            std::string name ((char *)bytes + (++consumed));
            consumed += name.size() + 1;
            consumed  += e.decode (bytes + consumed, ti);
            std::static_pointer_cast<array> (m_data) -> emplace_back (e);
        }
        return consumed + 1;
    }

    template<>
    void Element::serialize_bson<array> (std::ostringstream &oss) const
    {
        int index = 0;
        std::ostringstream data_ser;
        for (const Element &e : * (std::static_pointer_cast<array> (m_data)))
        {
            data_ser << to_char (e.m_type) << itos (index++) << X00;
            e.encode (data_ser);
        }
        _to_stream (oss, static_cast<int> (5 + data_ser.tellp()));
        oss << data_ser.str() << X00;
        return;
    }

    template <>
    std::string Element::_to_std_str<array>() const
    {
        std::ostringstream oss;
        int size = std::static_pointer_cast<array> (m_data) -> size();
        oss << "[ ";
        if (size > 0)
            oss << static_cast<std::string> ((* (std::static_pointer_cast<array> (m_data)))[0]);
        for (int i = 1; i < size; i++)
            oss << ", " << static_cast<std::string> ((* (std::static_pointer_cast<array> (m_data)))[i]);
        oss << " ]";
        return oss.str();
    }
}