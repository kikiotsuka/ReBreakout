#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Brick.h"

class Wall {
private:
    std::vector<std::vector<Brick> > grid;
    sf::Color get_design(int i, int j, int design, sf::Color *clist);
public:
    Wall();
    std::vector<Brick> operator[](const int &index) const;
    int size();
    void set_dead(int i, int j);
    int num_alive();
    bool has_won();
    void draw(sf::RenderWindow &window);
};

#endif // WALL_H
