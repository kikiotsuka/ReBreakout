#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <cmath>
#include "Meta.h"
#include "Player.h"
#include "Paddle.h"
#include "Wall.h"
#include "Ball.h"
#include <iostream>

//handle user input
void handle_input(sf::RenderWindow &window, Paddle &paddle, Ball &ball, Wall &wall, Player &player, sf::Clock &clock, bool &started, bool finished);
//handles collision detection
void check_collisions(Paddle &paddle, Ball &ball, Wall &wall);
//updates position
int recalc_position(BoundedShape rect, Ball &ball);
//launch ball with varying speed/angle
void set_ball_path(Paddle &paddle, Ball &ball);

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(S_WIDTH, S_HEIGHT), "Breakout - by Mitsuru Otsuka", sf::Style::Default, settings);

    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(FPS);

    Player player;
    Paddle paddle;
    Ball ball(paddle.get_top_center());
    Wall wall;
    sf::Clock clock;
    bool started = false;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error: Could not load font" << "\n";
        return 1;
    }
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Use left and right arrows to move the paddle.\nUse spacebar to fire ball, and Q to quit.\nPress any key to start!");
    instructions.setCharacterSize(25);
    sf::FloatRect ftmp = instructions.getGlobalBounds();
    instructions.setOrigin(ftmp.width / 2, ftmp.height / 2);
    instructions.setPosition(S_WIDTH / 2, S_HEIGHT / 2);

    sf::Text game_over;
    game_over.setFont(font);
    game_over.setString("");
    game_over.setCharacterSize(25);

    sf::Text win;
    win.setFont(font);
    win.setString("Congratulations! You beat the game!\nPress any key to restart");
    win.setCharacterSize(25);
    ftmp = win.getGlobalBounds();
    win.setOrigin(ftmp.width / 2, ftmp.height / 2);
    win.setPosition(S_WIDTH / 2, S_HEIGHT / 2);


    //initialize random seed
    srand(time(NULL));

    while (window.isOpen()) {
        handle_input(window, paddle, ball, wall, player, clock, started, wall.has_won() || !player.is_alive());
        if (player.is_alive() && !wall.has_won()) {
            if (started && paddle.get_has_ball() && clock.getElapsedTime().asMilliseconds() > 8001) {
                paddle.launch_ball();
            }

            paddle.move_paddle();
            if (paddle.get_has_ball()) {
                ball.reset(paddle.get_top_center());
            } else {
                if (ball.get_velocity() == 0.0f || ball.get_angle() == 0.0f) {
                    set_ball_path(paddle, ball);
                }
                ball.move_ball();
            }

            if (!ball.is_alive()) {
                player.lose_life();
                if (player.is_alive()) {
                    ball.reset(paddle.get_top_center());
                    paddle.reset_ball();
                }
                clock.restart();
            }

            check_collisions(paddle, ball, wall);

            if (!player.is_alive()) {
                std::stringstream ss;
                ss << ROWS * COLUMNS - wall.num_alive();
                game_over.setString("Game Over\nYour Score: " + ss.str() + "\nPress any key to restart");
                sf::FloatRect ftmp = game_over.getGlobalBounds();
                game_over.setOrigin(ftmp.width / 2, ftmp.height / 2);
                game_over.setPosition(S_WIDTH / 2, S_HEIGHT / 2);
            }
        }

        window.clear(sf::Color::Black);
        wall.draw(window);
        paddle.draw(window);
        ball.draw(window);
        player.draw(window);
        if (!started) {
            window.draw(instructions);
        }
        if (!player.is_alive()) {
            window.draw(game_over);
        }
        if (wall.has_won()) {
            window.draw(win);
        }

        window.display();
    }
    return 0;
}

void handle_input(sf::RenderWindow &window, Paddle &paddle, Ball &ball, Wall &wall, Player &player, sf::Clock &clock, bool &started, bool finished) {
    sf::Event e;
    while (window.pollEvent(e)) {
        switch(e.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Q) {
                window.close();
            }
            if (!started) {
                started = true;
                clock.restart();
            } else if (finished) {
                started = false;
                paddle = Paddle();
                ball.reset(paddle.get_top_center());
                wall = Wall();
                player = Player();
                clock.restart();
                break;
            }
            if (e.key.code == sf::Keyboard::Left) {
                paddle.set_direction(DIR_LEFT);
            } else if (e.key.code == sf::Keyboard::Right) {
                paddle.set_direction(DIR_RIGHT);
            } else if (e.key.code == sf::Keyboard::Space) {
                paddle.launch_ball();
            }
            break;
        case sf::Event::KeyReleased:
            if (e.key.code == sf::Keyboard::Left) {
                paddle.release_direction(DIR_LEFT);
            } else if (e.key.code == sf::Keyboard::Right) {
                paddle.release_direction(DIR_RIGHT);
            }
            break;
        }
    }
}

void check_collisions(Paddle &paddle, Ball &ball, Wall &wall) {
    if (paddle.get_shape()->getGlobalBounds().intersects(ball.get_shape()->getGlobalBounds())) {
        int loc = recalc_position(paddle, ball);
        if (loc == DIR_UP) {
            bool *direction = paddle.get_direction();
            float angle = ball.get_angle();
            float x_comp, y_comp;
            x_comp = cos(angle);
            y_comp = sin(angle);
            float deviation = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
            if (direction[DIR_RIGHT] ^ direction[DIR_LEFT]) {
                if (direction[DIR_RIGHT]) {
                    x_comp += deviation;
                } else {
                    x_comp -= deviation;
                }
            }
            angle = atan2(y_comp, x_comp);
            //make sure angle is not too shallow
            if (angle < to_rad(15)) {
                angle = to_rad(25);
            } else if (angle > to_rad(165)) {
                angle = to_rad(155);
            }
            ball.set_angle(angle);
            /*
            //angle reduction/increase
            if (abs(dx) < paddle.get_width() * 0.15) { //hit center
                ball.vertical_bounce();
            } else if (abs(dx) < paddle.get_width() * 0.85f) {

            } else { //edge

            }
            if (angle > to_rad(160)) {
                angle = to_rad(160);
            } else if (angle < to_rad(20)) {
                angle = angle = to_rad(20);
            }
            */
        }
    }
    std::vector<std::pair<Brick, sf::Vector2i> > candidates;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            Brick b = wall[i][j];
            if (b.get_state() == BRICK_ALIVE && b.get_shape()->getGlobalBounds().intersects(ball.get_shape()->getGlobalBounds())) {
                candidates.push_back(std::pair<Brick, sf::Vector2i>(b, sf::Vector2i(i, j)));
            }
        }
    }
    if (candidates.size() > 0) {
        float min_dist = dist(ball.get_previous_center_loc(), candidates[0].first.get_center());
        std::pair<Brick, sf::Vector2f> collided = candidates[0];
        for (int i = 1; i < candidates.size(); i++) {
            float compare_dist = dist(ball.get_previous_center_loc(), candidates[i].first.get_center());
            if (compare_dist < min_dist) {
                min_dist = compare_dist;
                collided = candidates[i];
            }
        }
        recalc_position(collided.first, ball);
        wall.set_dead(collided.second.x, collided.second.y);
    }
}

int recalc_position(BoundedShape rect, Ball &ball) {
    float r = ball.get_radius();
    float lt, rt, up, dn;
    lt = rect.get_left() - r;
    rt = rect.get_right() + r;
    up = rect.get_top() - r;
    dn = rect.get_bottom() + r;
    sf::Vector2f prev = ball.get_previous_center_loc();
    sf::Vector2f line_intersections[4] = {
        sf::Vector2f(lt, recalculate_loc('y', lt, prev, ball.get_center())),
        sf::Vector2f(rt, recalculate_loc('y', rt, prev, ball.get_center())),
        sf::Vector2f(recalculate_loc('x', up, prev, ball.get_center()), up),
        sf::Vector2f(recalculate_loc('x', dn, prev, ball.get_center()), dn)
    };
    std::vector<std::pair<sf::Vector2f, char> > candidates;
    sf::RectangleShape compare_rect(sf::Vector2f(rect.get_width() + 2 * r + 2, rect.get_height() + 2 * r + 2));
    compare_rect.setPosition(lt - 1, up - 1);
    for(int i = 0; i < 4; i++) {
        if (compare_rect.getGlobalBounds().contains(line_intersections[i])) {
            candidates.push_back(std::pair<sf::Vector2f, char>(line_intersections[i], i <= 1 ? 'y' : 'x'));
        }
    }
    float min_dist = dist(prev, candidates[0].first);
    sf::Vector2f transposed_loc = candidates[0].first;
    char bounce_direction = candidates[0].second;
    for (int i = 1; i < candidates.size(); i++) {
        float compare_dist = dist(prev, candidates[i].first);
        if (compare_dist < min_dist) {
            min_dist = compare_dist;
            transposed_loc = candidates[i].first;
            bounce_direction = candidates[i].second;
        }
    }
    ball.set_position(transposed_loc.x - r, transposed_loc.y - r);
    if (bounce_direction == 'y') {
        ball.vertical_bounce();
        if (transposed_loc.x < rect.get_left())
            return DIR_LEFT;
        return DIR_RIGHT;
    } else {
        ball.horizontal_bounce();
        if (transposed_loc.y < rect.get_top())
            return DIR_UP;
        return DIR_DOWN;
    }
}

void set_ball_path(Paddle &paddle, Ball &ball) {
    int min_angle = 30;
    int max_angle = 70;
    float angle = min_angle + rand() % (max_angle - min_angle + 1);
    float vel = 7 + rand() % (int) (9 - 7 + 1);
    bool *direction = paddle.get_direction();
    if (direction[DIR_LEFT] == direction[DIR_RIGHT]) {
        angle = rand() % 2 == 0 ? angle : 180 - angle;
    } else if (direction[DIR_LEFT]) {
        angle = 180 - angle;
    }
    ball.set_velocity(vel);
    ball.set_angle(to_rad(angle));
}
