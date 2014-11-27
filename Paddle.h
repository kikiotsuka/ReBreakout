#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include "BoundedShape.h"

class Paddle : public BoundedShape {
private:
    float vel;
    bool direction[2];
    bool has_ball;
public:
    Paddle();
    void move_paddle();
    void launch_ball();
    void reset_ball();
    void set_direction(int dir);
    void release_direction(int dir);

    bool get_has_ball();
    bool* get_direction();

    void draw(sf::RenderWindow &window);
};

#endif // PADDLE_H
