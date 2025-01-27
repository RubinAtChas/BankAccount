#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include "include/Bank.hpp"
#include "include/RandomHandler.hpp"

int main()
{
    Bank bank;
    std::mutex bankMutex;

    for (int i = 0; i < 5; ++i)
    {
        bank.addAccount(1000 + i, 1000);
    }

    std::thread waitForEnterThread(waitForEnter);

    std::vector<std::thread> clients;
    for (int i = 0; i < 10; ++i)
    {
        clients.emplace_back(clientSimulation, std::ref(bank), i + 1, std::ref(bankMutex));
    }

    for (auto &client : clients)
    {
        client.join();
    }
    waitForEnterThread.join();

    std::cout << "\nFinal account balances:\n";
    bank.displayAllAccounts();

    return 0;
}
