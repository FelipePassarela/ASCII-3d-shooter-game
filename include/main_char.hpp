#include <iostream>
#include "position.hpp"

class MainChar
{
private:
    int health = 100;
    char tile = '>';
    Position position;
    
public:
    MainChar() {}

    MainChar(std::size_t x, std::size_t y) : position(x, y) {}

    ~MainChar() {}

    /* <------------------------ Getters ------------------------> */

    int getHealth() const 
    {
        return health;
    }

    char getTile() const 
    {
        return tile;
    }

    std::size_t getX() const 
    {
        return position.getX();
    }

    std::size_t getY() const 
    {
        return position.getY();
    }

    Direction getDirection() const 
    {
        return position.getDirection();
    }

    /* <------------------------ Setters ------------------------> */

    void setHealth(int newHealth) 
    {
        health = newHealth;
    }

    void setTile(char newTile) 
    {
        tile = newTile;
    }

    void setX(std::size_t newX) 
    {
        position.setX(newX);
    }

    void setY(std::size_t newY) 
    {
        position.setY(newY);
    }

    void setDirection(Direction newDirection) 
    {
        position.setDirection(newDirection);
    }

    /* <------------------------ Methods ------------------------> */

    void move(Direction direction) 
    {
        position.move(direction);
    }
};