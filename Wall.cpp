#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Wall.h"
#include "Brick.h"
#include "Meta.h"

Wall::Wall() {
    sf::Color clist[5] = {
        sf::Color(219, 79, 60),
        sf::Color(231, 231, 93),
        sf::Color(69, 192, 120),
        sf::Color(69, 76, 192),
        sf::Color(225, 70, 184)
    };
    srand(time(NULL));
    int design = rand() % 3;
    for (int i = 0; i < ROWS; i++) {
        std::vector<Brick> tmpBrick;
        for (int j = 0; j < COLUMNS; j++) {
            sf::Vector2f pos((BRICK_BUFFER + BRICK_WIDTH) * j + BRICK_BUFFER / 2, BUFFER_ZONE + (BRICK_HEIGHT + BRICK_BUFFER) * i);
            sf::Vector2f s_size(BRICK_WIDTH, BRICK_HEIGHT);
            tmpBrick.push_back(Brick(pos, s_size, get_design(i, j, design, clist)));
        }
        grid.push_back(tmpBrick);
    }
}

sf::Color Wall::get_design(int i, int j, int design, sf::Color *clist) {
    switch(design) {
    case 0:
        return clist[i % 5];
    case 1:
        return clist[(int) ((i % 10) / 2)];
    case 2:
        return clist[(i + j) % 5];
    }
    return clist[0];
}

std::vector<Brick> Wall::operator[](const int &index) const { return grid[index]; }
int Wall::size() { return grid.size(); }

void Wall::set_dead(int i, int j) {
    grid[i][j].set_dead();
}

int Wall::num_alive() {
    int counter = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j].get_state() == BRICK_ALIVE) {
                counter++;
            }
        }
    }
    return counter;
}

bool Wall::has_won() {
    return num_alive() == 0;
}

void Wall::draw(sf::RenderWindow &window) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (grid[i][j].get_state() == BRICK_ALIVE) {
                grid[i][j].draw(window);
            }
        }
    }
}
