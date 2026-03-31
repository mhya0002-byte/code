#include "splashkit.h"

int i = 0;

int main()
{
    // Writes the numbers 0-9 using a while loop
    while (i < 10)
    {
        write_line(i);
        i++;
    }


    i = 0;

    // Writes the numbers 0-9 again, but this time using a goto command
loop:
    write_line(i);
    i++;
    if (i < 10)
    {
        goto loop;
    }

}
