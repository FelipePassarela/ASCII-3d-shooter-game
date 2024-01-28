#include <iostream>

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Position
{
protected:
    std::size_t x = 1;
    std::size_t y = 1;
    Direction direction;

public:
    Position() {}

    Position(std::size_t x, std::size_t y) : x(x), y(y) {}

    ~Position() {}

    /* <------------------------ Getters ------------------------> */

    std::size_t getX() const 
    {
        return x;
    }

    std::size_t getY() const 
    {
        return y;
    }

    Direction getDirection() const 
    {
        return direction;
    }

    /* <------------------------ Setters ------------------------> */

    void setX(std::size_t newX) 
    {
        x = newX;
    }

    void setY(std::size_t newY) 
    {
        y = newY;
    }

    void setDirection(Direction newDirection) 
    {
        direction = newDirection;
    }

    /* <------------------------ Methods ------------------------> */

    void move(Direction direction);    
};