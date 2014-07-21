#include <iostream>
#include "element.h"
#include <string>

using namespace std;

int main(int argc, char **argv) {
  bson::Element elm(5.4), elm2(string("hello"));
  cout << elm.data<double>() << endl;
  cout << elm2.data<string>() << endl;
  return 0;
}
