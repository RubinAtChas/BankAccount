#include "../include/Bank.hpp"
#include <iostream>

Bank::Bank()
{
}

void Bank::addAccount(int accountNumber, int initialBalance)
{
    if (accounts.find(accountNumber) == accounts.end())
    {
        accounts[accountNumber] = std::make_shared<BankAccount>(accountNumber, initialBalance);
        std::cout << "Account " << accountNumber << " added with initial balance: " << initialBalance << std::endl;
    }
    else
    {
        std::cout << "Account " << accountNumber << " already exists." << std::endl;
    }
}

std::shared_ptr<BankAccount> Bank::getAccount(int accountNumber) const
{
    auto it = accounts.find(accountNumber);
    if (it != accounts.end())
    {
        return it->second;
    }
    else
    {
        std::cout << "Account " << accountNumber << " not found." << std::endl;
        return nullptr;
    }
}

std::map<int, std::shared_ptr<BankAccount>> Bank::getAccounts() const
{
    return accounts;
}

void Bank::displayAllAccounts() const
{
    int totalDeposits = 0;
    int totalWithdrawals = 0;
    float finalBalance = 0.0;

    for (const auto &pair : getAccounts())
    {
        finalBalance += pair.second->getBalance();
        totalDeposits += pair.second->getTotalDeposits();
        totalWithdrawals += pair.second->getTotalWithdrawals();
    }

    std::cout << "\nFinal account balances:\n";
    for (const auto &pair : getAccounts())
    {
        std::cout << "Account " << pair.first << ": " << pair.second->getBalance() << "\n";
    }

    std::cout << "\nReport:\n";
    std::cout << "Total Deposits: " << totalDeposits << "\n";
    std::cout << "Total Withdrawals: " << totalWithdrawals << "\n";
    std::cout << "Final Balance: " << finalBalance << "\n";
}
