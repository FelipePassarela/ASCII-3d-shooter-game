#include "ray.hpp"
#include <cmath>

void Ray::castRay(double playerX, double playerY, double FOV, std::vector<std::string> map)
{
    // TODO: Fix this: Causing a segfault.
    // int newX = playerX;
    // int newY = playerY;
    // int oldX =  newX;
    // int oldY =  newY;

    // points.clear();
    // while (map[newX][newY] != '#')
    // {
    //     distance += steps;
        
    //     newX = (int) (playerX + distance * cosf(angle));
    //     newY = (int) (playerY + distance * sinf(angle));

    //     if (newX != oldX || newY != oldY)
    //     {
    //         points.push_back(std::make_pair(newX, newY));
    //     }

    //     oldX = newX;
    //     oldY = newY;
    // }

    // distance *= cosf(angle - FOV / 2);
}