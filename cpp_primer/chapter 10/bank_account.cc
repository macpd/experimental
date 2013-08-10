#include "bank_account.h"
#include <iostream>

using std::string;

BankAccount::BankAccount() {
  account_holder_name = "";
  account_number = "not assigned";
  balance = 0.0;
}

BankAccount::BankAccount(const string & account_holder_name,
    const string & account_number, double balance) {
  this->account_holder_name = string(account_holder_name);
  this->account_number = string(account_number);
  this->balance = balance;
}

void BankAccount::print() {
  using std::cout;
  using std::endl;
  cout << "Account Holder Name: " << account_holder_name << endl;
  cout << "Account Number: " << account_number;
  cout << "Balance: $" << balance;
}

bool BankAccount::deposit(double amount) {
  if(amount <= 0.0) {
    return false;
  }
  balance += amount;
  return true;
}

bool BankAccount::withdrawl(double amount) {
  if(amount <= 0.0) {
    return false;
  }
  balance -= amount;
  return true;
}
