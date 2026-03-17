#include "splashkit.h"
#include "utilities.h"

string team_name;
int goals, behinds, score;

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

void initialise()
{
    draw_title("Score Calculator", 26);
    write_line();
    write_line("Welcome to the AFL score calculator!");
    write_line();

    team_name = read_string("Enter team name: ");
    goals = read_integer("Enter goals: ");
    behinds = read_integer("Enter behinds: ");

    score = (goals * 6) + behinds;

    write_line();
    write_line("Score: " + to_string(score));
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

int main()
{
    initialise();
    draw_main_menu();

}