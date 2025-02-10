#ifndef BANK_HPP
#define BANK_HPP

#include <map>
#include <memory>
#include <mutex>
#include "BankAccount.hpp"

class Bank
{
public:
    Bank();

    void addAccount(int accountNumber, int initialBalance);
    std::shared_ptr<BankAccount> getAccount(int accountNumber) const;
    void displayAllAccounts() const;
    std::map<int, std::shared_ptr<BankAccount>> getAccounts() const;

private:
    mutable std::mutex bankMutex;
    std::map<int, std::shared_ptr<BankAccount>> accounts;
};

#endif
