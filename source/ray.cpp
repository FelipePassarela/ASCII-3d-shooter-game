#include "ray.hpp"
#include <cmath>

void Ray::castRay(double playerX, double playerY, double playerA, std::vector<std::wstring> map)
{
    // Source: https://lodev.org/cgtutor/raycasting.html

    // NOTE: This code is a slightly modified version of the one in the link above.
    // The modifications were made to make the algorithm more readable. There is no
    // performance loss or gain from these modifications.

    double rayDirX = cos(angle);
    double rayDirY = -sin(angle);

    int mapX = int(playerX);
    int mapY = int(playerY);

    // Calculate the distance to the next X or Y tile
    double deltaDistX = std::abs(1 / rayDirX);
    double deltaDistY = std::abs(1 / rayDirY);

    // Calculate the initial sideDist and step direction
    double sideDistX = std::abs((playerX - mapX) * deltaDistX);
    double sideDistY = std::abs((playerY - mapY) * deltaDistY);

    int stepX = (rayDirX < 0) ? -1 : 1;     // -1 for left, 1 for right
    int stepY = (rayDirY < 0) ? -1 : 1;     // -1 for up, 1 for down

    bool hit = false;
    int sideHit;        // 0 for horizontal, 1 for vertical
    while (!hit)        // TODO: Use (!hit && distance < maxDepth) when rendering the 3D scene
    {
        // Jump to the next map square, either in x-direction, or the y-direction
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            sideHit = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            sideHit = 1;
        }

        if (map[mapY][mapX] == '#')
        {
            if (sideHit == 0)   distance = (sideDistX - deltaDistX);
            else                distance = (sideDistY - deltaDistY);
            hit = true;
        }
        else
        {
            points.push_back(std::make_pair(mapX, mapY));
        }
    }
}