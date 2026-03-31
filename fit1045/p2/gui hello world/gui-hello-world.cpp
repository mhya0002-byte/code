#include "splashkit.h"

int main()
{
    open_window("Martin's First GUI Program", 640, 480);

    clear_screen(color_white());
    draw_text("Hi World! - Martin", color_black(), 50, 50);

    // Draw the H
    fill_rectangle(color_red(), 50, 100, 20, 100);
    fill_rectangle(color_red(), 70, 140, 40, 20);
    fill_rectangle(color_red(), 110, 100, 20, 100);

    // Draw the I
    fill_rectangle(color_orange(), 150, 100, 20, 100);

    // Draw the W
    fill_triangle(color_green(), 50, 250, 90, 370, 120, 250);
    fill_triangle(color_green(), 90, 250, 120, 370, 160, 250);
    fill_triangle(color_white(), 70, 250, 90, 310, 110, 250);
    fill_triangle(color_white(), 100, 250, 120, 310, 140, 250);
    fill_rectangle(color_white(), 70, 350, 80, 30);

    // Draw the O
    fill_ellipse(color_blue(), 170, 250, 80, 100);
    fill_ellipse(color_white(), 190, 270, 40, 60);

    // Draw the R
    fill_triangle(color_blue_violet(), 270, 250, 270, 350, 340, 350);
    fill_triangle(color_white(), 252, 250, 252, 350, 320, 350);
    fill_ellipse(color_blue_violet(), 252, 250, 80, 60);
    fill_ellipse(color_white(), 270, 270, 40, 20);
    fill_rectangle(color_white(), 252, 250, 20, 100);
    fill_rectangle(color_blue_violet(), 270, 250, 20, 100);

    // Draw the L
    fill_rectangle(color_purple(), 360, 250, 20, 100);
    fill_rectangle(color_purple(), 380, 330, 40, 20);

    // Draw the D
    fill_ellipse(color_magenta(), 420, 250, 100, 100);
    fill_ellipse(color_white(), 440, 270, 60, 60);
    fill_rectangle(color_white(), 420, 250, 30, 100);
    fill_rectangle(color_magenta(), 450, 250, 20, 101);

    // Draw the !
    fill_rectangle(color_pink(), 550, 250, 20, 60);
    fill_circle(color_pink(), 560, 340, 10);

    refresh_screen();
    delay(5000);
}