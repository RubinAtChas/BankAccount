#include "../include/Bank.hpp"
#include <iostream>
/**
 * @brief 
 * 
 * @param accountNumber = The number of a bank account
 * @param initialBalance = The accounts intitial balance, which is 1000 in this program.
 */
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
/**
 * @brief A function that displays the bankaccount and its balance.
 * 
 */
void Bank::displayAllAccounts() const
{
    for (const auto &pair : accounts)
    {
        std::cout << "Account Number: " << pair.first
                  << ", Balance: " << pair.second->getBalance() << std::endl;
    }
}
