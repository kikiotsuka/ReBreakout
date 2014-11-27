#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Meta.h"

Paddle::Paddle() {
    s = new sf::RectangleShape;
    //float width = S_WIDTH / COLUMNS * 1.25f;
    //float height = S_HEIGHT / FILL_PORTION / ROWS * 0.5f;
    float width = 75.0f;
    float height = 12.5f;
    float x = S_WIDTH / 2 - width / 2;
    float y = S_HEIGHT - 3.5 * height;
    set_size(width, height);
    set_position(x, y);
    s->setFillColor(sf::Color::White);
    vel = 4.0f;
    direction[DIR_RIGHT] = false;
    direction[DIR_LEFT] = false;
    has_ball = true;
}

void Paddle::move_paddle() {
    if (direction[DIR_RIGHT]) {
        s->move(vel, 0);
    }
    if (direction[DIR_LEFT]) {
        s->move(-vel, 0);
    }
    if (get_right() > S_WIDTH) {
        set_position(S_WIDTH - get_width(), get_top());
    } else if (get_left() < 0) {
        set_position(0, get_top());
    }
}

void Paddle::launch_ball() {
    has_ball = false;
}
void Paddle::reset_ball() { has_ball = true; }

void Paddle::set_direction(int dir) { direction[dir] = true; }
void Paddle::release_direction(int dir) { direction[dir] = false; }

bool Paddle::get_has_ball() { return has_ball; }
bool* Paddle::get_direction() { return direction; }

void Paddle::draw(sf::RenderWindow &window) {
    window.draw(*s);
}
