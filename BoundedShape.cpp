#include <SFML/Graphics.hpp>
#include "BoundedShape.h"

//constructors
BoundedShape::BoundedShape() { }
BoundedShape::BoundedShape(sf::Vector2f s_size) { set_size(s_size); }
BoundedShape::BoundedShape(float x_size, float y_size) { set_size(x_size, y_size); }

//setters
void BoundedShape::set_position(float x_loc, float y_loc) { s->setPosition(x_loc, y_loc); }
void BoundedShape::set_position(sf::Vector2f loc) { set_position(loc.x, loc.y); }
void BoundedShape::set_size(float x_size, float y_size) { set_size(sf::Vector2f(x_size, y_size)); }
void BoundedShape::set_size(sf::Vector2f s_size) {
    if (dynamic_cast<sf::RectangleShape *>(s)) {
        static_cast<sf::RectangleShape *>(s)->setSize(s_size);
    } else {
        set_radius(s_size.x);
    }
}
void BoundedShape::set_radius(float radius) {
    static_cast<sf::CircleShape *>(s)->setRadius(radius);
}

//getters - dimension
sf::Vector2f BoundedShape::get_size() {
    if (dynamic_cast<sf::RectangleShape *>(s)) {
        return static_cast<sf::RectangleShape *>(s)->getSize();
    }
    return sf::Vector2f(get_radius() * 2, get_radius() * 2);
}
float BoundedShape::get_width() { return get_size().x; }
float BoundedShape::get_height() { return get_size().y; }
float BoundedShape::get_radius() {
    return static_cast<sf::CircleShape *>(s)->getRadius();
}
//getters - position
sf::Vector2f BoundedShape::get_center() { return sf::Vector2f(get_center_x(), get_center_y()); }
sf::Vector2f BoundedShape::get_top_left() { return s->getPosition(); }
sf::Vector2f BoundedShape::get_top_right() { return sf::Vector2f(get_right(), get_top()); }
sf::Vector2f BoundedShape::get_top_center() { return sf::Vector2f(get_center_x(), get_top()); }
sf::Vector2f BoundedShape::get_bottom_left() { return sf::Vector2f(get_left(), get_bottom()); }
sf::Vector2f BoundedShape::get_bottom_right() { return sf::Vector2f(get_right(), get_bottom()); }
float BoundedShape::get_top() { return s->getPosition().y; }
float BoundedShape::get_bottom() { return s->getPosition().y + get_height(); }
float BoundedShape::get_left() { return s->getPosition().x; }
float BoundedShape::get_right() { return s->getPosition().x + get_width(); }
float BoundedShape::get_center_x() {
    if (dynamic_cast<sf::CircleShape *>(s)) {
        return get_left() + get_radius();
    }
    return get_left() + get_width() / 2;
}
float BoundedShape::get_center_y() {
    if (dynamic_cast<sf::CircleShape *>(s)) {
        return get_top() + get_radius();
    }
    return get_top() + get_height() / 2;
}
sf::Shape* BoundedShape::get_shape() { return s; }
