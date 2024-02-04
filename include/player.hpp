/**
 * @file player.hpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Player class header file.
 * @version 1.0
 * @date 2024-02-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include "ray.hpp"
#include "constants.hpp"

/**
 * @brief Enumerates the possible directions for the player.
 */
enum class Direction
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

/**
 * @class Player
 * @brief Represents the player in the game.
 * 
 * The Player class encapsulates the functionality of the player in the game. It is responsible for 
 * handling the player's movement, health, and field of view (FOV).
 */
class Player
{
private:
    int health = 100;
    double x = 1;
    double y = 1;
    char tile = '>';
    double angle = 0.0f;
    double initialFOV = PI / 3.5;
    double FOV = initialFOV;
    double speed = 5.0f;
    double rotationSpeed = speed * 0.75f;
    std::vector<Ray> rays;

    /**
     * @brief Fix player's floating point imprecision
     * 
     * This function is necessary to solve a bug when the player starts in (1, 1). The 
     * floating point imprecision allows the player to move through walls in certains 
     * angles. This function fixes that by rounding the player's position to the 
     * nearest 6th decimal place.
     */
    void fixFloatingPointImprecision();

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

    double getInitialFOV() const
    {
        return initialFOV;
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

    /**
     * Moves the player in the specified direction.
     * 
     * @param direction The direction in which the player should move.
     * @param deltaTime The time elapsed since the last movement.
     */
    void move(Direction direction, double deltaTime);

    /**
     * Moves the player backwards in the specified direction.
     * 
     * @param direction The direction in which the player should move.
     * @param deltaTime The time elapsed since the last frame.
     */
    void moveBack(Direction direction, double deltaTime);

    /**
     * @brief Updates the player's tile based on its angle.
     */
    void updateTile();

    /**
     * @brief Increases the field of view (FOV) of the player.
     * 
     * @param deltaTime The time elapsed since the last frame.
     */
    void increaseFOV(double deltaTime);

    /**
     * @brief Adds a ray to the player's list of rays.
     * 
     * @param ray The ray to be added.
     */
    void addRay(Ray ray)
    {
        rays.push_back(ray);
    }

    /**
     * @brief Clears the player's list of rays.
     */
    void clearRays()
    {
        rays.clear();
    }
};

#endif  // PLAYER_HPP