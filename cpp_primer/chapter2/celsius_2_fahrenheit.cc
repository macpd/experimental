#include <iostream>

double celsius2fahrenheit(double c);

int main() {
  using std::cin;
  using std::cout;
  using std::endl;

  cout << "Please enter a Celsius value: ";
  double celsius_input;
  cin >> celsius_input;
  cout << celsius_input << " degrees celsius is ";
  cout << celsius2fahrenheit(celsius_input) << " degrees Fahrenheit." << endl;

  return 0;
}

double celsius2fahrenheit(double const c) {
  return (1.8 * c) + 32;
}
