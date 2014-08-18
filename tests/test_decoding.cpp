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
    memcpy(bs, &i, sizeof(i));
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
    memcpy(bs, &i, sizeof(i));
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

TEST(Decoding, Document)
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
  ASSERT_EQ(5, e.data<bson::Document>().size());
  std::set<std::string> fields = e.data<bson::Document>().field_names();
  ASSERT_EQ(5, fields.size());
  ASSERT_EQ(1, fields.count("_id"));
  ASSERT_EQ(1, fields.count("s"));
  ASSERT_EQ(1, fields.count("i"));
  ASSERT_EQ(1, fields.count("d"));
  ASSERT_EQ(1, fields.count("l"));
  
  ASSERT_EQ(std::string("\"b\""), std::string(e.data<bson::Document>()["s"]));
  ASSERT_EQ(1234, e.data<bson::Document>()["i"].data<int>());
  ASSERT_EQ(1223412345622, e.data<bson::Document>()["l"].data<long>());
  ASSERT_EQ(3.14000, e.data<bson::Document>()["d"].data<double>());
  ASSERT_EQ(std::string("53d12bc68600b0ad4fbb902c"), static_cast<std::string>(e.data<bson::Document>()["_id"]));
}

TEST(Decoding, BoolTrue)
{
  unsigned char abool[] = {0x1};
  bson::Element e;
  bool res;
  ASSERT_EQ(1, e.decode(abool, bson::BOOL));
  e.data(res);
  ASSERT_TRUE(res);
}

TEST(Decoding, BoolFalse)
{
  unsigned char abool[] = {0x0};
  bson::Element e;
  bool res;
  ASSERT_EQ(1, e.decode(abool, bson::BOOL));
  e.data(res);
  ASSERT_FALSE(res);
}

TEST(Decoding, ArrayEmpty)
{
  unsigned char avec[] = {5, 0, 0, 0, 0};
  bson::Element e;
  bson::array res;
  ASSERT_EQ(5, e.decode(avec, bson::ARRAY));
  e.data(res);
  ASSERT_EQ(0, res.size());
}
TEST(Decoding, ArrayNonEmpty)
{
  unsigned char avec[] = {0x0c, 0, 0, 0,
                          0x10, '0', 0,
			  3, 0, 0, 0,
			  0};
  bson::Element e;
  bson::array res;
  ASSERT_EQ(12, e.decode(avec, bson::ARRAY));
  e.data(res);
  ASSERT_EQ(1, res.size());
  ASSERT_EQ(3, res[0].data<int>());
}

TEST(Decoding, MinKey)
{
  unsigned char minkey[] = {0};
  bson::Element e;
  ASSERT_EQ(0, e.decode(minkey, bson::MINKEY));
}
TEST(Decoding, MaxKey)
{
  unsigned char maxkey[] = {0};
  bson::Element e;
  ASSERT_EQ(0, e.decode(maxkey, bson::MAXKEY));
}
TEST(Decoding, Nil)
{
  unsigned char nil[] = {0};
  bson::Element e;
  ASSERT_EQ(0, e.decode(nil, bson::NIL));
}

TEST(Decoding, RegEx)
{
  unsigned char regex[] = {'a', 'b', 'c', 0, 'd', 'e', 'f', 0};
  bson::Element e;
  ASSERT_EQ(8, e.decode(regex, bson::REGEX));
  ASSERT_EQ(std::string("abc"), e.data<bson::regex>().first);
  ASSERT_EQ(std::string("def"), e.data<bson::regex>().second);
}

TEST(Decoding, DbPtr)
{
  unsigned char dbptr[] = {2, 0, 0, 0, 'a', 0, 1,2,3,4,5,6,7,8,9,10,11,12};
  bson::Element e;
  ASSERT_EQ(18, e.decode(dbptr, bson::DBPTR));
  ASSERT_EQ(std::string("a"), e.data<bson::dbptr>().first);
  for (unsigned char i = 0; i < 12; i++)
  {
    
    ASSERT_EQ(i+1, e.data<bson::dbptr>().second[i]);
  }
}

TEST(Decoding, EmptyJS)
{
  unsigned char jscd[] = {14, 0, 0, 0,
                          1, 0, 0, 0, 0, 
                          5, 0 ,0, 0, 0};
  bson::Element e;
  ASSERT_EQ(14, e.decode(jscd, bson::JS_SCOPE));
}

TEST(Decoding, NonEmptyJS)
{
  unsigned char jscd[] = {22, 0, 0, 0,
                          2, 0, 0, 0, '$', 0, 
                          0x0c, 0, 0, 0,
                          0x10, '0', 0,
			  3, 0, 0, 0,
			  0};
  bson::Element e;
  ASSERT_EQ(22, e.decode(jscd, bson::JS_SCOPE));
  ASSERT_EQ(std::string("$"), e.data<bson::jscode_scope>().first);
  ASSERT_EQ(3, e.data<bson::jscode_scope>().second["0"].data<int>());
}

TEST(Decoding, BinaryEmpty)
{
  unsigned char bin[] = {0,0,0,0,0};
  bson::Element e;
  ASSERT_EQ(5, e.decode(bin, bson::BINARY));
}

TEST(Decoding, BinaryNonEmpty)
{
  unsigned char bin[] = {7,0,0,0,0,0,1,2,3,4,5,6};
  bson::Element e;
  ASSERT_EQ(12, e.decode(bin, bson::BINARY));
  ASSERT_EQ(0x0, e.data<bson::binary>().first);
  ASSERT_EQ(7, e.data<bson::binary>().second.size());
  for (char i = 0; i < 7; i++)
    ASSERT_EQ(i, e.data<bson::binary>().second[i]);
}

TEST(Decoding, UnknownException)
{
  unsigned char blah[] = {0};
  bson::Element e;
  ASSERT_THROW(e.decode(blah, bson::_UNKNOWN), bson::type_UNKNOWN);
}