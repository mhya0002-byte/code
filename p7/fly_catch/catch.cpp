#include "splashkit.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

struct game_data
{
    spider_data spider;
    fly_data fly;
};

struct spider_data
{
    double x;
    double y;
};

struct fly_data
{
    double x;
    double y;
};

spider_data new_spider()
{
    spider_data spider;

    spider.x = SCREEN_WIDTH/2;
    spider.y = SCREEN_HEIGHT/2;

    return spider;

}

fly_data new_fly()
{
    fly_data fly;

    fly.x = 100;
    fly.y = 100;

    return fly;

}

void draw_game(const game_data &game)
{
    clear_screen(COLOR_WHITE);
    
    fill_circle(COLOR_BLACK, game.spider.x, game.spider.y, 20);

    fill_circle(COLOR_GREEN, game.fly.x, game.fly.y, 15);

    refresh_screen();
}

int main()
{
    game_data game;
    game.spider = new_spider();
    game.fly = new_fly();

    open_window("Fly Catch", SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!quit_requested())
    {
        process_events();

        draw_game(game);

    }
}