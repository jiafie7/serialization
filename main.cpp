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

  Student s1("Michael", 23);
  DataStream ds3;
  ds3 << s1;

  Student s2;
  ds3 >> s2;
  s2.show();

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
