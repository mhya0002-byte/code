#include "splashkit.h"

const int MAX_SIZE = 5;
struct double_array
{
    double data[MAX_SIZE];
    int size;
};

void sort(double_array &arr)
{
    double temp;
    for (int i = 0; i < arr.size - 1; i++)
    {
        for (int j = 0; j < MAX_SIZE - i - 1; j++)
        {
            if (arr.data[j] > arr.data[j + 1])
            {
                temp = arr.data[j];
                arr.data[j] = arr.data[j + 1];
                arr.data[j + 1] = temp;
            }
        }
    }
}

int main()
{
    double_array arr = {{5, 3, 2}, 3};
    sort(arr);
    for (int i = 0; i < 10; i++)
    {
        write_line(arr.data[i]);
    }
}