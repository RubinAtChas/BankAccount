#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "include/Bank.hpp"
#include "src/RandomHandler.cpp"

int main()
{
    Bank bank;

    for (int i = 0; i < 5; ++i)
    {
        bank.addAccount(1000 + i, 1000);
    }

    std::vector<std::thread> clients;
    for (int i = 0; i < 10; ++i)
    {
        clients.emplace_back(clientSimulation, std::ref(bank), i + 1);
    }

    for (auto &client : clients)
    {
        client.join();
    }

    std::cout << "\nFinal account balances:\n";
    bank.displayAllAccounts();

    return 0;
}
