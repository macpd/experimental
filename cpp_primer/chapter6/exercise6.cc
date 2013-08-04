#include <cstdlib>
#include <iostream>
#include <new>
#include <string>

const double GRAND_PATRON_MIN_CONTRIBUTION = 10000;

struct contributor {
  std::string name;
  double contribution;
};

int main() {
  using std::cin;
  using std::cout;
  using std::endl;
  using std::getline;
  using std::string;

  cout << "Number of contributors: " << endl;
  int num_contributors;
  cin >> num_contributors;
  if(!cin || num_contributors < 0) {
    cout << "Must enter a positive integer." << endl;
    exit(EXIT_FAILURE);
  }
  cin.get();
  contributor *contributor_list = new contributor[num_contributors];
  for(int i = 0; i < num_contributors; i++) {
    cout << "Contributor " << i << " name: ";
    getline(cin, contributor_list[i].name);
    if(!cin) {
      cout << "Type mismatch" << endl;
      exit(EXIT_FAILURE);
    }
    cout << "Contribution amount: ";
    cin >> contributor_list[i].contribution;
    cin.get();
  }
  cout << "Grand Patrons:" << endl;
  bool patron_shown = false;
  for(int i = 0; i < num_contributors; i++) {
    if(contributor_list[i].contribution >= GRAND_PATRON_MIN_CONTRIBUTION) {
      cout << contributor_list[i].name << " contributed $" << contributor_list[i].contribution << endl;
      patron_shown = true;
    }
  }
  if(!patron_shown) {
    cout << "none" << endl;
  }
  cout << "Patrons:" << endl;
  patron_shown = false;
  for(int i = 0; i < num_contributors; i++) {
    if(contributor_list[i].contribution < GRAND_PATRON_MIN_CONTRIBUTION) {
      cout << contributor_list[i].name << " contributed $" << contributor_list[i].contribution << endl;
      patron_shown = true;
    }
  } 
  if(!patron_shown) {
    cout << "none" << endl;
  }

  delete[] contributor_list;
  return 0;
}
