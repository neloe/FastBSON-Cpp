#include "../element.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <iostream>

TEST(Encoding, Int32)
{
  bson::Element e(1234);
  const unsigned char BSON_REP[] = {0xd2, 4, 0, 0};
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  for (int i=0; i<4; i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, Int64)
{
  bson::Element e(1223412345622);
  const unsigned char BSON_REP[] = {0x16, 0xeb, 0xe, 0xd9, 0x1c, 1, 0, 0};
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  for (int i=0; i<8; i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, Double)
{
  bson::Element e(3.140000);
  const unsigned char BSON_REP[] = {0x1f, 0x85, 0xeb, 'Q', 0xb8, 0x1e, 9, 0x40};
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  for (int i=0; i<8; i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, String)
{
  bson::Element e(std::string("b"));
  const unsigned char BSON_REP[] = {2, 0, 0, 0, 'b', 0};
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  for (int i=0; i<6; i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}