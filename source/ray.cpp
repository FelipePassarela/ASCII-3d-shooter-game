#include "ray.hpp"
#include <cmath>

void Ray::castRay(double playerX, double playerY, double FOV, std::vector<std::string> map)
{
    double x = playerX;
    double y = playerY;

    points.clear();
    while (map[static_cast<int>(y)][static_cast<int>(x)] != '#')
    {
        x += sinf(angle) * steps;
        y += cosf(angle) * steps;

        points.push_back(std::make_pair(x, y));
    }

    distance = sqrtf((x - playerX) * (x - playerX) + (y - playerY) * (y - playerY));
    // distance *= cosf(angle - FOV / 2);
}