#include "../element.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>

TEST(Decoding, Int32)
{
  bson::Element e;
  char bson[4];
  for (int i=0; i<10000; i++)
  {
    mempcpy(bson, &i, sizeof(i));
    e.decode(bson, bson::INT32);
    ASSERT_EQ(i, e.data<int>());
  }
}

TEST(Decoding, Int64)
{
  bson::Element e;
  char bson[8];
  for (long i=0; i<100000; i++)
  {
    mempcpy(bson, &i, sizeof(i));
    e.decode(bson, bson::INT64);
    ASSERT_EQ(i, e.data<long>());
  }
}

TEST(Decoding, String)
{
  bson::Element e;
  const char bson[] = {0x7,0,0,0,'$','q','u','e','r','y', 0};
  for (int i=0; i<10000; i++)
  {
    e.decode(bson, bson::STRING);
    ASSERT_EQ(std::string("$query"), e.data<std::string>());
  }
}