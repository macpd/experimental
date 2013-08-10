// basic implementation of a bank account

#ifndef BANKACCOUNT_H_
#define BANKACCOUNT_H_

#include <string>

using std::string;
class BankAccount {
  private:
    string account_holder_name;
    string account_number;
    double balance;
  public:
    BankAccount();
    BankAccount(const string & account_holder_name,
        const string & account_number, double balance);
    void print();
    bool deposit(double amount);
    bool withdrawl(double amount);
    const double get_balance() { return this->balance; }
    const string & get_account_holder_name() {
      return this->account_holder_name; }
    const string & get_account_number() { return this->account_number; };
};

#endif
