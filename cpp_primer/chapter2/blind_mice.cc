#include <iostream>

void print_3_blind_mice() {
  std::cout << "Three blind mice" << std::endl;
}

void print_see_how_they_run() {
  std::cout << "See how they run" << std::endl;
}

int main() {
  print_3_blind_mice();
  print_3_blind_mice();
  print_see_how_they_run();
  print_see_how_they_run();
  return 0;
}
