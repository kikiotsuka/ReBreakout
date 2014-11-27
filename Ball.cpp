#include <SFML/Graphics.hpp>
#include <cmath>
#include "Ball.h"
#include "Meta.h"
#include <iostream>

Ball::Ball(sf::Vector2f loc) {
    s = new sf::CircleShape(10.0f);
    set_position(loc.x, loc.y);
    angle = 0.0f;
    velocity = 0.0f;
    s->setFillColor(sf::Color::White);
}

sf::Vector2f Ball::calculate_offset() {
    sf::Vector2f offset(velocity * cos(angle), velocity * sin(angle));
    if (angle < PI) offset.y = -offset.y;
    else offset.y = abs(offset.y);
    return offset;
}

void Ball::move_ball() {
    angle = fmod(angle, T_PI);
    sf::Vector2f offset = calculate_offset();
    s->move(offset);
    if (get_right() > S_WIDTH || get_left() < 0) {
        float known_line = get_right() > S_WIDTH ? S_WIDTH - get_radius() : get_radius();
        float y = recalculate_loc('y', known_line, get_previous_center_loc(), get_center());
        set_position(known_line - get_radius(), y - get_radius());
        vertical_bounce();
    } else if (get_top() < 0) {
        float known_line = get_radius();
        float x = recalculate_loc('x', known_line, get_previous_center_loc(), get_center());
        set_position(x - get_radius(), known_line - get_radius());
        horizontal_bounce();
    }
}

void Ball::reset(sf::Vector2f loc) {
    float radius = get_radius();
    loc.x -= radius;
    loc.y -= 2 * radius;
    set_position(loc);
    angle = 0.0f;
    velocity = 0.0f;
}

void Ball::vertical_bounce() {
    float x_component = velocity * cos(angle);
    float y_component = velocity * sin(angle);
    angle = atan2(y_component, -x_component);
}

void Ball::horizontal_bounce() {
    float x_component = velocity * cos(angle);
    float y_component = velocity * sin(angle);
    angle = atan2(-y_component, x_component);
}

void Ball::set_velocity(float velocity) { this->velocity = velocity; }
void Ball::set_angle(float angle) { this->angle = angle; }

bool Ball::is_alive() { return get_top() <= S_HEIGHT; }
float Ball::get_velocity() { return velocity; }
float Ball::get_angle() { return angle; }

//returns center
sf::Vector2f Ball::get_previous_center_loc() {
    sf::Vector2f offset = calculate_offset();
    return sf::Vector2f(get_center_x() - offset.x, get_center_y() - offset.y);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(*s);
}
