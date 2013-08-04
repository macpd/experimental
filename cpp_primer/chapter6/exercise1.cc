#include <iostream>
#include <cctype>

int main() {
  using std::cin;
  using std::cout;
  using std::endl;
  char ch;

  cout << "Please enter some text. (input will be echoed, with case toggled and digits excluede.)" << endl;

  while(cin.get(ch) && ch != '@') {
    if(std::isdigit(ch)) {
      continue;
    }
    else if(std::islower(ch)) {
      ch = std::toupper(ch);
    }
    else if(std::isupper(ch)) {
      ch = std::tolower(ch);
    }
    cout << ch;
  }
  cout << endl;
  return 0;
}
