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
    double speed;

    Shot(double x, double y, double angle, double speed) : x(x), y(y), angle(angle), speed(speed) {}

    // Moves the shot in the direction it was fired. 
    void move(double deltaTime) 
    {
        x += cos(angle) * speed * deltaTime;
        y -= sin(angle) * speed * deltaTime;
    }
};

#endif // SHOT_HPP