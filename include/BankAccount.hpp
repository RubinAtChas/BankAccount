#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

#include <mutex>
#include <iostream>

class BankAccount
{
public:
    BankAccount();
    BankAccount(int accountNumber, float balance);

    bool deposit(int amount);
    bool withdraw(int amount);
    float getBalance() const;
    void printBalance(const std::string &clientName) const;
    int getTotalWithdrawals() const;
    int getTotalDeposits() const;

    mutable std::mutex accountMutex;

private:
    float balance;
    int accountNumber;
    int totalWithdrawals;
    int totalDeposits = 0;
};

#endif // BANKACCOUNT_HPP