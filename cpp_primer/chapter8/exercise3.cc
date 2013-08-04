#include <iostream>
#include <cctype>
#include <string>

const char QUIT_CHAR = 'q';

void capsLock(std::string & s);

int main() {
  using std::cin;
  using std::cout;
  using std::endl;
  using std::getline;

  cout << "Enter a string (" << QUIT_CHAR << " to quit): ";
  std::string input;
  getline(cin, input);
  while(cin.good() && input.size() != 1 && input[0] != QUIT_CHAR) {
    capsLock(input);
    cout << input << endl;
    cout << "Next string (q to quit): ";
    getline(cin, input);
  }
  cout << "Bye" << endl;

  return 0;
}

void capsLock(std::string & s) {
  for(int i = 0; i < s.size(); i++) {
    s[i] = std::toupper(s[i]);
  }
}
