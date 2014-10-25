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
#include "../element.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <set>

TEST(Element, CreateFromCStr)
{
  bson::Element e("hello world");
  ASSERT_EQ(bson::STRING, e.get_type());
  ASSERT_EQ(std::string("hello world"), e.data<std::string>());
}

TEST(Element, CreateFromCStrBumType)
{
  ASSERT_THROW(bson::Element e("hello world", bson::INT32), bson::type_error);
}

TEST(Element, CreateFromCStrBumTypeText)
{
  try
  {
    bson::Element e("hello world", bson::INT32);
    FAIL();
  }
  catch (bson::type_error & e)
  {
    ASSERT_STREQ("Invalid conversion between C++ type: std::string and BSON type: int32", e.what());
  }
}

TEST(Element, UnknownException)
{
  bson::Element e;
  std::ostringstream ss;
  ASSERT_THROW(e.encode(ss), bson::type_UNKNOWN);
}

TEST(Element, UnknownExceptionText)
{
  bson::Element e;
  std::ostringstream ss;
  try
  {
    e.encode(ss);
  }
  catch (bson::type_UNKNOWN & e)
  {
    ASSERT_STREQ("_UNKNOWN type not implemented", e.what());
  }
}