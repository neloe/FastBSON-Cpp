#include "jsonloader.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
  std::string input;
  bson::JSON_Loader l;
  while (getline(cin, input))
  {
    cout << l.parse(input) << endl;
  }
  return 0;
}