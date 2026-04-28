#include "splashkit.h"
#include "bounded_array.hpp"

int main()
{
    bounded_array<double, 50> numbers;

    numbers.add(1);
    numbers.add(2);
    numbers.add(3);
    numbers.add(4);
    numbers.add(5);

    numbers[2] = 67;

    try
    {
        numbers[-1] = 5;
    }
    catch (array_invalid_index)
    {
        write_line("Invalid index for assignment!");
    }

    numbers.remove(1);

    try
    {
        numbers.remove(-2);
    }
    catch (array_invalid_index)
    {
        write_line("Invalid index for removal!");
    }

    numbers.fill(3, 67);

    try
    {
        numbers.fill(100, 67);
    }
    catch (array_full)
    {
        write_line("Array full!");
    }

    for (int i = 0; i < numbers.length(); i++)
    {
        write_line(to_string(numbers.get(i)));
    }
}