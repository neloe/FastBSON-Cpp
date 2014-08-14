#include "../element.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>

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

TEST(Encoding, Short)
{
  bson::Element e(static_cast<short>(1234));
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

TEST(Encoding, OID)
{
  const bson::oid input = {'S', 0xd1, 0x2b, 0xc6, 0x86, 0, 0xb0, 0xad, 'O', 0xbb, 0x90, 0x2c};
  bson::Element e(input);
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  for (int i=0; i < input.size(); i++)
    ASSERT_EQ(input[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, EmptyDoc)
{
  bson::Document d;
  bson::Element e(d);
  const unsigned char BSON_REP[] = {5, 0, 0, 0, 0};
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(BSON_REP[0], strrep.size());
  for (int i=0; i<strrep.size(); i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, DocSingleI32)
{
  bson::Document d;
  d.add("i", 1234);
  ASSERT_EQ(bson::INT32, d["i"].get_type());
  const unsigned char BSON_REP[] = {0x0c, 0, 0, 0, 0x10, 'i', 0, 0xd2, 4, 0, 0, 0};
  bson::Element e(d);
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(BSON_REP[0], strrep.size());
  for (int i=0; i<strrep.size(); i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, DocSingleI64)
{
  bson::Document d;
  d.add("l", 1223412345622);
  ASSERT_EQ(bson::INT64, d["l"].get_type());
  const unsigned char BSON_REP[] = {0x10, 0, 0, 0, 0x12, 'l', 0, 0x16, 0xeb, 0x0e, 0xd9, 0x1c, 1, 0, 0, 0};
  bson::Element e(d);
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(BSON_REP[0], strrep.size());
  for (int i=0; i<strrep.size(); i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, DocSingleString)
{
  bson::Document d;
  d.add("s", std::string("b"));
  ASSERT_EQ(bson::STRING, d["s"].get_type());
  const unsigned char BSON_REP[] = {0x0E, 0, 0, 0, 0x2, 's', 0, 2, 0, 0, 0, 'b', 0, 0};
  bson::Element e(d);
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(BSON_REP[0], strrep.size());
  for (int i=0; i< strrep.size(); i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, DocEmptyDoc)
{
  bson::Document d, d1;
  d.add("d", d1);
  ASSERT_EQ(bson::DOCUMENT, d["d"].get_type());
  const unsigned char BSON_REP[] = {0x0d, 0, 0, 0, 0x03, 'd', 0, 5, 0, 0, 0, 0, 0};
  bson::Element e(d);
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(BSON_REP[0], strrep.size());
  for (int i=0; i< strrep.size(); i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, DocNonEmptyDoc)
{
  bson::Document d, d1;
  d1.add("s", std::string("b"));
  d.add("d", d1);
  ASSERT_EQ(bson::DOCUMENT, d["d"].get_type());
  const unsigned char BSON_REP[] = {0x16, 0, 0, 0, 0x03, 'd', 0, 0x0E, 0, 0, 0, 0x2, 's', 0, 2, 0, 0, 0, 'b', 0, 0, 0};
  bson::Element e(d);
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(BSON_REP[0], strrep.size());
  for (int i=0; i< strrep.size(); i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, EmptyArray)
{
  std::vector<bson::Element> v;
  bson::Element e(v);
  ASSERT_EQ(bson::ARRAY, e.get_type());
  const unsigned char BSON_REP[] = {5, 0, 0, 0, 0};
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(BSON_REP[0], strrep.size());
  for (int i=0; i< strrep.size(); i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, ArrayOneInt32)
{
  std::vector<bson::Element> v;
  v.push_back(bson::Element(4));
  bson::Element e(v);
  ASSERT_EQ(bson::ARRAY, e.get_type());
  const unsigned char BSON_REP[] = {0x0c, 0, 0, 0, 0x10, '0', 0, 4, 0, 0, 0, 0};
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(BSON_REP[0], strrep.size());
  for (int i=0; i< strrep.size(); i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, ArrayTwoVals)
{
  std::vector<bson::Element> v;
  v.push_back(bson::Element(4));
  v.push_back(bson::Element(std::string("b")));
  bson::Element e(v);
  ASSERT_EQ(bson::ARRAY, e.get_type());
  const unsigned char BSON_REP[] = {0x15, 0, 0, 0, 0x10, '0', 0, 4, 0, 0, 0, 0x02, '1', 0, 2, 0, 0, 0, 'b', 0, 0};
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(BSON_REP[0], strrep.size());
  for (int i=0; i< strrep.size(); i++)
    ASSERT_EQ(BSON_REP[i], static_cast<unsigned char>(strrep.c_str()[i]));
}

TEST(Encoding, BoolTrue)
{
  bson::Element e(true);
  ASSERT_EQ(bson::BOOL, e.get_type());
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(1, strrep.size());
  ASSERT_EQ(1, strrep.c_str()[0]);
}

TEST(Encoding, BoolFalse)
{
  bson::Element e(false);
  ASSERT_EQ(bson::BOOL, e.get_type());
  std::ostringstream oss;
  std::string strrep;
  e.encode(oss);
  strrep = oss.str();
  ASSERT_EQ(1, strrep.size());
  ASSERT_EQ(0, strrep.c_str()[0]);
}

TEST(Encoding, Nil)
{
  bson::Element e;
  std::ostringstream oss;
  e.make_void();
  ASSERT_EQ(bson::NIL, e.get_type());
  e.encode(oss);
  ASSERT_EQ(0,oss.str().size());
}

TEST(Encoding, MinKey)
{
  bson::Element e;
  std::ostringstream oss;
  e.make_void(bson::MINKEY);
  ASSERT_EQ(bson::MINKEY, e.get_type());
  e.encode(oss);
  ASSERT_EQ(0,oss.str().size());
}

TEST(Encoding, MaxKey)
{
  bson::Element e;
  std::ostringstream oss;
  e.make_void(bson::MAXKEY);
  ASSERT_EQ(bson::MAXKEY, e.get_type());
  e.encode(oss);
  ASSERT_EQ(0,oss.str().size());
}

TEST(Encoding, Regex)
{
  unsigned char regex[] = {'a', 'b', 'c', 0, 'd', 'e', 'f', 0};
  bson::Element e(bson::regex({std::string("abc"), std::string("def")}));
  std::ostringstream oss;
  e.encode(oss);
  std::string rep (oss.str());
  ASSERT_EQ(8, rep.size());
  for (int i=0; i<8; i++)
    ASSERT_EQ(regex[i], static_cast<unsigned char>(rep[i]));
}

TEST(Encoding, DbPtr)
{
  unsigned char dbptr[] = {2, 0, 0, 0, 'a', 0, 1,2,3,4,5,6,7,8,9,10,11,12};
  bson::Element e(bson::dbptr({"a", {1,2,3,4,5,6,7,8,9,10,11,12}}));
  std::ostringstream oss;
  e.encode(oss);
  std::string rep (oss.str());
  ASSERT_EQ(18, rep.size());
  for (int i=0; i<18; i++)
  {
    ASSERT_EQ(dbptr[i], static_cast<unsigned char>(rep[i]));
  }
}

TEST(Encoding, EmptyJS)
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

TEST(Encoding, NonEmptyJS)
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

TEST(Encoding, BinaryEmpty)
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

TEST(Encoding, BinaryNonEmpty)
{
  unsigned char bin[] = {7,0,0,0,0,'q','w','e','r','t','y','u'};
  bson::Element e(bson::binary({0,"qwertyu"}));
  std::ostringstream oss;
  e.encode(oss);
  std::string rep(oss.str());
  ASSERT_EQ(12, rep.size());
  for (int i=0; i<rep.size(); i++)
    ASSERT_EQ(bin[i], static_cast<unsigned char>(rep[i]));
}