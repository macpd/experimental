// golf.cc
#include "golf.h"
#include <iostream>
#include <cstring>


void set_golf(golf & g, const char * name, int hc) {
  strncpy(g.fullname, name, LEN-1);
  g.fullname[LEN] = '\0';
  g.handicap = hc;
}

int set_golf(golf & g) {
  using std::cin;
  using std::cout;

  cout << "Golfer's name: ";
  cin.getline(g.fullname, LEN);
  if(cin.fail()) {
    while(cin.get() != '\n');
    cin.get();
  }
  cout << "Handicap: ";
  while(!(cin >> g.handicap)) {
    cout << "Please enter an integer: ";
    cin.clear();
    while(cin.get() != '\n');
  }
  if(std::strlen(g.fullname) == 0) {
    return 0;
  }
  return 1;
}

void set_handicap(golf & g, int hc) {
  g.handicap = hc;
}

void showGolf(const golf & g) {
  using std::cout;
  using std::endl;

  cout << "Golfer's name: " << g.fullname << endl;
  cout << "Handicap: " << g.handicap << endl;
}
