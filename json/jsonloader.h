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
 * \file jsonloader.h
 * \author Nathan Eloe
 * \brief An interface to the flex/bison implementation of the JSON parser
 */
#pragma once

#include <memory>
#include "../document.h"
#include "jsonscanner.h"
#include "json.tab.hpp"

namespace bson
{
  class JSON_Loader
  {
    public:
      JSON_Loader(): m_doc(), parser(nullptr), scanner(nullptr) {}
      virtual ~JSON_Loader() {}
      
      void set_doc(const Document & doc) {m_doc = doc;}
      const Document& parse(const std::string& jsonstr);
      
    private:
      Document m_doc;
      std::shared_ptr<JSON_Parser> parser;
      std::shared_ptr<JSON_Scanner> scanner;
  };
}