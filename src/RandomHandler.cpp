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
/**
 * @brief Get the Random Number object
 * 
 * @param min A minimum value that the random generator can get
 * @param max A maximum value that the random genereator can get.
 * @return An int that is returning the random generated number.
 */
int getRandomNumber(int min, int max)
{
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}
/**
 * @brief Get the Random Client object between in this program 1000-1010.
 * 
 * @return an int value that is returning a random number between 1000-1010, in this program.
 */
int getRandomClient()
{
    return getRandomNumber(1000, 1010);
}
/**
 * @brief Get the Random Amount object, this is for deposit and withdrawl.
 * 
 * @return int returns a random amount between 1000 - 10 000 in this program
 */
int getRandomAmount()
{
    return getRandomNumber(1000, 10000);
}
/**
 * @brief Get the Random Account, for which account each client should access with a withdrawl och deposit.
 * 
 * @return int return between 1000 - 1005, in this program.
 */
int getRandomAccount()
{
    return getRandomNumber(1000, 1005);
}
/**
 * @brief This function randommizes a client that deposites ar random amount to a random account, with previous functions.
 * 
 * @param data A struct variable to make is easier to access varaibles that are in the struct.
 */
void depositRandom(RandomTransactionData data)
{

    {
        std::lock_guard<std::mutex> lock(data.bankMutex);
        data.account.deposit(data.amount);
        std::cout << "Client " << data.clientId << " deposited " << data.amount << " to account " << data.accountNumber << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
/**
 * @brief This function randommizes a client that withdrawls a random amount to a random account, with previous functions.
 * 
 * @param data A struct variable to make is easier to access varaibles that are in the struct.
 */
void withdrawRandom(RandomTransactionData data)
{

    {
        std::lock_guard<std::mutex> lock(data.bankMutex);
        data.account.withdraw(data.amount);
        std::cout << "Client " << data.clientId << " withdrew " << data.amount << " from account " << data.accountNumber << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}
/**
 * @brief A function that displays that a client is looking at the amount of balance that a account has.
 * 
 * @param data A struct variable to make is easier to access varaibles that are in the struct.
 */
void showBalance(RandomTransactionData data)
{

    {
        std::lock_guard<std::mutex> lock(data.bankMutex);
        std::cout << "Client " << data.clientId << " checked balance of account " << data.accountNumber << ": " << data.account.getBalance() << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2200));
}
/**
 * @brief A function that creates the threads of the running program.
 * 
 * @param bank a variable from the bank class, to access bankaccount
 * @param clientId a variable that to know which ID is suppose to be used in the thread.
 * @param bankMutex A mutex to hold a resource from being used from a scope where it is not suppose to run.
 */
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