#include "splashkit.h"
#include "utilities.h"

/**
 * An account value storing the name and balance of an account.
 *
 * @field name The name of the account.
 * @field balance The amount of funds allocated to the account.
 */
struct account
{
    string name;
    int balance;
};

/**
 * Print the account details to the terminal.
 *
 * @param act the account to print.
 */
void print_account(account &act)
{
    write_line("Name: " + act.name);
    write_line("Balance: " + to_string(act.balance));
}

int main()
{
    account *ptr;
    ptr = new account();

    // Store data in the account
    ptr->name = "My Account";
    ptr->balance = 154;

    // Print the account using the pointer
    write_line("Name: " + ptr->name);
    write_line("Balance: " + to_string(ptr->balance));

    // Print the account using the function
    print_account(*ptr);

    // Clean up
    delete ptr;
    ptr = nullptr;
}