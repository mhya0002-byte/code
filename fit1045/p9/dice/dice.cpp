#include "splashkit.h"

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

int main()
{
    die d6(6);
    die d12(12);

    for (int i = 0; i < 3; i++)
    {
        d6.roll();
        d6.print();
    }

    for (int i = 0; i < 3; i++)
    {
        d12.roll();
        d12.print();
    }
}