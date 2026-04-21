#include "splashkit.h"

string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

int read_integer(string prompt)
{
    string line = read_string(prompt);
    while (!is_integer(line))
    {
        write_line("Please enter a whole number.");
        line = read_string(prompt);
    }
    return to_integer(line);
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

class die
{
    int sides;
    int current_value;

public:
    int get_current_value()
    {
        return current_value;
    }

    void roll()
    {
        current_value = rnd(1, sides);
    }

    die(int sides)
    {
        this->sides = sides;
        roll();
    }

    void print()
    {
        write_line(to_string(sides) + " sides: value is " + to_string(current_value));
    }
};

void print_menu()
{
    write_line("1: Roll die");
    write_line("2: Get new die");
    write_line("3: Quit");
}

int read_menu_input()
{
    return read_integer_range("> ", 1, 3);
}

int main()
{
    die initial_die(6);

    die current_die = initial_die;

    int menu_selection;

    write_line("Sides: 6");

    do
    {
        write_line();
        print_menu();
        menu_selection = read_menu_input();

        switch (menu_selection)
        {
        case 1:
            current_die.roll();
            current_die.print();
            break;

        case 2:
            int new_sides = read_integer("Sides: ");
            die new_die(new_sides);
            current_die = new_die;
            break;
        }
    } while (menu_selection != 3);
}