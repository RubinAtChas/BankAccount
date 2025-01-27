#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <unordered_map>
#include "../include/RandomHandler.hpp"

std::condition_variable cv;
std::atomic<bool> running(true);
std::mutex mtx;
std::random_device rd;
std::mt19937 gen(rd());

class Logger
{
    public:
        void logDeposit(int accountNumber, int amount)
        {
            std::lock_guard<std::mutex> lock(logMutex);
            logs[accountNumber].totalDeposits += amount;
            logs[accountNumber].balance += amount;
        }

        void logWithdraw(int accountNumber, int amount)
        {
            std::lock_guard<std::mutex> lock(logMutex);
            logs[accountNumber].totalWithdraws += amount;
            logs[accountNumber].balance -= amount;
        }

        void printLog(int accountNumber)
        {
            std::lock_guard<std::mutex> lock(logMutex);
            const auto& log = logs[accountNumber];
            std::cout << "\n\n***Account" << accountNumber << "*** log:" << std::endl;
            std::cout << "***Total deposits: " << log.totalDeposits << std::endl;
            std::cout << "***Total withdraws: " << log.totalWithdraws << std::endl;
            std::cout << "***Balance: " << log.balance << "\n" << std::endl;
        }

    private:
        struct AccountLog
        {
            int totalDeposits = 0;
            int totalWithdraws = 0;
            int balance = 0;
        };

        std::unordered_map<int, AccountLog> logs;
        std::mutex logMutex;
};

Logger logger;

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

    {
        std::lock_guard<std::mutex> lock(data.bankMutex);
        data.account.deposit(data.amount);
        logger.logDeposit(data.accountNumber, data.amount);
        std::cout << "Client " << data.clientId << " deposited " << data.amount << " to account " << data.accountNumber << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void withdrawRandom(RandomTransactionData data)
{

    {
        std::lock_guard<std::mutex> lock(data.bankMutex);
        data.account.withdraw(data.amount);
        logger.logWithdraw(data.accountNumber, data.amount);
        std::cout << "Client " << data.clientId << " withdrew " << data.amount << " from account " << data.accountNumber << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}

void showBalance(RandomTransactionData data)
{

    {
        std::lock_guard<std::mutex> lock(data.bankMutex);
        std::cout << "Client " << data.clientId << " checked balance of account " << data.accountNumber << ": " << data.account.getBalance() << std::endl;
        logger.printLog(data.accountNumber);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2200));
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
    while (running)
    {
        std::thread depositThread(depositRandom, data);
        std::thread withdrawThread(withdrawRandom, data);
        std::thread showBalanceThread(showBalance, data);

        depositThread.join();
        withdrawThread.join();
        showBalanceThread.join();
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait_for(lock, std::chrono::seconds(1), []
                    { return !running; }); // HÄR VA VI SENAST, KOLLA HÄR MISSA MIG INTE
    }
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