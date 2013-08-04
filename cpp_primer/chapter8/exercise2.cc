#include <iostream>
#include <cstring>

const int NAME_SIZE_MAX = 50;

struct CandyBar {
  char name[NAME_SIZE_MAX];
  double weight;
  int calories;
};

void setCandyBar(CandyBar & cb, const char* name, double, int calories);

void showCandyBar(const CandyBar & cb);

int main () {
  using std::cout;
  using std::endl;
  CandyBar c = {"Charlreston Who?", 1.01, 500};
  cout << "Before modfication:" << endl;
  showCandyBar(c);
  setCandyBar(c, "3 musketrears", 3.5, 300);
  cout << "After modification:" << endl;
  showCandyBar(c);

  return 0;
}

void setCandyBar(CandyBar & cb, const char* name = "Millenium Munch", double weight = 2.85,
    int calories = 350) {
  std::strncpy(cb.name, name, NAME_SIZE_MAX);
  cb.weight = weight;
  cb.calories = calories;
}

void showCandyBar(const CandyBar & cb) {
  using std::cout;
  using std::endl;
  cout << "Name: " << cb.name << endl;
  cout << "Weight: " << cb.weight << endl;
  cout << "Calories: " << cb.calories << endl;
}
