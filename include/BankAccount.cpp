#include "BankAccount\src\BankAccount.hpp"

BankAccount::BankAccount() : balance(0.0), accountNumber(0) {}
BankAccount::BankAccount(int accountNumber, double balance) : accountNumber(accountNumber), balance(balance) {}

void BankAccount::deposit(double amount)
{
    if (amount > 0)
    {
        balance += amount;
    }
}

void BankAccount::withdraw(double amount)
{
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;
    }
}

double BankAccount::getBalance() const
{
    return balance;
}