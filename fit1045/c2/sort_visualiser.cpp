#include "splashkit.h"
#include "splashkit-arrays.h"

const int DATA_SIZE = 10;
const double MAX_VALUE = DATA_SIZE;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int MARGIN = 10;

const color BACKGROUND_COLOUR = color_black();
const color OUTLINE_COLOUR = color_light_blue();
const color FILL_COLOUR = color_dark_blue();
const color HIGHLIGHT_COLOUR = color_yellow();

void swap(int i1, int i2, fixed_array<int, DATA_SIZE> &data)
{
    int temp;

    temp = data.get(i1);

    data.set(i1, data.get(i2));

    data.set(i2, temp);
}

void visualise_array(const fixed_array<int, DATA_SIZE> &data, int highlight_index)
{
    double bar_distance = SCREEN_WIDTH / DATA_SIZE;
    double bar_width = bar_distance - MARGIN * 2;

    clear_screen(BACKGROUND_COLOUR);

    for (int i = 0; i < DATA_SIZE; i++)
    {
        double bar_height = data.get(i) / MAX_VALUE * SCREEN_HEIGHT;
        double x = i * bar_distance + MARGIN;
        double y = SCREEN_HEIGHT - bar_height;

        color selected_colour = (i == highlight_index or i == highlight_index + 1) ? HIGHLIGHT_COLOUR : FILL_COLOUR;

        fill_rectangle(selected_colour, x, y, bar_width, bar_height);
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
        visualise_array(data, i);
        delay(100);
    }
}

void bubble_sort(fixed_array<int, DATA_SIZE> &data)
{
    for (int range = DATA_SIZE; range > 1; range--)
    {
        bubble_sort_pass(data, range);
    }
}

void fill_array_random(fixed_array<int, DATA_SIZE> &data, int min, int max)
{
    for (int i = 0; i < DATA_SIZE; i++)
    {
        data.set(i, rnd(min, max));
    }
}

int main()
{
    open_window("Sort visualiser", SCREEN_WIDTH, SCREEN_HEIGHT);

    fixed_array<int, DATA_SIZE> data;

    fill_array_random(data, 1, 10);

    bubble_sort(data);

    delay(2000);

    return 0;
}