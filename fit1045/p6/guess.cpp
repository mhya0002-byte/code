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

int read_integer_range(string prompt, int bound_1, int bound_2)
{
    int lower_bound;
    int upper_bound;
    if (bound_1 <= bound_2)
    {
        lower_bound = bound_1;
        upper_bound = bound_2;
    }
    else
    {
        lower_bound = bound_2;
        upper_bound = bound_1;
    }
    int input = read_integer(prompt);
    while (input < lower_bound || input > upper_bound)
    {
        write_line("Please enter a value between " + to_string(lower_bound) + " and " + to_string(upper_bound) + ".");
        input = read_integer(prompt);
    }
    return input;
}

bool perform_guess(int guess_number, int target)
{
    int guess;

    guess = read_integer_range("Guess " + to_string(guess_number) + ": ", 0, 100);

    if (target > guess)
    {
        write_line("The number is larger than " + to_string(guess));
    }
    else if (target < guess)
    {
        write_line("The number is smaller than " + to_string(guess));
    }
    else
    {
        write_line("Well done! The number was " + to_string(guess));
    }
    return guess == target;
}

const int MAX_NUMBER = 100;
const int NUM_GUESSES = 7;

void play_game()
{
    int my_number = rnd(MAX_NUMBER);
    int guess_number = 0;

    bool got_it;

    do
    {
        guess_number++;
        got_it = perform_guess(guess_number, my_number);
    } while (guess_number < NUM_GUESSES && !got_it);

    if (!got_it)
    {
        write_line("You ran out of guesses! The number was " + to_string(my_number));
    }
}

int main()
{
    play_game();
    return 0;
}