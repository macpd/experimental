#include <iostream>

int const MAX_HOUR = 23;
int const MAX_MINUTE = 59;

void print_time(int const hours, int const minutes);

int main() {
  using std::cin;
  using std::cout;
  using std::cerr;
  using std::endl;

  cout << "Enter the number of hours: ";

  int hours_input;
  cin >> hours_input;

  if (hours_input <= 0) {
    cerr << "WTF! " << hours_input << " is negative." << endl;
    return 1;
  } else if (hours_input > MAX_HOUR) {
    cerr << "WTF! " << hours_input << " is too DAMN high." << endl;
    return 2;
  }

  cout << "Enter the number of minutes: ";

  int minutes_input;
  cin >> minutes_input;

  if (minutes_input <= 0) {
    cerr << "WTF! " << minutes_input << " is negative." << endl;
    return 1;
  } else if (minutes_input > MAX_MINUTE) {
    cerr << "WTF! " << minutes_input << " is too DAMN high." << endl;
    return 2;
  }

  print_time(hours_input, minutes_input);

  return 0;
}

void print_time(int const hours, int const minutes) {
  std::cout << "Time: " << hours << ":" ;
  if (minutes < 10) {
    std::cout << "0";
   }
  std::cout << minutes << std::endl;
}
