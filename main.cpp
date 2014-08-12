#include <iostream>
#include "element.h"
#include "typeinfo.h"
#include <string>
#include "template_spec/convert_utils.h"
#include "document.h"

using namespace std;

int main(int argc, char **argv) {
  /*
  bson::Element elm(5.4), elm2(string("hello")), elm3, elm4;
  char data[4] = {5,1}; // should be 261 in little endian 0x105
  char floatdata[8];
  cout << elm.data<double>() << endl;
  cout << elm2.data<string>() << endl;
  elm3.decode(data, bson::INT32);
  cout << elm3.data<int>() << endl;
  bson::_to_bytes<double>(floatdata, 42.314);
  elm4.decode(floatdata, bson::FLOATING);
  cout << elm4.data<double>() << endl;
  bson::Document doc;
  doc.add("a double", elm);
  doc.add("a string", std::string("hello world"));
  cout << "indexing: " << doc["a double"].data<double>() << " " << doc["a string"].data<string>() << endl;
  
  bson::Document querydoc, emptydoc;
  querydoc.add("$query", bson::Element(emptydoc));
  
  ostringstream ss;
  bson::Element::encode(ss, querydoc);
  bson::printbson(ss);
  bson::Document q;
  bson::Element e2;
  e2.decode(ss.str().c_str(), bson::DOCUMENT);
  cout << e2.data<bson::Document>()<< endl;
  */
  bson::Document d2({{"a",1}, {"b", "s"}});
  cout << d2 << endl;
  return 0;
}
