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
 * \file pairs.cpp
 * \author Nathan Eloe
 * \brief template specializations or pair type objects
 */

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <memory>

namespace bson
{
    //regexes
    template<>
    TypeInfo default_type<regex>()
    {
        return REGEX;
    }

    template<>
    std::string to_string<regex>()
    {
        return "std::pair<std::string, std::string>";
    }

    template<>
    bool Element::check_convert<regex>() const
    {
        return m_type == REGEX;
    }

    template<>
    unsigned Element::deserialize_bytes<regex> (const unsigned char *bytes)
    {
        int size;
        m_data = std::shared_ptr<regex> (new regex);
        std::static_pointer_cast<regex> (m_data) -> first = std::string ((char *)bytes);
        size = (std::static_pointer_cast<regex> (m_data) -> first).size() + 1;
        std::static_pointer_cast<regex> (m_data) -> second = std::string ((char *)bytes + size);
        size += (std::static_pointer_cast<regex> (m_data) -> second).size() + 1;
        return size;
    }

    template<>
    void Element::serialize_bson<regex> (std::ostringstream &oss) const
    {
        _to_stream (oss, std::static_pointer_cast<regex> (m_data) -> first.c_str());
        _to_stream (oss, std::static_pointer_cast<regex> (m_data) -> second.c_str());
        return;
    }

    template<>
    std::string Element::_to_std_str<regex>() const
    {
        std::ostringstream oss;
        oss << "regex : [ ";
        oss << std::static_pointer_cast<regex> (m_data) -> first << ", "
            << std::static_pointer_cast<regex> (m_data) -> second << " ]";
        return oss.str();
    }

    // dbpointers
    template<>
    TypeInfo default_type<dbptr>()
    {
        return DBPTR;
    }

    template<>
    std::string to_string<dbptr>()
    {
        return "std::pair<std::string, std::array<unsigned char, 12>>";
    }

    template<>
    bool Element::check_convert<dbptr>() const
    {
        return m_type == DBPTR;
    }

    template<>
    unsigned Element::deserialize_bytes<dbptr> (const unsigned char *bytes)
    {
        int size = 0;
        int strsize;
        memcpy (&strsize, bytes, 4);
        size += 4;
        m_data = std::shared_ptr<dbptr> (new dbptr);
        std::static_pointer_cast<dbptr> (m_data) -> first = std::string ((char *)bytes + size, strsize - 1); //to avoid the trailing null
        size += strsize;
        std::memcpy (& ((std::static_pointer_cast<dbptr> (m_data) -> second)[0]), bytes + size, DB_PTR_SIZE);
        return size + DB_PTR_SIZE;
    }

    template<>
    void Element::serialize_bson<dbptr> (std::ostringstream &oss) const
    {
        _to_stream (oss, static_cast<int> (std::static_pointer_cast<dbptr> (m_data) -> first.size() + 1));
        oss << std::static_pointer_cast<dbptr> (m_data) -> first << X00;
        for (const char c : std::static_pointer_cast<dbptr> (m_data) -> second)
            oss << c;
        return;
    }

    template<>
    std::string Element::_to_std_str<dbptr>() const
    {
        std::ostringstream oss;
        oss << "dbptr : [ ";
        oss << std::static_pointer_cast<dbptr> (m_data) -> first << ", ";
        for (const char c : std::static_pointer_cast<dbptr> (m_data) -> second)
            oss << c;
        oss << " ]";
        return oss.str();
    }
}
