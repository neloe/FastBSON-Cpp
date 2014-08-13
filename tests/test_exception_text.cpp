#include "../element.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>

TEST(ExceptionText, FromNum)
{
  try
  {
    bson::Element e(4, bson::STRING);
    FAIL();
  }
  catch (bson::type_error & e)
  {
    ASSERT_EQ(std::string ("Invalid conversion between C++ type: int and BSON type: string"), std::string(e.what()));
  }
  try
  {
    bson::Element e(4l, bson::STRING);
    FAIL();
  }
  catch (bson::type_error & e)
  {
    ASSERT_EQ(std::string ("Invalid conversion between C++ type: long and BSON type: string"), std::string(e.what()));
  }
  try
  {
    bson::Element e(3.14, bson::STRING);
    FAIL();
  }
  catch (bson::type_error & e)
  {
    ASSERT_EQ(std::string ("Invalid conversion between C++ type: double and BSON type: string"), std::string(e.what()));
  }
  try
  {
    bson::Element e(static_cast<short>(4), bson::STRING);
    FAIL();
  }
  catch (bson::type_error & e)
  {
    ASSERT_EQ(std::string ("Invalid conversion between C++ type: short and BSON type: string"), std::string(e.what()));
  }
}

TEST(ExceptionText, FromBin)
{
  try
  {
    bson::Element e(bson::binary({}), bson::STRING);
    FAIL();
  }
  catch (bson::type_error & e)
  {
    ASSERT_EQ(std::string ("Invalid conversion between C++ type: std::pair<char, std::string> and BSON type: string"), std::string(e.what()));
  }
}