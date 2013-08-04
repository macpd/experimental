#include <iostream>

int num_times_printed = 0;

void print_num_times_static(const char * s, int n=0) {
  if(n == 0) {
    std::cout << s << std::endl;
  } else {
    for(int i = 0; i < num_times_printed; i++) {
      std::cout << s << std::endl;
    }
  }
  num_times_printed++;
}

int main() {
  char * c = "Thomas";
  char * d = "Bryan";
  print_num_times_static(c); //prints string once
  print_num_times_static(c, 0); // prints string once again
  print_num_times_static(d, 1); // prints string 2 times
  print_num_times_static(c); //prints string once
  print_num_times_static(d, 2); //prints string 4 times
  
  return 0;
}
