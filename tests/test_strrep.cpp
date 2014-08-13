#include "../element.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>

TEST(StringRepresentation, Int32)
{
  bson::Element e(1234);
  const std::string strrep("1234");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, Int64)
{
  bson::Element e(1223412345622);
  const std::string strrep("1223412345622");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, Double)
{
  bson::Element e(3.140000);
  const std::string strrep("3.14");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, String)
{
  bson::Element e(std::string("b"));
  const std::string strrep("\"b\"");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, OID)
{
  const bson::oid input = {'S', 0xd1, 0x2b, 0xc6, 0x86, 0, 0xb0, 0xad, 'O', 0xbb, 0x90, 0x2c};
  bson::Element e(input);
  const std::string strrep("53d12bc68600b0ad4fbb902c");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, EmptyDoc)
{
  bson::Document d;
  bson::Element e(d);
  const std::string strrep("{  }");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, DocSingleI32)
{
  bson::Document d({{"i", 1234}});
  bson::Element e(d);
  const std::string strrep("{ i : 1234 }");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, DocSingleI64)
{
  bson::Document d;
  d.add("l", 1223412345622);
  bson::Element e(d);
  const std::string strrep("{ l : 1223412345622 }");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, DocSingleString)
{
  bson::Document d;
  d.add("s", std::string("b"));
  bson::Element e(d);
  const std::string strrep("{ s : \"b\" }");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, DocEmptyDoc)
{
  bson::Document d, d1;
  d.add("d", d1);
  bson::Element e(d);
  const std::string strrep("{ d : {  } }");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, DocNonEmptyDoc)
{
  bson::Document d, d1;
  d1.add("s", std::string("b"));
  d.add("d", d1);
  bson::Element e(d);
  const std::string strrep("{ d : { s : \"b\" } }");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, EmptyArray)
{
  std::vector<bson::Element> v;
  bson::Element e(v);
  const std::string strrep("[  ]");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, ArrayOneInt32)
{
  std::vector<bson::Element> v;
  v.push_back(bson::Element(4));
  bson::Element e(v);
  const std::string strrep("[ 4 ]");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, ArrayTwoVals)
{
  std::vector<bson::Element> v;
  v.push_back(bson::Element(4));
  v.push_back(bson::Element(std::string("b")));
  bson::Element e(v);
  const std::string strrep("[ 4, \"b\" ]");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, BoolTrue)
{
  bson::Element e(true);
  const std::string strrep("true");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, BoolFalse)
{
  bson::Element e(false);
  const std::string strrep("false");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, Nil)
{
  bson::Element e;
  e.make_void();
  ASSERT_EQ(std::string(""), static_cast<std::string>(e));
}

TEST(StringRepresentation, MinKey)
{
  bson::Element e;
  e.make_void(bson::MINKEY);
  ASSERT_EQ(std::string(""), static_cast<std::string>(e));
}

TEST(StringRepresentation, MaxKey)
{
  bson::Element e;
  e.make_void(bson::MAXKEY);
  ASSERT_EQ(std::string(""), static_cast<std::string>(e));
}
/*
TEST(StringRepresentation, Regex)
{
  unsigned char regex[] = {'a', 'b', 'c', 0, 'd', 'e', 'f', 0};
  bson::Element e(bson::regex({std::string("abc"), std::string("def")}), bson::REGEX);
  std::ostringstream oss;
  e.encode(oss);
  std::string rep (oss.str());
  ASSERT_EQ(8, rep.size());
  for (int i=0; i<8; i++)
    ASSERT_EQ(regex[i], static_cast<unsigned char>(rep[i]));
}

TEST(StringRepresentation, DbPtr)
{
  unsigned char dbptr[] = {2, 0, 0, 0, 'a', 0, 1,2,3,4,5,6,7,8,9,10,11,12};
  bson::Element e(bson::dbptr({"a", {1,2,3,4,5,6,7,8,9,10,11,12}}), bson::DBPTR);
  std::ostringstream oss;
  e.encode(oss);
  std::string rep (oss.str());
  ASSERT_EQ(18, rep.size());
  for (int i=0; i<18; i++)
  {
    ASSERT_EQ(dbptr[i], static_cast<unsigned char>(rep[i]));
  }
}

TEST(StringRepresentation, EmptyJS)
{
  unsigned char jscd[] = {14, 0, 0, 0,
                          1, 0, 0, 0, 0, 
                          5, 0 ,0, 0, 0};
  bson::Document d;
  bson::Element e(bson::jscode_scope({"",d}));
  std::ostringstream oss;
  e.encode(oss);
  std::string rep(oss.str());
  
  ASSERT_EQ(14, rep.size());
  for (int i=0; i<rep.size(); i++)
  {
    ASSERT_EQ(jscd[i], static_cast<unsigned char>(rep[i]));
  }
}

TEST(StringRepresentation, NonEmptyJS)
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

TEST(StringRepresentation, BinaryEmpty)
{
  unsigned char bin[] = {0,0,0,0,0};
  bson::Element e(bson::binary({0,""}));
  std::ostringstream oss;
  e.encode(oss);
  std::string rep(oss.str());
  ASSERT_EQ(5, rep.size());
  for (int i=0; i<rep.size(); i++)
    ASSERT_EQ(bin[i], static_cast<unsigned char>(rep[i]));
}

TEST(StringRepresentation, BinaryNonEmpty)
{
  unsigned char bin[] = {7,0,0,0,0,'q','w','e','r','t','y','u'};
  bson::Element e(bson::binary({0,"qwertyu"}));
  std::ostringstream oss;
  e.encode(oss);
  std::string rep(oss.str());
  ASSERT_EQ(12, rep.size());
  for (int i=0; i<rep.size(); i++)
    ASSERT_EQ(bin[i], static_cast<unsigned char>(rep[i]));
}*/