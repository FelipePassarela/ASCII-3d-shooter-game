#include <iostream>

class MainChar
{
private:
    int health = 100;
    char tile = '>';
    std::size_t x = 1;
    std::size_t y = 1;
public:
    MainChar() {}

    MainChar(std::size_t x, std::size_t y) : x(x), y(y) {}

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
        return x;
    }

    std::size_t getY() const 
    {
        return y;
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
        x = newX;
    }

    void setY(std::size_t newY) 
    {
        y = newY;
    }
};