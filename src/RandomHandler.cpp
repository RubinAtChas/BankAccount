#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <atomic>
#include <condition_variable>
#include "../include/RandomHandler.hpp"

std::condition_variable cv;
std::atomic<bool> running(true);
std::mutex mtx;
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

void depositRandom(RandomTransactionData data)
{
    while (running)
    {
        {
            std::lock_guard<std::mutex> lock(data.bankMutex);
            data.account.deposit(data.amount);
            std::cout << "Client " << data.clientId << " deposited " << data.amount << " to account " << data.accountNumber << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

void withdrawRandom(RandomTransactionData data)
{
    while (running)
    {
        {
            std::lock_guard<std::mutex> lock(data.bankMutex);
            data.account.withdraw(data.amount);
            std::cout << "Client " << data.clientId << " withdrew " << data.amount << " from account " << data.accountNumber << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
}

void showBalance(RandomTransactionData data)
{
    while (running)
    {
        {
            std::lock_guard<std::mutex> lock(data.bankMutex);
            std::cout << "Client " << data.clientId << " checked balance of account " << data.accountNumber << ": " << data.account.getBalance() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2200));
    }
}

void clientSimulation(Bank &bank, int clientId, std::mutex &bankMutex)
{
    int accountNumber = getRandomAccount();
    int amount = getRandomAmount();
    std::shared_ptr<BankAccount> account;

    {
        std::lock_guard<std::mutex> lock(bankMutex);
        account = bank.getAccount(accountNumber);
    }

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

void waitForEnter()
{
    std::cin.get();
    {
        std::lock_guard<std::mutex> lock(mtx);
        running = false;
    }
    cv.notify_all();
}
