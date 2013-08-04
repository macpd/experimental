#include <iostream>

const int SIZE = 10;

/* assignes n to all elements of array a, starting at start and upto (but not
 * including) end*/
void assignArrayRange(int* a, int* end, int val);

int main() {
  using std::cout;
  using std::endl;
  
  int array[SIZE];

  cout << "assigning 4 to elements 0-4" << endl;
  assignArrayRange(array, &array[5], 4);

  cout << "assigning 10 to elements 5-9" << endl;
  assignArrayRange(&array[5], &array[SIZE], 10);

  cout << "final array values:" << endl;
  for(int i = 0; i < SIZE; i++) {
    cout << "array[" << i << "]: " << array[i] << endl;
  }
  return 0;
}

void assignArrayRange(int* a, int* end, int val) {
  for(int i = 0; a+i != end; i++) {
    std::cerr << "a+" << i << std::endl;
    *(a+i) = val;
  }
  return;
}
