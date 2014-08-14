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