#include "splashkit.h"
#include "splashkit-arrays.h"

struct rock_data
{
    int speed;
    circle circle_properties;
};

struct game_data
{
    dynamic_array<rock_data> rocks = {};

    circle player_circle_properties;

    int player_lives = 3;
    int score;
};

void new_rock(game_data &game)
{
    rock_data rock;

    rock.circle_properties.radius = rnd(20, 200);
    rock.speed = rnd(1, 5);
    rock.circle_properties.center.x = rnd(0, screen_width());
    rock.circle_properties.center.y = -rock.circle_properties.radius;

    game.rocks.add(rock);
    game.score++;
}

void draw_game(const game_data &game)
{
    clear_screen(COLOR_WHITE);

    for (int i = 0; i < length(game.rocks); i++)
    {
        rock_data rock = game.rocks[i];

        fill_circle(COLOR_BROWN, rock.circle_properties);
        draw_circle(COLOR_BLACK, rock.circle_properties);
        draw_text(to_string(rock.circle_properties.radius, 0), COLOR_BLACK, rock.circle_properties.center.x, rock.circle_properties.center.y);
    }

    fill_circle(COLOR_LIGHT_BLUE, game.player_circle_properties);
    draw_circle(COLOR_BLACK, game.player_circle_properties);

    draw_text("Score: " + to_string(game.score), COLOR_BLACK, 0, 0);
    draw_text("Lives: " + to_string(game.player_lives), COLOR_BLACK, 0, 10);

    refresh_screen();
};

void game_tick(game_data &game)
{
    for (int i = 0; i < length(game.rocks); i++)
    {
        game.rocks[i].circle_properties.center.y += game.rocks[i].speed;

        rock_data rock = game.rocks[i];

        if (rock.circle_properties.center.y >= screen_height() + game.rocks[i].circle_properties.radius)
        {
            game.score += rock.circle_properties.radius;
            remove(game.rocks, i);
            i--;
        }
        
        if (circles_intersect(rock.circle_properties, game.player_circle_properties))
        {
            game.player_lives--;
            remove(game.rocks, i);
        }
    }

    if (rnd(1, 60) == 1)
    {
        new_rock(game);
    }

    if ((key_down(LEFT_KEY) or key_down(A_KEY)) and game.player_circle_properties.center.x > game.player_circle_properties.radius)
    {
        game.player_circle_properties.center.x -= 3;
    }

    else if ((key_down(RIGHT_KEY) or key_down(D_KEY)) and game.player_circle_properties.center.x < screen_width() - game.player_circle_properties.radius)
    {
        game.player_circle_properties.center.x += 3;
    }
}

int main()
{
    open_window("Rock Dodge", 800, 600);
    game_data game;
    game.score = 0;

    game.player_circle_properties.center.x = screen_width() / 2;
    game.player_circle_properties.center.y = screen_height();
    game.player_circle_properties.radius = 20;

    while (!quit_requested())
    {
        process_events();
        game_tick(game);
        draw_game(game);
        if (game.player_lives == 0)
        {
            return 0;
        }
        delay(1000 / 60);
    }
}
