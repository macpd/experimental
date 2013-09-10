#include "vintage_port.h"
#include <iostream>

int main() {
  Port port1;
  Port port2("Portal", "Ruby", 1);
  Port port3("Sandeman", "Tawny", 2);

  std::cout << "Ports:" << "\n"
    << port1 << '\n';
  port2.show();
  std::cout << ',';
  port3.show();
  std::cout << std::endl;

  VintagePort vp1;
  VintagePort vp2("Portal", 1, "Ye Olde Glory", 1785);

  std::cout << "Vintage Ports:" << "\n"
    << vp1 << '\n';
  vp2.show();
  std::cout << std::endl;

  std::cout << "Using a Port * pointer to test virtual methods." << '\n';

  Port * port_pointer;
  port_pointer = &port1;
  std::cout << "port1: ";
  port_pointer->show();
  std::cout << '\n';

  port_pointer = &vp2;
  std::cout << "vp2: ";
  port_pointer->show();
  std::cout << '\n';

  std::cout << "Testing assignment" << '\n';
  port3 = port1;
  std::cout << port3 << '\n';
  vp1 = vp2;
  std::cout << vp1 << endl;

  return 0;
}
