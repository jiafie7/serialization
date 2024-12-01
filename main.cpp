#include "serialize/data_stream.h"

using namespace melon::serialize;

int main()
{
  DataStream ds1;
  ds1 << true << 123 << "hello world";

  ds1.show();
  
  return 0;
}
