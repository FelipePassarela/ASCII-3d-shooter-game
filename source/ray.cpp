#include "ray.hpp"
#include <cmath>

void Ray::castRay(double playerX, double playerY, double playerA, double FOV, std::vector<std::string> map)
{
    angle = -playerA;

    double steps = 0.0f;
    int newX = static_cast<int>(playerX);
    int newY = static_cast<int>(playerY);
    int oldX =  newX;
    int oldY =  newY;

    points.clear();
    while (map[newY][newX] != '#')
    {
        steps += stepSize;
        
        newX = static_cast<int>(playerX + steps * cosf(angle));
        newY = static_cast<int>(playerY + steps * sinf(angle));

        if (newX < 0 || newX >= map[0].size() || newY < 0 || newY >= map.size())
        {
            break;
        }

        if (newX != oldX || newY != oldY)
        {
            points.push_back(std::make_pair(newX, newY));
        }

        oldX = newX;
        oldY = newY;
    }

    distance = steps * cosf(angle - FOV / 2);
}