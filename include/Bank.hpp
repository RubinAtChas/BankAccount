#ifndef BANK_HPP
#define BANK_HPP

#include <map>
#include <memory>
#include "BankAccount.hpp"
/**
 * @brief A class for bank accounts and their initial balance
 * 
 */
class Bank
{
private:
    std::map<int, std::shared_ptr<BankAccount>> accounts;

public:
    void addAccount(int accountNumber, int initialBalance);

    std::shared_ptr<BankAccount> getAccount(int accountNumber) const;

    void displayAllAccounts() const;
};

#endif
