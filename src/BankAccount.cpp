#include "../include/BankAccount.hpp"
#include <thread>
#include <chrono>

BankAccount::BankAccount() : balance(0.0), accountNumber(0) {}
BankAccount::BankAccount(int accountNumber, float balance) : accountNumber(accountNumber), balance(balance) {}

void BankAccount::deposit(float amount)
{        
    std::lock_guard<std::mutex> lock(accountMutex);
    if (amount > 0)
    {
        balance += amount;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //test 
}

void BankAccount::withdraw(float amount)
{
    std::lock_guard<std::mutex> lock(accountMutex);
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //test
}

float BankAccount::getBalance() const
{
    std::lock_guard<std::mutex> lock(accountMutex);

    return balance;
}

