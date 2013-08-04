#include <iostream>
#include <cstdlib>

const int SIZE = 10;

int main() {
  using std::cin;
  using std::cout;
  using std::endl;

  cout << "Enter " << SIZE << " donation values." << endl;

  double values[SIZE];
  double temp, sum;

  for(int i = 0; i < SIZE; i++) {
    cin >> temp;
    if(!cin) {
      cout << "Bad input" << endl;
      exit(EXIT_FAILURE);
    }
    values[i] = temp;
    sum += temp;
  }
  double average = sum/SIZE;
  cout << "Average: " << average << endl;
  int values_greater_than_average = 0;
  for(int i = 0; i < SIZE; i++) {
    if(values[i] > average) {
      values_greater_than_average++;
    }
  }
  cout << "Values greater than average: " << values_greater_than_average << endl;
  return 0;
}
