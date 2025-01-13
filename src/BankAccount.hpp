#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

#include <mutex>
#include <iostream>

class BankAccount
{
public:
    BankAccount();
    BankAccount(int accountNumber, double balance);

    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;
    int getAccountNumber() const;
    mutable std::mutex accountMutex;

private:
    double balance;
    int accountNumber;
};

#endif // BANKACCOUNT_HPP