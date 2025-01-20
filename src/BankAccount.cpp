#include "../include/BankAccount.hpp"

BankAccount::BankAccount() : balance(0.0), accountNumber(0) {}
BankAccount::BankAccount(int accountNumber, float balance) : accountNumber(accountNumber), balance(balance) {}

void BankAccount::deposit(float amount)
{
    if (amount > 0)
    {
        balance += amount;
    }
}

void BankAccount::withdraw(float amount)
{
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;
    }
}

float BankAccount::getBalance() const
{
    return balance;
}