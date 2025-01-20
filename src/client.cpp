#include "../include/Bank.hpp"

void clientSimulation(Bank &bank, int clientId)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)) + clientId);
    for (int i = 0; i < 10; ++i)
    {
        int accountNumber = 1000 + std::rand() % 5;
        int action = std::rand() % 3;
        int amount = (std::rand() % 100) + 1;

        auto account = bank.getAccount(accountNumber);
        if (account)
        {
            switch (action)
            {
            case 0:
                account->deposit(amount);
                std::cout << "Client " << clientId << ": Deposited " << amount
                          << " to account " << accountNumber << std::endl;
                break;
            case 1:
                account->withdraw(amount);
                std::cout << "Client " << clientId << ": Attempted to withdraw " << amount
                          << " from account " << accountNumber << std::endl;
                break;
            case 2:
                std::cout << "Client " << clientId << ": Checked balance of account "
                          << accountNumber << ": " << account->getBalance() << std::endl;
                break;
            }
        }
        else
        {
            std::cout << "Client " << clientId << ": Account " << accountNumber
                      << " not found." << std::endl;
        }
    }
}
