#include "../include/BankAccount.hpp"
#include <thread>
#include <chrono>

BankAccount::BankAccount() : balance(0.0), accountNumber(0) {}
BankAccount::BankAccount(int accountNumber, float balance) : accountNumber(accountNumber), balance(balance) {}

void BankAccount::deposit(float amount)
{        
    std::lock_guard<std::mutex> lock(accountMutex); //Mutex that protects the balance
    if (amount > 0)
    {
        balance += amount;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //sleep after the changes in balance, after if statment to avoid race conditions if another methods dont have lock_guard 
}

void BankAccount::withdraw(float amount)
{
    std::lock_guard<std::mutex> lock(accountMutex); //Mutex that protects the balance
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //sleep after the changes in balance as the first one :)
}

float BankAccount::getBalance() const
{
    std::lock_guard<std::mutex> lock(accountMutex); //Mutex that protects the balance

    return balance;
}

