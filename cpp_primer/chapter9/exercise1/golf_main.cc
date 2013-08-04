// simple program to demonstrate golf.cc functionality

#include "golf.h"
#include <iostream>

int main() {
  using std::cout;
  using std::endl;

  golf geoff;
  set_golf(geoff);

  showGolf(geoff);

  cout << "Setting his handicap to 3" << endl;
  set_handicap(geoff, 3);
  showGolf(geoff);

  golf other;
  set_golf(other, "Tiger woods", 1);
  cout << "Golfer created for S & G: " << endl;
  showGolf(other);

  return 0;
}
