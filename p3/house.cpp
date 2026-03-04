#include "splashkit.h"

int main()
{
    open_window("House drawing by Martin!", 800, 600); // Create a window 800x600 pixels in size

    clear_screen(COLOR_LIGHT_BLUE); // Fill the screen with a light blue sky

    fill_ellipse(COLOR_YELLOW, -150, -150, 300, 300); // Sun

    fill_ellipse(COLOR_GREEN, 0, 400, 800, 400); // Hill

    fill_rectangle(COLOR_GRAY, 300, 300, 200, 200); // Base of house

    fill_rectangle(COLOR_LIGHT_BLUE, 400, 350, 50, 50); // Window

    draw_rectangle(COLOR_BLACK, 400, 350, 50, 50); // Window frame

    fill_triangle(COLOR_BROWN, 250, 300, 400, 150, 550, 300); // Roof of house

    fill_rectangle(COLOR_BROWN, 320, 400, 50, 100); // Door

    fill_ellipse(COLOR_BLACK, 320, 450, 10, 10); // Doorknob

    refresh_screen();

    delay(5000);
}