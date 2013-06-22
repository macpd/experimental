// prompts for distance in furlongs, outputs distance in yards

#include <iostream>

int const yards_in_furlong = 220;

int furlongs2yards(int furlongs);

int main() {
  using std::cin;
  using std::cout;
  using std::endl;

  int distance_input;
  
  cout << "Distance in furlongs: ";
  cin >> distance_input;
  cout << distance_input << " is " << furlongs2yards(distance_input) << " yards." << endl;
  
  return 0;
}

int furlongs2yards(int const furlongs) {
  return furlongs * yards_in_furlong;
}

