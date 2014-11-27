#ifndef META_H
#define META_H

#include <SFML/Graphics.hpp>

extern const int S_WIDTH;
extern const int S_HEIGHT;

extern const int FPS;

extern const int DIR_RIGHT;
extern const int DIR_LEFT;
extern const int DIR_UP;
extern const int DIR_DOWN;

extern const int ROWS;
extern const int COLUMNS;

extern const float BRICK_BUFFER;
extern const int BRICK_WIDTH;
extern const int BRICK_HEIGHT;

extern const int BRICK_ALIVE;
extern const int BRICK_DEAD;

extern const float BUFFER_ZONE;

extern const long double PI;
extern const long double T_PI; //two pi

float to_rad(float deg);
float to_deg(float rad);
float recalculate_loc(char mode, float known_line, sf::Vector2f prev_loc, sf::Vector2f curr_loc);
float slope(sf::Vector2f a, sf::Vector2f b);
float slope(float x1, float y1, float x2, float y2);
float dist(sf::Vector2f a, sf::Vector2f b);
float dist(float x1, float y1, float x2, float y2);

//return new bounce angle
float vert_bounce(float angle);
float horz_bounce(float angle);

#endif // META_H
