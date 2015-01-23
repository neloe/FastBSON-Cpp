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
 * \file jsscope.cpp
 * \author Nathan Eloe
 * \brief Javascript code with scope template specializations
 */

#include "../typeinfo.h"
#include "convert_utils.h"
#include "../element.h"
#include <string>
#include <memory>

namespace bson
{

    template<>
    TypeInfo default_type<jscode_scope>()
    {
        return JS_SCOPE;
    }

    template<>
    std::string to_string<jscode_scope>()
    {
        return "std::pair<std::string, bson::Document>";
    }

    template<>
    bool Element::check_convert<jscode_scope>() const
    {
        return m_type == JS_SCOPE;
    }

    template<>
    unsigned Element::deserialize_bytes<jscode_scope> (const unsigned char *bytes)
    {
        m_data = std::shared_ptr<jscode_scope> (new jscode_scope);
        std::shared_ptr<jscode_scope> data (std::static_pointer_cast<jscode_scope> (m_data));
        Element e;
        int size;
        std::memcpy (&size, bytes + 4, 4);
        data->first = std::string ((char *)bytes + 8, size - 1);
        size += 8;
        size += e.decode (bytes + size, DOCUMENT);
        e.data (data->second);
        return size;
    }

    template<>
    void Element::serialize_bson<jscode_scope> (std::ostringstream &oss) const
    {
        std::shared_ptr<jscode_scope> data (std::static_pointer_cast<jscode_scope> (m_data));
        std::ostringstream temp;
        _to_stream (temp, data -> first);
        //_to_stream(temp, data -> second);
        Element::encode (temp, data->second);
        _to_stream (oss, static_cast<int> (temp.tellp()) + 4);
        oss << temp.str();
        return;
    }

    template<>
    std::string Element::_to_std_str<jscode_scope>() const
    {
        std::ostringstream oss;
        std::shared_ptr<jscode_scope> data (std::static_pointer_cast<jscode_scope> (m_data));
        Element e (data->second);
        oss << "js_scope : { code : " << data->first << ", mapping : "
            << static_cast<std::string> (e) << " }";
        return oss.str();
    }
}