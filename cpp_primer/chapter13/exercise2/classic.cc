#include "classic.h"
#include <cstring>
#include <iostream>

Classic::Classic(char* work, char *s1, char *s2, int n, double x) : Cd(s1, s2, n, x) {
  primary_work = new char[std::strlen(work) + 1];
  std::strcpy(primary_work, work);
}

Classic::Classic(char * work, Cd & d) : Cd(d) {
  primary_work = new char[std::strlen(work) + 1];
  std::strcpy(primary_work, work);
}

Classic::Classic(Classic & c) : Cd(c) {
  primary_work = new char[std::strlen(c.primary_work) + 1];
  std::strcpy(primary_work, c.primary_work);
}

// Classic::Classic() : Cd() {
Classic::Classic() {
  primary_work = new char[1];
  primary_work[0] = '\0';
}

Classic::~Classic() {
  delete [] primary_work;
}

void Classic::report() const {
  std::cout << "Primary Work: " << primary_work << std::endl;
  Cd::report();
}

Classic & Classic::operator=(const Classic &c) {
  if(this == &c) {
    return *this;
  }
  Cd::operator=(c);

  delete [] primary_work;
  primary_work = new char[std::strlen(c.primary_work) + 1];
  std::strcpy(primary_work, c.primary_work);
  return *this;
}
