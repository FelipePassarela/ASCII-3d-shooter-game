#include "main_char.hpp"
#include "constants.hpp"
#include <cmath>

void MainChar::move(Direction direction)
{
    if (direction == Direction::LEFT)
    {
        angle += PI/20;
    } else if (direction == Direction::RIGHT)
    {
        angle -= PI/20;
    } else if (direction == Direction::UP)
    {
        x += (int) (speed * cosf(angle));
        y -= (int) (speed * sinf(angle));
    } else if (direction == Direction::DOWN)
    {
        x -= (int) (speed * cosf(angle));
        y += (int) (speed * sinf(angle));
    }

    if (angle > 2 * PI)
    {
        angle -= 2 * PI;
    } else if (angle < 0)
    {
        angle += 2 * PI;
    }    
}

void MainChar::moveBack(Direction direction)
{
    if (direction == Direction::UP)
    {
        x -= (int) (speed * cosf(angle));
        y += (int) (speed * sinf(angle));
    } else if (direction == Direction::DOWN)
    {
        x += (int) (speed * cosf(angle));
        y -= (int) (speed * sinf(angle));
    }
}