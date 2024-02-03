#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include "ray.hpp"
#include "constants.hpp"

enum class Direction
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class Player
{
private:
    int health = 100;
    double x = 1;
    double y = 1;
    char tile = '>';
    double angle = 0.0f;
    double FOV = PI / 4;
    double speed = 5.0f;
    double rotationSpeed = speed * 2.0f;
    std::vector<Ray> rays;

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

    std::vector<Ray> getRays() const
    {
        return rays;
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

    void move(Direction direction, double deltaTime);

    void moveBack(Direction direction, double deltaTime);

    void updateTile();

    void increaseFOV(double deltaTime);

    void addRay(Ray ray)
    {
        rays.push_back(ray);
    }

    void clearRays()
    {
        rays.clear();
    }
};

#endif