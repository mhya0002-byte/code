#include "splashkit.h"
#include "splashkit-arrays.h"

const int DATA_SIZE = 10;
const double MAX_VALUE = DATA_SIZE;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int MARGIN = 10;

const color OUTLINE_COLOUR = color_light_blue();
const color FILL_COLOUR = color_dark_blue();

fixed_array<int, DATA_SIZE> shuffled_list()
{
    dynamic_array<int> temp_array;
    fixed_array<int, DATA_SIZE> shuffled_array;

    for (int i = 1; i < DATA_SIZE + 1; i++)
    {
        temp_array.add(i);
    }

    int rand_value;

    for (int i = 0; i < DATA_SIZE - 1; i++)
    {
        int rand_index = rnd(0, length(temp_array));
        rand_value = temp_array.get(rand_index);
        temp_array.remove(rand_index);
        shuffled_array.set(i, rand_value);
    }
    return shuffled_array;
}

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

    fixed_array<int, DATA_SIZE> data = shuffled_list();

    bubble_sort(data);

    delay(2000);

    return 0;
}