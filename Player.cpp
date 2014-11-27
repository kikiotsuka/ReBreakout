#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player() {
    lives = 3;
    life.setRadius(5.0f);
    life.setOrigin(life.getRadius(), life.getRadius());
    life.setFillColor(sf::Color::Red);
    life.setOutlineColor(sf::Color::White);
    life.setOutlineThickness(2.0f);
}

void Player::lose_life() { lives--; }

bool Player::is_alive() { return lives > 0; }
int Player::get_lives() { return lives; }

void Player::draw(sf::RenderWindow &window) {
    for (int i = 0; i < lives; i++) {
        life.setPosition(i * 20 + 10, 20.0f);
        window.draw(life);
    }
}
