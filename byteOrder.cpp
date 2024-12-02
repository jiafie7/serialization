/************************ MacOS ***************************/

// #include <cstdio>
// #include <iostream>
// #include <machine/endian.h>
//
// int main()
// {
//   if (BYTE_ORDER == LITTLE_ENDIAN)
//     std::cout << "Little endian." << '\n';
//   else if (BYTE_ORDER == BIG_ENDIAN)
//     std::cout << "Big endian." << '\n';
//   else 
//     std::cout << "Unknown." << '\n';
//
//   return 0;
// }


/*********************** CROSS-PLATFORM *********************/
#include <cstdio>
#include <cstring>
#include <iostream>

int main()
{
  int a = 0x12345678;
  char str[4] = { 0 };

  std::memcpy(str, &a, sizeof(int));
  for (int i = 0; i < sizeof(int); i++) 
    printf("%x\n", str[i]); 

  if (str[0] == 0x12)
    std::cout << "Big endian." << '\n';
  else if (str[0] == 0x78)
    std::cout << "Littel endian." << '\n';
  else
    std::cout << "Unknown." << '\n';

  return 0;
}

