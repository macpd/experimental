#include <iostream>

const int SIZE = 50;

int replace(char * str, char c1, char c2);

int main() {
  using std::cin;
  using std::cout;
  using std::endl;

  cout << "enter a string (max 50 characters): ";
  char str[SIZE];
  cin.getline(str, SIZE);
  char new_char, old_char;
  cout << "Enter a character and it's replacement: ";
  cin >> old_char >> new_char;
  int replacements = replace(str, old_char, new_char);
  cout << "Here you go:" << endl;
  cout << str << endl;
  cout << "Replaced " << replacements << " characters" << endl;

  return 0;
}

int replace(char * str, char c1, char c2) {
  int num_replacements;
  for(int i = 0; str[i] != '\0' && i < SIZE; i++) {
    if(str[i] == c1) {
      str[i] = c2;
      num_replacements++;
    }
  }
  return num_replacements;
}
