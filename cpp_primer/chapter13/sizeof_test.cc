#include <iostream>

int main() {
  using std::cout;
  using std::endl;

  char arr[20];

  cout << "sizeof arr: " << sizeof arr << "\n"
    << "sizeof arr[0]: " << sizeof arr[0] << "\n"
    << "sizeof arr - sizeof arr[0]: " << sizeof arr - sizeof arr[0] << "\n"
    << "sizeof arr - 1: " << sizeof arr - 1 << endl;
  
  return 0;
}
