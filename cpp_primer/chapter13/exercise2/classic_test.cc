#include <iostream>
using namespace std;
#include "classic.h"

void Bravo(const Cd & disk);

int main() {
  Cd c1("Beatles", "Capitol", 14, 35.5);
  Classic c2("Piano Sonata in B flat, Fantasia in C", "Alfred Brendel", "Phillips", 2, 57.17);

  Cd *pcd = &c1;
  cout << "Using objects directly:\n";
  c1.report();
  c2.report();

  cout << endl;

  cout << "Using type cd * pointer to objects:\n";
  pcd->report();
  pcd = &c2;
  pcd->report();

  cout << endl;

  cout << "Calling function with a Cd refrence argument:\n";
  Bravo(c1);
  Bravo(c2);

  cout << endl;

  cout << "Testing assignment:\n";
  Classic* to_delete = new Classic(c2);
  Classic copy;
//  copy = c2;
  copy = *to_delete;
  delete to_delete;
  copy.report();

  return 0;
}

void Bravo(const Cd & disk) {
  disk.report();
}
