#include "cow.h"
#include <iostream>

int main() {
  using std::cout;
  using std::endl;

  std::cerr << "Cow::NAME_MAX " << Cow::NAME_MAX << endl;
  Cow default_cow;
  Cow argued_cow("Chester", "bowling", 2500);
  
  cout << "Default Cow:" << endl;
  default_cow.ShowCow();

  cout << "Argued Cow" << endl;
  argued_cow.ShowCow();

  Cow assinged_cow = argued_cow;

  cout << "Assigned Cow:" << endl;
  assinged_cow.ShowCow();

  assinged_cow = Cow("Newton", "Gravity", 80000);

  cout << "Assigned Cow:" << endl;
  assinged_cow.ShowCow();

  return 0;
}
