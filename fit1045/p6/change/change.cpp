#include "splashkit.h"

string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

int read_integer(string prompt)
{
    string input = read_string(prompt);
    while (!is_integer(input))
    {
        write_line("Please enter a whole number");
        input = read_string(prompt);
    }
    return to_integer(input);
}

int calculate_and_output_change(int change_value, int coin_value, string coin_text)
{
    // Calculate the number of coins to give using the coin value.
    int to_give = change_value / coin_value;

    // Output the number of coins with the coin text
    write(to_string(to_give) + " x " + coin_text);

    // Return the amount of change remaining
    return change_value - to_give * coin_value;
}

const int NUM_COIN_TYPES = 6;

void get_coin(int coin_index, int &value, string &text)
{
    switch (coin_index)
    {
    case 0:
        value = 200;
        text = "$2, ";
        break;
    case 1:
        value = 100;
        text = "$1, ";
        break;
    case 2:
        value = 50;
        text = "50c, ";
        break;
    case 3:
        value = 20;
        text = "20c, ";
        break;
    case 4:
        value = 10;
        text = "10c, ";
        break;
    case 5:
        value = 5;
        text = "5c";
        break;
    default:
        value = 1;
        text = "ERROR";
        break;
    }
}

int main()
{
    string again;

    do
    {
        int cost_of_item;
        int amount_paid;
        int change_value;

        int coin_value;
        string coin_text;

        cost_of_item = read_integer("Cost of item (in cents): ");
        amount_paid = read_integer("Amount paid (in cents): ");

        change_value = amount_paid - cost_of_item;
        write_line("Change to give: " + to_string(change_value));

        int i = 0;
        while (i < NUM_COIN_TYPES)
        {
            get_coin(i, coin_value, coin_text);
            change_value = calculate_and_output_change(change_value, coin_value, coin_text);
            i++;
        }
        write_line();
        again = read_string("Run again: ");
    } while (again != "N" && again != "n");
}