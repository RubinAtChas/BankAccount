#include "../include/BankAccount.hpp"
#include <thread>
#include <chrono>

BankAccount::BankAccount() : balance(0.0), accountNumber(0) {}
BankAccount::BankAccount(int accountNumber, float balance) : accountNumber(accountNumber), balance(balance) {}
/**
 * @brief A function that changes the variable balance with to a new variable value depending on the amount that was deposited.
 * 
 * @param amount The new amount after "Money" has been deposited. SShould be more than the previous amount.
 */
void BankAccount::deposit(float amount)
{
    std::lock_guard<std::mutex> lock(accountMutex); // Mutex that protects the balance
    if (amount > 0)
    {
        balance += amount;
    }
}
/**
 * @brief A function that changes balance from its previous value to a new value depending on the amount that was withdrawn.
 * 
 * @param amount The new amount value after "Money" has been withdrawn. Should be less than the previous amount. 
 */
void BankAccount::withdraw(float amount)
{
    std::lock_guard<std::mutex> lock(accountMutex); // Mutex that protects the balance
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;
    }
}
/**
 * @brief Function that gets balance of a bankaccount. This function only gets the balance value.
 * 
 * @return float variable that is returned 
 */
float BankAccount::getBalance() const
{
    std::lock_guard<std::mutex> lock(accountMutex); // Mutex that protects the balance

    return balance;
}
/**
 * @brief This function displays the clients name and the balance of the account that the client has accesed(Randomly).
 * 
 * @param clientName A string that gets the clients name. A parameter string value for a function.
 */
void BankAccount::printBalance(const std::string &clientName) const
{
    std::lock_guard<std::mutex> lock(accountMutex); // Mutex that protects the balance
    std::cout << "Client: " << clientName << ", Balance: " << balance << std::endl;
}