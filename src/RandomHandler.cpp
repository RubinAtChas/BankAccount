#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>
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

void clientSimulation(Bank &bank, int clientId, std::mutex &bankMutex)
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
        std::thread depositThread([&]()
                                  {
            while (true)
            {
                {
                    std::lock_guard<std::mutex> lock(bankMutex);
                    account->deposit(amount);
                    std::cout << "Client " << clientId << " deposited " << amount << " to account " << accountNumber << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(6000));
            } });

        std::thread withdrawThread([&]()
                                   {
            while (true)
            {
                {
                    std::lock_guard<std::mutex> lock(bankMutex);
                    account->withdraw(amount);
                    std::cout << "Client " << clientId << " withdrew " << amount << " from account " << accountNumber << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            } });
        std::thread showBalanceThread([&]()
                                      {
            while (true)
            {
                {
                    std::lock_guard<std::mutex> lock(bankMutex);
                    std::cout << "Client " << clientId << " checked balance of account " << accountNumber << ": " << account->getBalance() << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(22000));
            } });

        {
        }

        depositThread.join();
        withdrawThread.join();
    }
}
