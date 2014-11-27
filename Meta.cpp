#include <cmath>
#include "Meta.h"

extern const int S_WIDTH = 600;
extern const int S_HEIGHT = 800;

extern const int FPS = 60;

extern const int DIR_RIGHT = 0;
extern const int DIR_LEFT = 1;
extern const int DIR_UP = 2;
extern const int DIR_DOWN = 3;

extern const int ROWS = 10;
extern const int COLUMNS = 10;

extern const float BRICK_BUFFER = 1.0f;
extern const int BRICK_WIDTH = (S_WIDTH - (ROWS - 1) * BRICK_BUFFER) / ROWS;
extern const int BRICK_HEIGHT = 25;

extern const int BRICK_ALIVE = 0;
extern const int BRICK_DEAD = 1;

extern const float BUFFER_ZONE = 40;

extern const long double PI = atan(1) * 4.0;
extern const long double T_PI = PI * 2;

float to_rad(float deg) { return deg * PI / 180; }
float to_deg(float rad) { return rad * 180 / PI; }

float recalculate_loc(char mode, float known_line, sf::Vector2f prev_loc, sf::Vector2f curr_loc) {
    float m = slope(curr_loc, prev_loc);
    switch(mode) {
    case 'y':
        return m * (known_line - curr_loc.x) + curr_loc.y;
    case 'x':
        return (known_line - curr_loc.y) / m + curr_loc.x;
    }
    return 0.0f;
}

float slope(sf::Vector2f a, sf::Vector2f b) { return (b.y - a.y) / (b.x - a.x); }
float slope(float x1, float y1, float x2, float y2) { return slope(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2)); }
float dist(sf::Vector2f a, sf::Vector2f b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return dx * dx + dy * dy;
}
float dist(float x1, float y1, float x2, float y2) { return dist(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2)); }
