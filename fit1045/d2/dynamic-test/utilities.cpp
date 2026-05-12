#include "utilities.h"
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

double read_double(string prompt)
{
  string line = read_string(prompt);
  while (!is_double(line))
  {
    write_line("Please enter a number.");
    line = read_string(prompt);
  }
  return to_double(line);
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