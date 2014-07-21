#include <iostream>
#include "element.h"

using namespace std;

int main(int argc, char **argv) {
  bson::Element elm(5.4);
  cout << elm.data<double>() << endl;
  return 0;
}
