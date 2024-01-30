#include "player.hpp"
#include "constants.hpp"
#include <cmath>

void Player::move(Direction direction)
{
    if (direction == Direction::LEFT)           angle += PI / 20;
    else if (direction == Direction::RIGHT)     angle -= PI / 20;
    else if (direction == Direction::UP)
    {
        x += speed * cosf(angle);
        y -= speed * sinf(angle);
    } 
    else if (direction == Direction::DOWN)
    {
        x -= speed * cosf(angle);
        y += speed * sinf(angle);
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