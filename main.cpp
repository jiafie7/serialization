#include "serialize/data_stream.h"
#include "serialize/custom_type.h"

using namespace melon::serialize;

int main()
{
  // basic type
  DataStream ds1;
  ds1 << false << 123 << "hello world";
  bool b;
  int i;
  std::string s;
  ds1 >> b >> i >> s;
  std::cout << "b = " << b << ", i = " << i << ", s = " << s << '\n';

  // composite type
  DataStream ds2;
  std::map<char, int> v1 = {{'a', 7}, {'b', 77}, {'c', 777}};
  ds2 << v1;

  std::map<char, int> v2;
  ds2 >> v2;
  for (auto it = v2.begin(); it != v2.end(); ++ it)
    std::cout << it->first << ' ' << it->second << '\n';

  // custom type
  Fruit f1("Banana", "yellow");
  DataStream ds4;
  ds4 << f1;
  ds4.save("./../fruit.out");
  
  Fruit f2;
  DataStream ds5;
  ds5.load("./../fruit.out");
  ds5 >> f2;
  f2.show();
  
  return 0;
}
