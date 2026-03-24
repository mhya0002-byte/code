#include "splashkit.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

struct entity
{
    point_2d pos;
    double radius;
    color clr;
};

struct spider_data
{
    entity ent;
};

struct fly_data
{
    entity ent;
};

struct game_data
{
    spider_data spider;
    fly_data fly;
};

spider_data new_spider()
{
    spider_data spider;

    spider = {{{SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, 20, COLOR_BLACK}};

    return spider;
}

fly_data new_fly()
{
    fly_data fly;

    fly = {{{100, 100}, 15, COLOR_GREEN}};


    return fly;
}

void draw_entity(const entity &ent)
{
    fill_circle(ent.clr, ent.pos.x, ent.pos.y, ent.radius);
}

void draw_game(const game_data &game)
{
    clear_screen(COLOR_WHITE);

    draw_entity(game.spider.ent);
    draw_entity(game.fly.ent);

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