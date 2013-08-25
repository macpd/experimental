// demo functionality of BankAccount

#include <iostream>
#include "bank_account.h"

int main() {
  using std::cout;
  using std::endl;
  BankAccount ba1;
  BankAccount ba2("Chester", "cheeses12", 100.1);

  cout << "Default constructed BankAccount:" << endl;
  ba1.print();

  cout << "Value intialized BankAccount:" << endl;
  ba2.print();

  cout << "depositing $60:" << endl;
  cout << "Total before: " << ba1.get_balance() << endl;
  ba1.deposit(60.0);
  cout << "Total after: " << ba1.get_balance() << endl;

  cout << "Withdrawing $32:" << endl;
  cout << "Total before: " << ba1.get_balance() << endl;
  ba1.withdrawl(32.0);
  cout << "Total after: " << ba1.get_balance() << endl;
}
