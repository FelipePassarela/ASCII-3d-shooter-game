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
    double speed = 10.0f;
    double rotationSpeed = speed * 1.5;
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

    /**
     * @brief Casts rays to detect collisions with the game map.
     * 
     * This function takes a vector of strings representing the game map and casts rays
     * to detect collisions with walls or other objects in the map. It is used to determine
     * the visibility of the player in the game world.
     * 
     * @param[out] map The game map represented as a vector of wstrings.
     */
    void castRays(std::vector<std::wstring> map);
};

#endif