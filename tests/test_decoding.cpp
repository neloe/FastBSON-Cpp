#include "../element.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <set>

TEST(Decoding, Int32)
{
  bson::Element e;
  unsigned char bs[4];
  for (int i=0; i<10000; i++)
  {
    mempcpy(bs, &i, sizeof(i));
    e.decode(bs, bson::INT32);
    ASSERT_EQ(i, e.data<int>());
  }
}

TEST(Decoding, Int64)
{
  bson::Element e;
  unsigned char bs[8];
  for (long i=0; i<100000; i++)
  {
    mempcpy(bs, &i, sizeof(i));
    e.decode(bs, bson::INT64);
    ASSERT_EQ(i, e.data<long>());
  }
}

TEST(Decoding, String)
{
  bson::Element e;
  const unsigned char bs[] = {0x7,0,0,0,'$','q','u','e','r','y', 0};
  e.decode(bs, bson::STRING);
  ASSERT_EQ(std::string("$query"), e.data<std::string>());
}

TEST(Decode, Document)
{
  bson::Element e;
  // This is actual hex pulled from a mongodb query, not just random crap
  // I promise.
  unsigned char bs[] = {0x3c,0x0,0x0,0x0,0x7,0x5f,0x69,0x64,0x0,0x53,
                        0xd1,0x2b,0xc6,0x86,0x0,0xb0,0xad,0x4f,0xbb,
		        0x90,0x2c,0x2,0x73,0x0,0x2,0x0,0x0,0x0,0x62,
		        0x0,0x10,0x69,0x0,0xd2,0x4,0x0,0x0,0x1,0x64,
		        0x0,0x1f,0x85,0xeb,0x51,0xb8,0x1e,0x9,0x40,
		        0x12,0x6c,0x0,0x16,0xeb,0xe,0xd9,0x1c,0x1,0x0,0x0,0x0};
  e.decode(bs, bson::DOCUMENT);
  std::set<std::string> fields = e.data<bson::Document>().field_names();
  ASSERT_EQ(5, fields.size());
  ASSERT_EQ(1, fields.count("_id"));
  ASSERT_EQ(1, fields.count("s"));
  ASSERT_EQ(1, fields.count("i"));
  ASSERT_EQ(1, fields.count("d"));
  ASSERT_EQ(1, fields.count("l"));
  
  ASSERT_EQ(std::string("b"), std::string(e.data<bson::Document>()["s"]));
  ASSERT_EQ(1234, e.data<bson::Document>()["i"].data<int>());
  ASSERT_EQ(1223412345622, e.data<bson::Document>()["l"].data<long>());
  ASSERT_EQ(3.14000, e.data<bson::Document>()["d"].data<double>());
  ASSERT_EQ(std::string("53d12bc68600b0ad4fbb902c"), static_cast<std::string>(e.data<bson::Document>()["_id"]));
}