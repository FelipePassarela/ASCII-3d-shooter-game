/**
 * @file player.hpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Player class header file.
 * @date 2024-02-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include "ray.hpp"
#include "shot.hpp"
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
    double angle = 0.0f;        // The angle of the player's view in radians.
    double initialFOV = PI / 3.5;
    double FOV = initialFOV;
    double speed = 4.0f;
    double rotationSpeed = 10.0f;
    std::vector<Shot> shots;    // The shots fired by the player.   

    /**
     * @brief Fix player's position floating point imprecision
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

    std::vector<Shot> getShots() const
    {
        return shots;
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
     * Rotates the player in the specified direction.
     * 
     * @param direction The direction to rotate the player.
     * @param deltaTime The time elapsed since the last frame.
     */
    void rotate(Direction direction, double deltaTime);

    /**
     * @brief Shoots a projectile.
     * 
     * This function is responsible for shooting a projectile from the player's position.
     * The function shoots according to the rate of fire.
     */
    void shoot();

    /**
     * @brief Updates the shots fired by the player.
     * 
     * This function updates the positions of the shots fired by the player based on the current game map,
     * the width of the map, and the time elapsed since the last update.
     * 
     * @param map The game map represented as a string.
     * @param mapWidth The width of the game map.
     * @param deltaTime The time elapsed since the last update.
     */
    void updateShots(const std::string& map, int mapWidth, double deltaTime);

    /**
     * Checks if the player is at the specified position.
     * 
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @return True if the player is at the specified position, false otherwise.
     */
    bool isAtPosition(int x, int y) const
    {
        return (int)this->x == x && (int)this->y == y;
    }

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
};

#endif  // PLAYER_HPP