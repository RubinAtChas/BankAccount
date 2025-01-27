#ifndef RANDOMHANDLER_HPP
#define RANDOMHANDLER_HPP

#include "../include/Bank.hpp"
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <chrono>
#include <atomic>
#include <condition_variable>

extern std::condition_variable cv;
extern std::atomic<bool> running;
extern std::mutex mtx;
extern std::random_device rd;
extern std::mt19937 gen;

struct RandomTransactionData
{
    BankAccount &account;
    int clientId;
    int accountNumber;
    int amount;
    std::mutex &bankMutex;
};

int getRandomNumber(int min, int max);
int getRandomClient();
int getRandomAmount();
int getRandomAccount();
void clientSimulation(Bank &bank, int clientId, std::mutex &bankMutex);
void waitForEnter();

#endif
