#pragma once

#include <cmath>
#include <string>

struct Shot // Represents a shot fired by the player.
{
    double x;
    double y;
    double angle;

    Shot(double x, double y, double angle) : x(x), y(y), angle(angle) {}

    void move(double deltaTime) // Moves the shot in the direction it was fired. 
    {
        x += cos(angle) * 40 * deltaTime;
        y -= sin(angle) * 40 * deltaTime;
    }
};