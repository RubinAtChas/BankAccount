#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

#include <mutex>
#include <iostream>

class BankAccount
{
public:
    BankAccount();
    BankAccount(int accountNumber, float balance);

    void deposit(float amount);
    void withdraw(float amount);
    float getBalance() const;
    int getAccountNumber() const;
    void printBalance(const std::string &clientName) const;
    mutable std::mutex accountMutex;

private:
    float balance;
    int accountNumber;
};

#endif // BANKACCOUNT_HPP