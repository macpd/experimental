#include "vintage_port.h"
#include <cstring>

VintagePort::VintagePort() {
  nickname = new char[1];
  nickname[0] = '\0';
  year = 0;
}

VintagePort::VintagePort(const char * br, int b, const char * nn, int y) : Port(br, "Vintage", b) {
  nickname = new char[std::strlen(nn) + 1];
  std::strcpy(nickname, nn);
  year = y;
}

VintagePort::VintagePort(const VintagePort & vp) : Port(vp) {
  nickname = new char[std::strlen(vp.nickname) + 1];
  std::strcpy(nickname, vp.nickname);
  year = vp.year;
}

VintagePort & VintagePort::operator=(VintagePort & vp) {
  if(this == &vp) {
    return *this;
  }
  
  Port::operator=(vp);

  delete [] nickname;
  nickname = new char[std::strlen(vp.nickname) + 1];
  std::strcpy(nickname, vp.nickname);

  year = vp.year;
}

void VintagePort::show() const {
  cout << "Nickname: " << nickname << "\n";
  Port::show();
}

ostream & operator<<(ostream & os, const VintagePort & vp) {
  os << vp.nickname << ',' << operator<<(os, vp);
  return os;
}
