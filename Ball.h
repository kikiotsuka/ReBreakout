#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "BoundedShape.h"

class Ball : public BoundedShape {
private:
    float angle; //in radians
    float velocity;
public:
    Ball(sf::Vector2f loc);
    sf::Vector2f calculate_offset();
    void move_ball();
    void reset(sf::Vector2f loc);
    void vertical_bounce(); //bounce on wall
    void horizontal_bounce(); //bounce on ceiling/paddle top or bottom
    void set_velocity(float velocity);
    void set_angle(float angle);

    bool is_alive();
    float get_velocity();
    float get_angle();
    sf::Vector2f get_previous_center_loc();
    void draw(sf::RenderWindow &window);
};

#endif // BALL_H
