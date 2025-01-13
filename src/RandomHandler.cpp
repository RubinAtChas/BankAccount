#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

int getRandomNumber(int min, int max)
{
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

int getRandomClient()
{
    return getRandomNumber(1, 10);
}

int getRandomAmount()
{
    return getRandomNumber(1, 100000);
}

int getRandomAccount()
{
    return getRandomNumber(1, 5);
}