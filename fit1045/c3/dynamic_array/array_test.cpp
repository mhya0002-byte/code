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

    numbers.remove(1);

    numbers.fill(3, 67);

    for (int i = 0; i < numbers.length(); i++)
    {
        write_line(to_string(numbers.get(i)));
    }
}