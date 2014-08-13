#include "../element.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>

TEST(ExceptionText, TypeMismatch)
{
  bson::Element e(bson::jscode_scope({}));
  try
  {
    e.data<std::string>();
    FAIL();
  }
  catch (bson::type_error & e)
  {
    ASSERT_EQ(std::string ("Invalid conversion between C++ type: std::string and BSON type: scoped javascript"), std::string(e.what()));
  }
}