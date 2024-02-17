/**
 * @file shot.hpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Shot struct header file.
 * @date 2024-02-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SHOT_HPP
#define SHOT_HPP

#include <cmath>

struct Shot // Represents a shot fired by the player.
{
    double x;
    double y;
    double angle;

    Shot(double x, double y, double angle) : x(x), y(y), angle(angle) {}

    // Moves the shot in the direction it was fired. 
    void move(double deltaTime) 
    {
        x += cos(angle) * 40 * deltaTime;
        y -= sin(angle) * 40 * deltaTime;
    }
};

#endif // SHOT_HPP