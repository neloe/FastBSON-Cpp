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

TEST(StringRepresentation, DocMulti)
{
  bson::Document d({{"i", 1234}});
  d.add("s", std::string("b"));
  bson::Element e(d);
  const std::string strrep1("{ s : \"b\", i : 1234 }");
  const std::string strrep2("{ i : 1234, s : \"b\" }");
  ASSERT_TRUE(strrep1 == static_cast<std::string>(e) || strrep2 == static_cast<std::string>(e));
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

TEST(StringRepresentation, Regex)
{
  unsigned char regex[] = {'a', 'b', 'c', 0, 'd', 'e', 'f', 0};
  bson::Element e(bson::regex({std::string("abc"), std::string("def")}), bson::REGEX);
  const std::string strrep("regex : [ abc, def ]");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, DbPtr)
{
  unsigned char dbptr[] = {2, 0, 0, 0, 'a', 0, 1,2,3,4,5,6,7,8,9,10,11,12};
  bson::Element e(bson::dbptr({"a", {1,2,3,4,5,6,7,8,9,10,11,12}}), bson::DBPTR);
  const std::string strrep("dbptr : [ a, \x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc ]");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, EmptyJS)
{
  unsigned char jscd[] = {14, 0, 0, 0,
                          1, 0, 0, 0, 0, 
                          5, 0 ,0, 0, 0};
  bson::Document d;
  bson::Element e(bson::jscode_scope({"",d}));
  const std::string strrep("js_scope : { code : , mapping : {  } }");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
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
  const std::string strrep("js_scope : { code : $, mapping : { 0 : 3 } }");
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, BinaryEmpty)
{
  unsigned char bin[] = {0,0,0,0,0};
  bson::Element e(bson::binary({0,""}));
  const std::string strrep("binary : { size : 0, type : \x0, bytes :  }", 41);
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, BinaryNonEmpty)
{
  unsigned char bin[] = {7,0,0,0,0,'q','w','e','r','t','y','u'};
  bson::Element e(bson::binary({0,"qwertyu"}));
  std::string strrep("binary : { size : 7, type : \x0, bytes : qwertyu }", 48);
  ASSERT_EQ(strrep, static_cast<std::string>(e));
}

TEST(StringRepresentation, BadType)
{
  bson::Element e;
  ASSERT_THROW(static_cast<std::string>(e), bson::type_UNKNOWN);
}