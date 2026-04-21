#include "splashkit.h"
#include "splashkit-arrays.h"

const int DATA_SIZE = 20;

const double SCREEN_WIDTH = 1280;
const double SCREEN_HEIGHT = 720;

const double MARGIN = 10;

const color BACKGROUND_COLOUR = color_black();
const color OUTLINE_COLOUR = color_light_blue();
const color FILL_COLOUR = color_dark_blue();
const color HIGHLIGHT_COLOUR = color_yellow();

int max(fixed_array<int, DATA_SIZE> data)
{
    int current_max = 0;
    for (int i = 0; i < length(data); i++)
    {
        if (data[i] > current_max)
        {
            current_max = data[i];
        }
    }
    return current_max;
}

void swap(int i1, int i2, fixed_array<int, DATA_SIZE> &data)
{
    int temp;

    temp = data.get(i1);

    data.set(i1, data.get(i2));

    data.set(i2, temp);
}

void visualise_array(const fixed_array<int, DATA_SIZE> &data, int highlight_index, int algorithm)
{
    double bar_distance = SCREEN_WIDTH / DATA_SIZE;
    double bar_width = bar_distance - (MARGIN * 2);

    clear_screen(BACKGROUND_COLOUR);

    string text = algorithm == 0 ? "Bubble Sort" : "Quick Sort";

    draw_text(text, HIGHLIGHT_COLOUR, 0, 0);

    for (int i = 0; i < DATA_SIZE; i++)
    {
        double max_value = max(data);
        double bar_height = data.get(i) / max_value * SCREEN_HEIGHT;
        double x = i * bar_distance + MARGIN;
        double y = SCREEN_HEIGHT - bar_height;

        color selected_colour = (i == highlight_index or (i == highlight_index + 1 and algorithm == 0)) ? HIGHLIGHT_COLOUR : FILL_COLOUR;

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
        visualise_array(data, i, 0);
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

int partition(fixed_array<int, DATA_SIZE> &data, int low, int high)
{

    // Selecting last element as the pivot
    int pivot = data[high];

    // Index of element just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        // If current element is smaller than or
        // equal to pivot
        if (data[j] <= pivot)
        {
            i++;
            swap(i, j, data);

            visualise_array(data, pivot, 1);
            delay(500);
        }
    }

    // Put pivot to its position
    swap(i + 1, high, data);

    visualise_array(data, pivot, 1);
    delay(500);

    // Return the point of partition
    return (i + 1);
}

void quick_sort(fixed_array<int, DATA_SIZE> &data, int low, int high)
{

    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high)
    {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(data, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quick_sort(data, low, pi - 1);
        quick_sort(data, pi + 1, high);
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
    while (!quit_requested())
    {
        open_window("Martin's sort visualiser", SCREEN_WIDTH, SCREEN_HEIGHT);

        fixed_array<int, DATA_SIZE> data;

        fill_array_random(data, 1, 10);

        bubble_sort(data);
        
        delay(2000);

        fill_array_random(data, 1, 10);

        quick_sort(data, 0, DATA_SIZE - 1);

        delay(2000);

        break;
    }

    return 0;
}