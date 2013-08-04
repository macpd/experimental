#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <new>
#include <string>

const double GRAND_PATRON_MIN_CONTRIBUTION = 10000;
const char* DEFAULT_FILENAME = "contributors.txt";
const int MAX_FILENAME_SIZE = 255;

struct contributor {
  std::string name;
  double contribution;
};

int main() {
  using std::cin;
  using std::cout;
  using std::cerr;
  using std::endl;
  using std::getline;
  using std::string;

  char filename[MAX_FILENAME_SIZE];
  std::strncpy(filename, DEFAULT_FILENAME, MAX_FILENAME_SIZE);

  std::fstream infile;
  infile.open(filename);
  if(!infile.is_open()) {
    cerr << "Unable to open " << filename << endl;
    exit(EXIT_FAILURE);
  }

  int num_contributors;
  infile >> num_contributors;
  if(!infile || num_contributors < 0) {
    cerr << "File incorrectly formatted" << endl;
    exit(EXIT_FAILURE);
  }
  infile.get();
  contributor *contributor_list = new contributor[num_contributors];
  for(int i = 0; i < num_contributors; i++) {
    getline(infile, contributor_list[i].name);
    if(!infile) {
      cerr << "Type mismatch" << endl;
      exit(EXIT_FAILURE);
    }
    infile >> contributor_list[i].contribution;
    infile.get();
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
