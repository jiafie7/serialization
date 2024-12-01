#include "serialize/data_stream.h"

using namespace melon::serialize;

int main()
{
  DataStream ds1;
  ds1 << false << 123 << "hello world";

  bool b;
  int i;
  std::string s;
  ds1 >> b >> i >> s;
  std::cout << "b = " << b << ", i = " << i << ", s = " << s << '\n';
  
  return 0;
}
