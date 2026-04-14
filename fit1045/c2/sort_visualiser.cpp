#include "splashkit.h"
#include "splashkit-arrays.h"

const int DATA_SIZE = 10;
const double MAX_VALUE = DATA_SIZE;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int MARGIN = 10;

const color OUTLINE_COLOUR = color_light_blue();
const color FILL_COLOUR = color_dark_blue();


void swap(int i1, int i2, fixed_array<int, DATA_SIZE> &data)
{
    int temp;

    temp = data.get(i1);

    data.set(i1, data.get(i2));

    data.set(i2, temp);
}

void visualise_array(const fixed_array<int, DATA_SIZE> &data)
{
    double bar_distance = SCREEN_WIDTH / DATA_SIZE;
    double bar_width = bar_distance - MARGIN * 2;

    clear_screen();

    for (int i = 0; i < DATA_SIZE; i++)
    {
        double bar_height = data.get(i) / MAX_VALUE * SCREEN_HEIGHT;
        double x = i * bar_distance + MARGIN;
        double y = SCREEN_HEIGHT - bar_height;

        fill_rectangle(FILL_COLOUR, x, y, bar_width, bar_height);
        draw_rectangle(OUTLINE_COLOUR, x, y, bar_width, bar_height);
    }

    refresh_screen();
}

void bubble_sort_pass(fixed_array<int, DATA_SIZE> &data, int range)
{
    for (int i = 0; i < range - 1; i++)
    {
        if (data.get(i) > data.get(i + 1))
        {
            swap(i, i + 1, data);
        }
        visualise_array(data);
        delay(50);
    }
}

void bubble_sort(fixed_array<int, DATA_SIZE> &data)
{
    for (int range = DATA_SIZE; range > 1; range--)
    {
        bubble_sort_pass(data, range);
    }
}

int main()
{
    open_window("Sort visualiser", SCREEN_WIDTH, SCREEN_HEIGHT);

    fixed_array<int, DATA_SIZE> data;

    data.set(0, 6);
    data.set(1, 5);
    data.set(2, 8);
    data.set(3, 3);
    data.set(4, 7);
    data.set(5, 2);
    data.set(6, 1);
    data.set(7, 10);
    data.set(8, 9);
    data.set(9, 4);
    

    bubble_sort(data);

    delay(2000);

    return 0;
}