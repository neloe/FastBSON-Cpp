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

TEST (ExceptionText, FromNum)
{
    try
    {
        bson::Element e (4, bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: int and BSON type: string"), std::string (e.what()));
    }
    try
    {
        bson::Element e (4l, bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: long and BSON type: string"), std::string (e.what()));
    }
    try
    {
        bson::Element e (3.14, bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: double and BSON type: string"), std::string (e.what()));
    }
    try
    {
        bson::Element e (static_cast<short> (4), bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: short and BSON type: string"), std::string (e.what()));
    }
}

TEST (ExceptionText, FromBin)
{
    try
    {
        bson::Element e (bson::binary ({}), bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: std::pair<char, std::string> and BSON type: string"), std::string (e.what()));
    }
}

TEST (ExceptionText, FromOID)
{
    try
    {
        bson::Element e (bson::oid ({}), bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: std::array<unsigned char, 12> and BSON type: string"), std::string (e.what()));
    }
}

TEST (ExceptionText, FromBool)
{
    try
    {
        bson::Element e (true, bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: bool and BSON type: string"), std::string (e.what()));
    }
}

TEST (ExceptionText, FromDocument)
{
    try
    {
        bson::Element e (bson::Document ({{}}), bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: bson::Document and BSON type: string"), std::string (e.what()));
    }
}

TEST (ExceptionText, FromJSON)
{
    try
    {
        bson::Element e (bson::jscode_scope ({}), bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: std::pair<std::string, bson::Document> and BSON type: string"), std::string (e.what()));
    }
}

TEST (ExceptionText, FromRegex)
{
    try
    {
        bson::Element e (bson::regex ({}), bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: std::pair<std::string, std::string> and BSON type: string"), std::string (e.what()));
    }
}

TEST (ExceptionText, FromDBPtr)
{
    try
    {
        bson::Element e (bson::dbptr ({}), bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: std::pair<std::string, std::array<unsigned char, 12>> and BSON type: string"), std::string (e.what()));
    }
}

TEST (ExceptionText, FromArr)
{
    try
    {
        bson::Element e (bson::array ({}), bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: std::vector<bson::Element> and BSON type: string"), std::string (e.what()));
    }
}

TEST (ExceptionText, FromVoid)
{
    try
    {
        bson::Element e;
        e.make_void (bson::STRING);
        FAIL();
    }
    catch (bson::type_error &e)
    {
        ASSERT_EQ (std::string ("Invalid conversion between C++ type: void and BSON type: string"), std::string (e.what()));
    }
}