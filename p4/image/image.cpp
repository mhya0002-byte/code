#include "splashkit.h"

const string IMAGE_NAME = "tree";

int main()
{
    bitmap tree;
    double rotation, scale_x, scale_y;
    string user_input;

    write("What is the X scale factor for the first image? ");
    user_input = read_line();
    scale_x = to_double(user_input);

    write("What is the Y scale factor for the first image? ");
    user_input = read_line();
    scale_y = to_double(user_input);

    write("How many degrees to rotate the second image? ");
    user_input = read_line();
    rotation = to_double(user_input);

    open_window("Image Drawing", 500, 300);

    tree = load_bitmap(IMAGE_NAME, "tree.png");

    draw_bitmap(tree, 10, 20, option_scale_bmp(scale_x, scale_y));
    draw_bitmap(IMAGE_NAME, 220, 20, option_rotate_bmp(rotation));

    refresh_screen();
    delay(10000);
}