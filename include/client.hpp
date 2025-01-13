#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Bank.hpp"
//#include "bankAccount.hpp"
class Client
{
   private:
    int clientId;
    Bank bank;  

    public:
    Client();       
    Client(int clientId, Bank bank);

    //void simulate(); 
};

#endif