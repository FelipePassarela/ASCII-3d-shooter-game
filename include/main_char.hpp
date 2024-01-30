#ifndef MAIN_CHAR_HPP
#define MAIN_CHAR_HPP

#include <iostream>
#include "ray.hpp"

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class MainChar
{
private:
    int health = 100;
    int x = 1;
    int y = 1; 
    char tile = '>';
    double angle = 0.0f;
    double FOV = 3.14159 / 4;
    double speed = 1.0f;
    Ray ray;

public:
    MainChar() {}

    MainChar(int x, int y) : x(x), y(y) {}

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

    double getAngle() const 
    {
        return angle;
    }

    double getFOV() const 
    {
        return FOV;
    }

    Ray getRay() const 
    {
        return ray;
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

    void setAngle(double newAngle) 
    {
        angle = newAngle;
    }

    void setFOV(double newFOV) 
    {
        FOV = newFOV;
    }

    /* <------------------------ Methods ------------------------> */

    void move(Direction direction);

    void moveBack(Direction direction);
};

#endif