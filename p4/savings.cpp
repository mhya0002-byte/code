#include "splashkit.h"

int main()
{
    string event, user_input;
    double savings_goal, time_until_purchase, starting_money, savings_needed, savings_needed_per_week;

    write("What are you saving for? Enter title: ");
    event = read_line();

    write("How much in total do you need to save? Enter dollars: ");
    user_input = read_line();
    savings_goal = to_double(user_input);
    write_line();

    write("How long before the purchase? Enter weeks: ");
    user_input = read_line();
    time_until_purchase = to_double(user_input);

    write("How much have you already saved? Enter dollars: ");
    user_input = read_line();
    starting_money = to_double(user_input);
    write_line();

    savings_needed = savings_goal - starting_money;

    write("To reach your savings goal you must save an additional " + to_string(savings_needed, 2) + " dollars.");
    write_line();

    savings_needed_per_week = savings_needed / time_until_purchase;

    write("To reach your savings goal in " + to_string(time_until_purchase, 2) + " weeks, you will need to save " + to_string(savings_needed_per_week, 2) + " dollars per week.");
}