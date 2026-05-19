#include "splashkit.h"

template <typename T>
class dynamic_array
{
private:
    T *_data;
    int _size;
    int _capacity;

    void resize(int new_capacity)
    {
        if (new_capacity < 2)
        {
            new_capacity = 2;
        }

        T *new_data = (T *)malloc(new_capacity * sizeof(T));

        if (new_data == NULL)
        {
            throw "Memory allocation failed";
        }

        for (int i = 0; i < _size; i++)
        {
            new (&new_data[i]) T(std::move(_data[i]));
            _data[i].~T();
        }

        free(_data);

        _data = new_data;
        _capacity = new_capacity;
    }

public:
    dynamic_array()
    {
        _capacity = 2;
        _size = 0;

        _data = (T *)malloc(_capacity * sizeof(T));

        if (_data == NULL)
        {
            throw "Memory allocation failed";
        }
    }

    // Disable copying
    dynamic_array(const dynamic_array &) = delete;
    dynamic_array &operator=(const dynamic_array &) = delete;

    ~dynamic_array()
    {
        for (int i = 0; i < _size; i++)
        {
            _data[i].~T();
        }

        free(_data);
        _data = NULL;
    }

    void add(const T &value)
    {
        if (_size >= _capacity)
        {
            resize(_capacity * 2);
        }

        new (&_data[_size]) T(value);

        _size++;
    }

    void remove(int index)
    {
        if (_size == 0)
        {
            throw "Cannot remove from empty list";
        }

        if (index < 0 || index >= _size)
        {
            throw "Index out of bounds";
        }

        _data[index].~T();

        for (int i = index; i < _size - 1; i++)
        {
            new (&_data[i]) T(std::move(_data[i + 1]));
            _data[i + 1].~T();
        }

        _size--;

        if (_size < _capacity / 2)
        {
            resize(_capacity / 2);
        }
    }

    T &operator[](int index) const
    {
        if (index < 0 || index >= _size)
        {
            throw "Index out of bounds";
        }

        return _data[index];
    }

    int size() const
    {
        return _size;
    }

    int capacity() const
    {
        return _capacity;
    }
};

struct rock_data
{
    int speed;
    circle circle_properties;
};

struct game_data
{
    dynamic_array<rock_data> rocks;

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

    for (int i = 0; i < game.rocks.size(); i++)
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
    for (int i = 0; i < game.rocks.size(); i++)
    {
        game.rocks[i].circle_properties.center.y += game.rocks[i].speed;

        rock_data rock = game.rocks[i];

        if (rock.circle_properties.center.y >= screen_height() + game.rocks[i].circle_properties.radius)
        {
            game.score += rock.circle_properties.radius;
            game.rocks.remove(i);
            i--;
        }

        if (circles_intersect(rock.circle_properties, game.player_circle_properties))
        {
            game.player_lives--;
            game.rocks.remove(i);
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
