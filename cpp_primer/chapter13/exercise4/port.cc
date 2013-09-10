#include "port.h"
#include <cstring>

Port::Port(const char * br, const char * st, int b) {
  brand = new char[strlen(br) + 1];
  strcpy(brand, br);

  strncpy(style, st, sizeof style - sizeof style[0]); // subtract sizeof 1 element so there is space for the null character
  style[sizeof style - 1] = '\0'; // use '1' becuase this is array elemnt access notation

  bottles = b >= 0 ? b : 0; // set bottles to 0 if argument is negative
}

Port::Port(const Port & p) {
  brand = new char [strlen(p.brand) + 1 ];
  strcpy(brand, p.brand);

  strncpy(style, p.style, sizeof style - sizeof style[0]); // subtract sizeof 1 element so there is space for the null character
  style[sizeof style - 1] = '\0';

  bottles = p.bottles;
}

Port & Port::operator=(const Port & p) {
  if(this == &p) {
    return *this;
  }
  delete [] brand;
  brand = new char[strlen(p.brand) + 1];
  strcpy(brand, p.brand);

  strcpy(style, p.style);

  bottles = p.bottles;
}

/* adds b to bottles.  If sum is negative, bottles is set to 0 */
Port & Port::operator+=(int b) {
  int sum = bottles + b;
  bottles = sum >= 0 ? sum : 0;
}

/* subtracts b from bottles.  If difference is negative, bottles is set to 0 */
Port & Port::operator-=(int b) {
  int diff = bottles - b;
  bottles = diff >= 0 ? diff : 0;
}

void Port::show() const {
  cout << "Brand: " << brand << "\n"
    << "Kind: " << style << "\n"
    << "Bottles: " << bottles << endl;
}

ostream & operator<<(ostream & os, const Port & p) {
  os << p.brand << ',' << p.style << ',' << p.bottles;
  return os;
}
