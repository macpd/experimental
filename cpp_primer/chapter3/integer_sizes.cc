// basic program to output integer type sizes of the compiling system

#include <iostream>
#include <climits>

#define CONVERT_BYTES_TO_BITS(n) n * CHAR_BIT

int main() {
  short short_var = SHRT_MAX;
  int int_var= INT_MAX;
  long long_var = LONG_MAX;
  long long llong_var = LLONG_MAX;

  std::cout << "integer type widths for the system this was compiled on." << std::endl;
  std::cout << "1 byte: " << CHAR_BIT << "bits." << std::endl;
  std::cout << "short: " << sizeof(short_var) << " bytes ; " << CONVERT_BYTES_TO_BITS(sizeof(short_var)) << " bits." << std::endl;
  std::cout << "int: " << sizeof(int_var) << " bytes ; " << CONVERT_BYTES_TO_BITS(sizeof(int_var)) << " bits." << std::endl;
  std::cout << "long: " << sizeof(long_var) << " bytes ; " << CONVERT_BYTES_TO_BITS(sizeof(long_var)) << " bits." << std::endl;
  std::cout << "long long: " << sizeof(llong_var) << " bytes ; " << CONVERT_BYTES_TO_BITS(sizeof(llong_var)) << " bits." << std::endl;

  return 0;
}

