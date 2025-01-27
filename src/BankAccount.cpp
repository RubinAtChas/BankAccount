#include "../include/BankAccount.hpp"
#include <thread>
#include <chrono>

BankAccount::BankAccount() : balance(0.0), accountNumber(0) {}
BankAccount::BankAccount(int accountNumber, float balance) : accountNumber(accountNumber), balance(balance) {}

bool BankAccount::deposit(int amount)
{
    totalDeposits += amount;

    std::lock_guard<std::mutex> lock(accountMutex); // Mutex that protects the balance
    if (amount > 0)
    {
        balance += amount;
        return true;
    }
    return false;
}

bool BankAccount::withdraw(int amount)
{
    std::lock_guard<std::mutex> lock(accountMutex); // Mutex that protects the balance
    if (balance >= amount)
    {
        balance -= amount;
        return true;
    }
    return false;
}

float BankAccount::getBalance() const
{
    std::lock_guard<std::mutex> lock(accountMutex); // Mutex that protects the balance

    return balance;
}
void BankAccount::printBalance(const std::string &clientName) const
{
    std::lock_guard<std::mutex> lock(accountMutex); // Mutex that protects the balance
    std::cout << "Client: " << clientName << ", Balance: " << balance << std::endl;
}

int BankAccount::getTotalWithdrawals() const
{
    return totalWithdrawals;
}

int BankAccount::getTotalDeposits() const
{
    return totalDeposits;
}