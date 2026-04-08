#include <splashkit.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int spider_radius = 25;
int spider_speed = 3;

int fly_radius = 3;

// Set the spider in the center of the screen
int spider_x = SCREEN_WIDTH / 2;
int spider_y = SCREEN_HEIGHT / 2;

int main()
{

    int fly_x = rnd(800), fly_y = rnd(600);
    bool fly_appeared = false;
    long time_to_appear = 1000 + rnd(2000);

    open_window("Fly Catch", SCREEN_WIDTH, SCREEN_HEIGHT);

    create_timer("game_timer");
    start_timer("game_timer");

    while (!quit_requested())
    {
        if (key_down(RIGHT_KEY) && spider_x + spider_radius < SCREEN_WIDTH)
        {
            spider_x += spider_speed;
        }

        if (key_down(LEFT_KEY) && spider_x - spider_radius > 0)
        {
            spider_x -= spider_speed;
        }

        if (!fly_appeared && timer_ticks("game_timer") > time_to_appear)
        {
            fly_appeared = true;

            fly_x = rnd(SCREEN_WIDTH);
            fly_y = rnd(SCREEN_HEIGHT);
        }

        clear_screen(color_white());
        fill_circle(color_black(), spider_x, spider_y, spider_radius);

        if (fly_appeared)
        {
            fill_circle(color_dark_green(), fly_x, fly_y, fly_radius);
        }

        refresh_screen(60);
        process_events();
    }
}