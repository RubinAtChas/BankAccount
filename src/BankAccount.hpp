#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

class BankAccount
{
public:
    BankAccount();

    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;

private:
    double balance;
    int accountNumber;
};

#endif // BANKACCOUNT_HPP