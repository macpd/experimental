#include "cd.h"
#include <cstring>
#include <iostream>

Cd::Cd(char *s1, char *s2, int n, double x) {
  using std::strncpy;
  strncpy(performers, s1, 49);
  performers[49] = '\0';
  strncpy(label, s2, 19);
  label[19] = '\0';
  selections = n;
  playtime = x;
}

Cd::Cd(const Cd & d) {
  using std::strncpy;
  strncpy(performers, d.performers, 49);
  performers[49] = '\0';
  strncpy(label, d.label, 19);
  label[19] = '\0';
  selections = d.selections;
  playtime = d.playtime;
}

Cd::Cd() {
  performers[0] = label[0] = '\0';
  selections = 0;
  playtime = 0.0;
}

Cd::~Cd() {}

void Cd::report() const {
  using std::cout;
  using std::endl;
  cout << "Performers: " << performers << "\n"
    << "Lable: " << label << "\n"
    << "Selections: " << selections << "\n"
    << "Playtime: " << playtime << endl;
}

Cd & Cd::operator=(const Cd & d) {
  using std::strncpy;

  if (this == &d) {
    return *this;
  }

  strncpy(performers, d.performers, 49);
  performers[49] = '\0';
  strncpy(label, d.label, 19);
  label[19] = '\0';
  selections = d.selections;
  playtime = d.playtime;
  return *this;
}
