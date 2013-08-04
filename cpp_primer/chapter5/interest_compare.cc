// calcuates numer of years for 5% compound interest account to exceed value of
// a 10% simple interest account.
#include <iostream>

const float SIMPLE_INTEREST = 0.1;
const float COMPOUND_INTEREST = 0.05;

int main() {
  using std::cout;
  using std::endl;

  double daphne_original_balance = 100.0, cleo_original_balance = 100.0;

  cout << "Daphe has $" << daphne_original_balance << " and Cleo has $"
       << cleo_original_balance << "." << endl;

  double daphne_new_balance = daphne_original_balance, cleo_new_balance = daphne_original_balance;
  
  int years = 1;
  while(daphne_new_balance >= cleo_new_balance)
  {
    daphne_new_balance += daphne_original_balance * SIMPLE_INTEREST;
    cleo_new_balance += cleo_new_balance * COMPOUND_INTEREST;
    years++;
  }

  cout << "Cleo's investment value exceeds Daphne's after " << years - 1 << " years." << endl;
  cout << "Daphe's account balance: $" << daphne_new_balance << endl;
  cout << "Cleo's account balance: $" << cleo_new_balance << endl;
  return 0;
}
