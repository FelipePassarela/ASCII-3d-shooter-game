#include "ray.hpp"
#include <cmath>

void Ray::castRay(double playerX, double playerY, double playerA, std::vector<std::string> map)
{
    int newX = static_cast<int>(playerX);
    int newY = static_cast<int>(playerY);
    int oldX = newX;
    int oldY = newY;

    bool hit = false;
    while (!hit)
    {
        distance += 0.1;

        newX = static_cast<int>(playerX + distance * cosf(angle));      // Formula: X = X0 + t * Dx. Source: https://en.wikipedia.org/wiki/Ray_casting. 
        newY = static_cast<int>(playerY - distance * sinf(angle));      // X0 is the initial position, t is the parameter (distance here), and Dx is 
                                                                        // the direction vector.

        if ((newX < 0 || newX >= map[0].size() || newY < 0 || newY >= map.size()) ||
            (map[newY][newX] == '#'))
        {
            hit = true;
        } 
        else if (newX != oldX || newY != oldY)
        {
            points.push_back(std::make_pair(newX, newY));
        }

        oldX = newX;
        oldY = newY;
    }

    distance = sqrtf(powf(playerX - newX, 2) + powf(playerY - newY, 2));
    distance *= cosf(angle - playerA);    // Corrects the fish-eye effect. Source: https://lodev.org/cgtutor/raycasting.html
}