#include "cd.h"
#include <cstring>
#include <iostream>

Cd::Cd(char *s1, char *s2, int n, double x) {
  using std::strcpy;
  using std::strlen;
  performers = new char[strlen(s1) + 1];
  strcpy(performers, s1);
  label = new char[strlen(s2) + 1];
  strcpy(label, s2);
  selections = n;
  playtime = x;
}

Cd::Cd(const Cd & d) {
  using std::strcpy;
  using std::strlen;
  performers = new char[strlen(d.performers) + 1];
  strcpy(performers, d.performers);
  label = new char[strlen(d.label) + 1];
  strcpy(label, d.label);
  selections = d.selections;
  playtime = d.playtime;
}

Cd::Cd() {
  performers = new char[1];
  label = new char[1];
  performers[0] = label[0] = '\0';
  selections = 0;
  playtime = 0.0;
}

Cd::~Cd() {
  delete [] performers;
  delete [] label;
}

void Cd::report() const {
  using std::cout;
  using std::endl;
  cout << "Performers: " << performers << "\n"
    << "Lable: " << label << "\n"
    << "Selections: " << selections << "\n"
    << "Playtime: " << playtime << endl;
}

Cd & Cd::operator=(const Cd & d) {
  if (this == &d) {
    return *this;
  }
  using std::strcpy;
  using std::strlen;

  delete [] performers;
  performers = new char[strlen(d.performers) + 1];
  strcpy(performers, d.performers);

  delete [] label;
  label = new char[strlen(d.label) + 1];
  strcpy(label, d.label);
  selections = d.selections;
  playtime = d.playtime;
  return *this;
}
