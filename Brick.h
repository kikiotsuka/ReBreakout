#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>
#include "BoundedShape.h"

class Brick : public BoundedShape {
private:
    int state;
public:
    Brick(sf::Vector2f pos, sf::Vector2f s_size, sf::Color c);
    void set_dead();
    int get_state();
    void draw(sf::RenderWindow &window);
};

#endif // BRICK_H
