#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <mutex>
#include <iostream>

class BankAccount {
private:
    int accountNumber;
    int balance;
    mutable std::mutex accountMutex; // mutable to allow const member functions to lock

public:
    // Constructor
    BankAccount(int accountNumber, int initialBalance);

    // Deposit method
    void deposit(int amount);

    // Withdraw method
    bool withdraw(int amount);

    // Get balance method
    int getBalance() const;

    // Get account number method
    int getAccountNumber() const;
};

#endif // BANK_ACCOUNT_HPP
