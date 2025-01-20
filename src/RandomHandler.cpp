#include <iostream>
#include <random>
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
    int accountNumber = getRandomClient();
    int amount = getRandomAmount();
    int account = getRandomAccount();

    std::shared_ptr<BankAccount> clientAccount = bank.getAccount(accountNumber);

    if (clientAccount)
    {
        std::lock_guard<std::mutex> lock(clientAccount->accountMutex);

        if (account >= 1)
        {
            clientAccount->deposit(amount);
            std::cout << "Client " << clientId << " deposited $" << amount << " into account " << accountNumber << std::endl;
        }
        else
        {
            clientAccount->withdraw(amount);
            std::cout << "Client " << clientId << " withdrew $" << amount << " from account " << accountNumber << std::endl;
        }
    }
    else
    {
        std::cout << "Client " << clientId << " could not access account " << accountNumber << std::endl;
    }
}
