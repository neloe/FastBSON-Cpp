#include <iostream>
#include "element.h"
#include "typeinfo.h"
#include <string>
#include "template_spec/convert_utils.h"

using namespace std;

int main(int argc, char **argv) {
  bson::Element elm(5.4), elm2(string("hello")), elm3, elm4;
  char data[4] = {5,1}; // should be 261 in little endian 0x105
  char floatdata[8];
  cout << elm.data<double>() << endl;
  cout << elm2.data<string>() << endl;
  elm3.from_bytes(data, bson::INT32);
  cout << elm3.data<int>() << endl;
  bson::_to_bytes<double>(floatdata, 42.314);
  elm4.from_bytes(floatdata, bson::FLOATING);
  cout << elm4.data<double>() << endl;
  return 0;
}
