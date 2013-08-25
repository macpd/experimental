#include "cow.h"
#include <cstring>
#include <iostream>

Cow::Cow() {
  name[0] = '\0';
  hobby = new char[1];
  hobby[0] = '\0';
  weight = 0;
}

Cow::Cow(const char* nm, const char* ho, double wt) {
  if(nm != NULL) {
    std::strncpy(name, nm, Cow::NAME_MAX -1);
    name[NAME_MAX -1] = '\0';
  } else {
    name[0] = '\0';
  }
  if(ho != NULL) {
    int hobby_len = std::strlen(ho);
    hobby = new char[hobby_len + 1];
    std::strcpy(hobby, ho);
  } else {
    hobby = new char[1];
    hobby[0] = '\0';
  }
  weight = wt;
}

Cow::Cow(const Cow & c) {
  std::cerr << "Cow::Cow(const Cow & c)" << std::endl;
  std::strncpy(name, c.name, Cow::NAME_MAX);
  name[NAME_MAX - 1] = '\0';
  if(c.hobby != NULL) {
    int hobby_len = std::strlen(c.hobby);
    hobby = new char[hobby_len + 1];
    std::strcpy(hobby, c.hobby);
  } else {
    hobby = new char[1];
    hobby[0] = '\0';
  }
  weight = c.weight;
}


Cow::~Cow() {
  delete [] hobby;
}

Cow & Cow::operator=(const Cow & c) {
  std::cerr << "Cow & Cow::operator=(const Cow & c)" << std::endl;
  std::strncpy(name, c.name, Cow::NAME_MAX);
  name[NAME_MAX - 1] = '\0';
  if(c.hobby != NULL) {
    int hobby_len = std::strlen(c.hobby);
    hobby = new char[hobby_len + 1];
    std::strcpy(hobby, c.hobby);
  } else {
    hobby = new char[1];
    hobby[0] = '\0';
  }
  weight = c.weight;
  return *this;
}

void Cow::ShowCow() const {
  std::cout << "Name: " << name << "\n" 
    << "Hobby: " << hobby << "\n" 
    << "Weight: " << weight << std::endl;
}
