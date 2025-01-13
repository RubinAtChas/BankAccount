#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <mutex>
#include <iostream>

class BankAccount
{
private:
    int accountNumber;
    int balance;
    mutable std::mutex accountMutex;

public:
    BankAccount(int accountNumber, int initialBalance);

    void deposit(int amount);

    bool withdraw(int amount);

    int getBalance() const;

    int getAccountNumber() const;
};

#endif
