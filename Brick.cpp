#include <SFML/Graphics.hpp>
#include "Brick.h"
#include "Meta.h"

Brick::Brick(sf::Vector2f pos, sf::Vector2f s_size, sf::Color c) {
    s = new sf::RectangleShape;
    set_position(pos);
    set_size(s_size);
    s->setFillColor(c);
    s->setOutlineColor(sf::Color::Black);
    s->setOutlineThickness(-0.5);
    state = BRICK_ALIVE;
}

void Brick::set_dead() { state = BRICK_DEAD; }

int Brick::get_state() { return state; }

void Brick::draw(sf::RenderWindow &window) {
    window.draw(*s);
}
