#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include "ray.hpp"

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player
{
private:
    int health = 100;
    double x = 1;
    double y = 1;
    char tile = '>';
    double angle = 0.0f;
    double FOV = 3.14159 / 4;
    double speed = 1.0f;
    Ray ray;

public:
    Player() {}

    Player(double x, double y) : x(x), y(y) {}

    ~Player() {}

    /* <------------------------ Getters ------------------------> */

    int getHealth() const
    {
        return health;
    }

    char getTile() const
    {
        return tile;
    }

    double getX() const
    {
        return x;
    }

    double getY() const
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

    Ray& getRay()
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

    void setX(double newX)
    {
        x = newX;
    }

    void setY(double newY)
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

    void updateTile();
};

#endif