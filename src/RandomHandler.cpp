#include <iostream>
#include <random>
#include <thread>
#include "../include/RandomHandler.hpp"

std::random_device rd;
std::mt19937 gen(rd());

int getRandomNumber(int min, int max)
{
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

int getRandomClient()
{
    return getRandomNumber(1000, 1010);
}

int getRandomAmount()
{
    return getRandomNumber(1000, 10000);
}

int getRandomAccount()
{
    return getRandomNumber(1000, 1005);
}

void clientSimulation(Bank &bank, int clientId)
{
    int accountNumber = getRandomAccount();
    int amount = getRandomAmount();
    std::shared_ptr<BankAccount> account = bank.getAccount(accountNumber);
    if (account == nullptr)
    {
        std::cout << "Account not found" << std::endl;
        return;
    }

    while (true)
    {
        while (true)
        {
            account->deposit(amount);
            std::cout << "Client " << clientId << " deposited " << amount << " to account " << accountNumber << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        }
        while (true)
        {
            account->withdraw(amount);
            std::cout << "Client " << clientId << " withdrew " << amount << " from account " << accountNumber << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(20000));
        }

        std::cout << account->getBalance() << std::endl;
    }
}
