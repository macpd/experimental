// allocate array of structs at runtime

#include <iostream>
#include <cstring>
#include <string>

const int BUF_SIZE = 2;
const int DROSS_SIZE = 20;
const std::string NUM_NAMES[] = {"One", "Two"};

struct chaff {
  char dross[DROSS_SIZE];
  int slag;
};

int main() {
  using std::cout;
  using std::endl;


  chaff * chaff_arr;
  chaff_arr = new chaff[BUF_SIZE];
  for(int i = 0; i < BUF_SIZE; i++) { 
    cout << "Assigning " << NUM_NAMES[i] << " to chaff.dross member" << endl;
    strncpy(chaff_arr[i].dross, NUM_NAMES[i].c_str(), DROSS_SIZE);
    chaff_arr[i].dross[DROSS_SIZE] = '\0';
    chaff_arr[i].slag = i;
  }
  cout << "Buffer contenets: " << endl;
  for(int i = 0; i < BUF_SIZE; i++) {
    cout << chaff_arr[i].dross << endl;
    cout << chaff_arr[i].slag << endl;
  }
  delete[] chaff_arr;
  return 0;
}
