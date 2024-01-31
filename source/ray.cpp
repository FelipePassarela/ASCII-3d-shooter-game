#include "ray.hpp"
#include <cmath>

void Ray::castRays(double playerX, double playerY, double playerA, double FOV, std::vector<std::string> map)
{
    // TODO: Create a vector of rays, and then cast them all. This function should only cast one ray.
    
    angle = -playerA - FOV / 2.0;
    distance = 0.0f;
    points.clear();

    int newX = static_cast<int>(playerX);
    int newY = static_cast<int>(playerY);
    int oldX =  newX;
    int oldY =  newY;

    while (angle <= -playerA + FOV / 2.0)
    {
        while (true)
        {
            distance += stepDistance;

            newX = static_cast<int>(playerX + distance * cosf(angle));      // Formula: X = X0 + t * Dx. Source: https://en.wikipedia.org/wiki/Ray_casting. X0 is the
            newY = static_cast<int>(playerY + distance * sinf(angle));      // initial position, t is the parameter (distance here), and Dx is the direction vector.

            if ((newX < 0 || newX >= map[0].size() || newY < 0 || newY >= map.size()) ||
                (map[newY][newX] == '#'))
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

        angle += stepAngle;
        distance = 0.0f;
    }

    // distance *= cosf(playerA - angle); // Fish eye correction
}