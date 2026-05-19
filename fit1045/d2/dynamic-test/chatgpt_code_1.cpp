#include <stdlib.h>
#include "splashkit.h"
#include "utilities.h"

int main()
{
    double *data_ptr = NULL;

    int size = 0;
    int capacity = 2; // initial capacity

    data_ptr = (double *)malloc(capacity * sizeof(double));

    if (data_ptr == NULL)
    {
        write_line("Memory allocation failed");
        return 1;
    }

    while (true)
    {
        string input = read_string("Enter a number (or q to quit): ");

        if (input == "q")
        {
            break;
        }

        double value = convert_to_double(input);

        // Expand array if full
        if (size >= capacity)
        {
            capacity *= 2;

            double *temp = (double *)realloc(data_ptr, capacity * sizeof(double));

            if (temp == NULL)
            {
                write_line("Memory reallocation failed");
                free(data_ptr);
                return 1;
            }

            data_ptr = temp;

            write_line("Array expanded to capacity: " + to_string(capacity));
        }

        data_ptr[size] = value;
        size++;
    }

    write_line("\nStored values:");

    for (int i = 0; i < size; i++)
    {
        write_line("Value at index " + to_string(i) + ": " + to_string(data_ptr[i]));
    }

    free(data_ptr);
    data_ptr = NULL;

    return 0;
}
