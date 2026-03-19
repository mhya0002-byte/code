#include "splashkit.h"
#include "utilities.h"

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

bool read_boolean(string prompt)
{
    string input = read_string(prompt);

    input = to_lowercase(input);

    while (!(input == "y" or input == "n"))
    {
        write_line("Enter Y or N!");
        input = read_string(prompt);
    }
    if (input == "y")
    {
        return true;
    }
    else if (input == "n")
    {
        return false;
    }
    else
    {
        return false;
    }
}

void draw_heading_line(int width)
{
    write("+");
    int i = 0;
    do
    {
        i++;
        write("-");
    } while (i < width - 2);
    write_line("+");
}

void draw_title(string title, int width)
{
    draw_heading_line(width);
    write("| " + title);
    int i = 0;
    do
    {
        i++;
        write(" ");
    } while (i < width - (length_of(title) + 3));
    write_line("|");
    draw_heading_line(width);
}

int score(int goals, int behinds)
{
    return (goals * 6) + behinds;
}

void initialise(string team_name, int &goals, int &behinds)
{
    draw_title("Score Calculator", 26);
    write_line();
    write_line("Welcome to the AFL score calculator!");
    write_line();

    team_name = read_string("Enter team name: ");
    goals = read_integer("Enter goals: ");
    behinds = read_integer("Enter behinds: ");

    write_line();
    write_line("Score: " + to_string(score(goals, behinds)));
    write_line();
}

void draw_main_menu()
{
    draw_title("Main Menu", 26);
    write_line();
    write_line("1: Update goals");
    write_line("2: Update behinds");
    write_line("3: Print details");
    write_line("4: Quit");
    draw_heading_line(26);
}

void update(int &var, int new_value)
{
    var = new_value;
}

int main()
{

    int goals, behinds;
    string team_name;
    initialise(team_name, goals, behinds);

    bool quit = false;

    int value_to_update;

    do
    {

        draw_main_menu();

        int menu_selection = read_integer_range("Enter Option: ", 1, 4);

        write_line();

        switch (menu_selection)
        {
        case 1:

            write_line("Current goals: " + to_string(goals));
            value_to_update = read_integer("Enter new goals: ");
            update(goals, value_to_update);
            write_line();
            write_line("Current score: " + to_string(score(goals, behinds)));
            break;

        case 2:
            write_line("Current behinds: " + to_string(behinds));
            value_to_update = read_integer("Enter new behinds: ");
            update(behinds, value_to_update);
            write_line();
            write_line("Current score: " + to_string(score(goals, behinds)));
            break;

        case 3:
            write_line("Stats for " + team_name + ":");
            write_line("Goals: " + to_string(goals));
            write_line("Behinds: " + to_string(behinds));
            write_line("Total score: " + to_string(score(goals, behinds)));
            break;

        case 4:
            quit = read_boolean("Are you sure you want to quit? (Y/N): ");
            break;
        }
        write_line();
        write_line();
    } while (quit == false);

    write_line("Bye!");
}