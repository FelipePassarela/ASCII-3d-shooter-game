#include "player.hpp"
#include "constants.hpp"
#include <cmath>

void Player::move(Direction direction)
{
    if (direction == Direction::LEFT)           angle += PI / 20;
    else if (direction == Direction::RIGHT)     angle -= PI / 20;
    else if (direction == Direction::UP)
    {
        x = x + speed * cosf(angle);            // Formula: X = X0 + t * Dx. Source: https://en.wikipedia.org/wiki/Ray_casting
        y = y - speed * sinf(angle);            // X0 is the initial position, t is the parameter (time in this context), and
    }                                           // Dx is the direction vector.
    else if (direction == Direction::DOWN)
    {
        x = x - speed * cosf(angle);
        y = y + speed * sinf(angle);
    }

    if (angle > 2 * PI)         angle -= 2 * PI;
    else if (angle < 0)         angle += 2 * PI;
}

void Player::moveBack(Direction direction)
{
    if (direction == Direction::UP)
    {
        x -= speed * cosf(angle);
        y += speed * sinf(angle);
    } 
    else if (direction == Direction::DOWN)
    {
        x += speed * cosf(angle);
        y -= speed * sinf(angle);
    }
}