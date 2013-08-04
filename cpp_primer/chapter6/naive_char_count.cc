#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

const char* DEFAULT_FILE = "default.txt";

int main() {
  using std::cout;
  using std::cerr;
  using std::endl;
  std::ifstream infile;
  char filename[50];
  std::strncpy(filename, DEFAULT_FILE, 50);
  infile.open(filename);
  if(!infile.is_open()) {
    cerr << "Catastrophic failure" << endl;
    exit(EXIT_FAILURE);
  }
  char ch;
  long long num_characters;
  while(infile.get(ch) && infile.good()) {
    num_characters++;
  }
  if(infile.fail() && !infile.eof()) {
    cerr << "Some failure." << endl;
  }
  cout << filename << " has " << num_characters << " characters." << endl;
  infile.close();
  return 0;
}
