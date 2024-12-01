#include "serialize/data_stream.h"
#include "serialize/custom_type.h"

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

  DataStream ds2;
  std::set<char> vi = {'a', 'b', 'c'};
  ds2 << vi;

  std::set<char> v2;
  ds2 >> v2;
  for (auto it = v2.begin(); it != v2.end(); ++ it)
    std::cout << *it << '\n';

  A a1("Michael", 27);
  DataStream ds3;
  ds3 << a1;

  A a2;
  ds3 >> a2;
  a2.show();
  
  return 0;
}
