#ifndef BOUNDEDSHAPE_H
#define BOUNDEDSHAPE_H

#include <SFML/Graphics.hpp>

class BoundedShape {
protected:
    sf::Shape *s;
public:
    BoundedShape();
    BoundedShape(sf::Vector2f s_size);
    BoundedShape(float x_size, float y_size);

    void set_position(float x_loc, float y_loc);
    void set_position(sf::Vector2f loc);
    void set_size(float x_size, float y_size);
    void set_size(sf::Vector2f s_size);
    void set_radius(float radius);

    sf::Vector2f get_size();
    float get_width();
    float get_height();
    float get_radius();

    sf::Vector2f get_center();
    sf::Vector2f get_top_left();
    sf::Vector2f get_top_right();
    sf::Vector2f get_top_center();
    sf::Vector2f get_bottom_left();
    sf::Vector2f get_bottom_right();
    float get_top();
    float get_bottom();
    float get_left();
    float get_right();
    float get_center_x();
    float get_center_y();
    sf::Shape* get_shape();
};

#endif // BOUNDEDSHAPE_H
