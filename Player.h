#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    int lives;
    sf::CircleShape life;
public:
    Player();
    void lose_life();
    bool is_alive();
    int get_lives();

    void draw(sf::RenderWindow &window);
};

#endif // PLAYER_H
