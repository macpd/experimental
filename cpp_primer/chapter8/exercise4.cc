#include <iostream>
#include <cstring>

struct stringy {
  char * str;
  int ct; 
};

void set(stringy & sy, const char *c);

void show(const stringy & sy, int num_times=1);

void show(const char *c, int num_times=1);

int main() {
  stringy beanie;
  char testing[] = "Reality isn't what it used to be.";
  set(beanie, testing);
  show(beanie);
  show(beanie, 2);
  testing[0] = 'D';
  testing[1] = 'u';
  show(testing);
  show(testing, 3);
  show("Done!");
  return 0;
}

void set(stringy & sy, const char *c) {
  sy.ct = std::strlen(c);
  sy.str = new char[sy.ct];
  std::strncpy(sy.str, c, sy.ct);
}

void show(const stringy & sy, int num_times) {
  for(int i = 0; i < num_times; i++) {
    std::cout << sy.str << std::endl;
  }
}

void show(const char *c, int num_times) {
  for(int i = 0; i < num_times; i++) {
    std::cout << c << std::endl;
  }
}
