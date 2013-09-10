#ifndef PORT_H
#define PORT_H

#include <iostream>

using namespace std;

class Port {
  private:
    char * brand;
    char style[20]; // i.e. tawny, ruby, vintage
    int bottles;
  public:
    Port(const char * br = "none", const char * st = "none", int b = 0);
    Port(const Port & p);
    virtual ~Port() { delete[] brand; }
    Port & operator=(const Port & p);
    Port & operator+=(int b); // adds b to bottles
    Port & operator-=(int b); // subtracts b from bottles
    int bottleCount() const { return bottles; }
    virtual void show() const;
    friend ostream & operator<<(ostream & os, const Port & p);
};
#endif
