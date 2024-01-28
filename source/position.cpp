#include "position.hpp"

void Position::move(Direction direction)
{
    switch (direction)
    {
    case Direction::UP:
        y--;
        break;
    case Direction::DOWN:
        y++;
        break;
    case Direction::LEFT:
        x--;
        break;
    case Direction::RIGHT:
        x++;
        break;
    }

    this->direction = direction;
}