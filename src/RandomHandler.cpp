#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>
#include "../include/RandomHandler.hpp"

std::random_device rd;
std::mt19937 gen(rd());

struct RandomTransactionData
{
    BankAccount &account;
    int clientId;
    int accountNumber;
    int amount;
    std::mutex &bankMutex;
};

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

void depositRandom(RandomTransactionData data)
{
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(data.bankMutex);
            data.account.deposit(data.amount);
            std::cout << "Client " << data.clientId << " deposited " << data.amount << " to account " << data.accountNumber << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(6000));
    }
}

void withdrawRandom(RandomTransactionData data)
{
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(data.bankMutex);
            data.account.withdraw(data.amount);
            std::cout << "Client " << data.clientId << " withdrew " << data.amount << " from account " << data.accountNumber << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
}

void showBalance(RandomTransactionData data)
{
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(data.bankMutex);
            std::cout << "Client " << data.clientId << " checked balance of account " << data.accountNumber << ": " << data.account.getBalance() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(22000));
    }
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

    RandomTransactionData data = {*account, clientId, accountNumber, amount, bankMutex};

    std::thread depositThread(depositRandom, data);
    std::thread withdrawThread(withdrawRandom, data);
    std::thread showBalanceThread(showBalance, data);

    depositThread.join();
    withdrawThread.join();
    showBalanceThread.join();
}
