#include "splashkit.h"

class account
{
    int balance;

public:
    string name;

    account(string name, int balance)
    {
        this->name = name;
        this->balance = balance;
    }

    account()
    {
        name = "Default Name";
        balance = 0;
    }

    void deposit(int amount)
    {
        if (amount < 0)
        {
            balance += amount;
        }
    }

    void withdraw(int amount)
    {
        if (amount < 0)
        {
            balance -= amount;
        }
    }

    void print()
    {
        write_line("Name: " + name);
        write_line("Balance: " + to_string(balance / 100.00));
    }

    double get_balance()
    {
        return balance;
    }
};

int main()
{
    return 0;
}