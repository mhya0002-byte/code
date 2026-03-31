#include "splashkit.h"

int main()
{
    string user_input;
    double total = 0;
    double average = 0;
    int count = 0;

    write_line("Welcome to the simple stats calculator:");
    write_line();

    do
    {

        write("Enter value: ");
        user_input = read_line();
        write_line();

        count++;
        write_line("Count: " + to_string(count));

        total += to_double(user_input);
        write_line("Total: " + to_string(total, 2));

        average = total / count;
        write_line("Average: " + to_string(average, 2));
        write_line();

        write("Add another value? (Y/N) ");
        user_input = read_line();
    } while (user_input != "N");

}