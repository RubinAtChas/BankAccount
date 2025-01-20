#ifndef RANDOMHANDLER_HPP
#define RANDOMHANDLER_HPP

#include "../include/Bank.hpp"
#include <iostream>
#include <memory>
#include <mutex>
#include <random>

int getRandomNumber(int min, int max);
int getRandomClient();
int getRandomAmount();
int getRandomAccount();
void clientSimulation(Bank &bank, int clientId, std::mutex &bankMutex);

#endif
