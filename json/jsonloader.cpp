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
 * \file jsonloader.cpp
 * \author Nathan Eloe
 * \brief Implementation of the JSON Loader class
 */

#include "jsonloader.h"
#include <sstream>

namespace bson
{
  const Document& JSON_Loader::parse(const std::string& jsonstr)
  {
    std::istringstream iss;
    iss.str(jsonstr);
    return parse(iss);
  }
  const Document& JSON_Loader::parse(std::istream& jsonstream)
  {
    scanner = std::shared_ptr<JSON_Scanner>(new JSON_Scanner(jsonstream));
    parser = std::shared_ptr<JSON_Parser>(new JSON_Parser(*scanner, *this));
    parser->parse();
    //TODO handle errors here
    return m_doc;
  }
}

