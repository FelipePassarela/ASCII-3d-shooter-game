/**
 * @file ray.cpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Ray class implementation file.
 * @version 1.0
 * @date 2024-02-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "ray.hpp"
#include <algorithm>

void Ray::castRay(double playerX, double playerY, int mapWidth, int mapHeight, const std::string& map, const Objective& objective)
{
    int newX = int(playerX);
    int newY = int(playerY);
    int oldX = newX;
    int oldY = newY;

    bool hit = false;

    while (!hit && distance < maxDepth)
    {
        distance += 0.1;

        newX = int(playerX + distance * cosf(angle));       // Formula: X = X0 + t * Dx. Source: https://en.wikipedia.org/wiki/Ray_casting. 
        newY = int(playerY - distance * sinf(angle));       // X0 is the initial position, t is the parameter (distance here), and Dx is 
                                                            // the direction vector.

        if (newX < 0 || newX >= mapWidth || newY < 0 || newY >= mapHeight)
        {
            hit = true;
            this->hitWall = true;
        } 
        else if (map[newY * mapWidth + newX] == '#')
        {
            hit = true;
            this->hitWall = true;
            verifyBoundary(newX, newY, playerX, playerY);
        }
        else if (newX == int(objective.getX()) && newY == int(objective.getY()))
        {
            hit = true;
            this->hitObjective = true;
            verifyBoundary(newX, newY, playerX, playerY);
        }
        else if (newX != oldX || newY != oldY)
        {
            points.push_back(std::make_pair(newX, newY));
        }

        oldX = newX;
        oldY = newY;
    }
}

void Ray::verifyBoundary(int mapX, int mapY, double playerX, double playerY)
{
    // Source: https://github.com/OneLoneCoder/CommandLineFPS

    std::vector<std::pair<double, double>> p;

    for (int tx = 0; tx < 2; tx++)
    {
        for (int ty = 0; ty < 2; ty++)
        {
            // Angle of corner to eye
            double vy = (double)mapY + ty - playerY;
            double vx = (double)mapX + tx - playerX;
            double d = sqrt(vx * vx + vy * vy);
            double dot = (cosf(angle) * vx / d) + (-sinf(angle) * vy / d);
            p.push_back(std::make_pair(d, dot));
        }
    }

    // Sort Pairs from closest to farthest
    sort(p.begin(), p.end(), [](const std::pair<double, double>& left, const std::pair<double, double>& right) {return left.first < right.first; });

    // First two/three are closest (we will never see all four)
    double bound = 0.01;    
    if (acos(p.at(0).second) < bound) hitBoundary = true;
    if (acos(p.at(1).second) < bound) hitBoundary = true;
    if (acos(p.at(2).second) < bound) hitBoundary = true;
}

void Ray::castRayDDA(double playerX, double playerY, std::vector<std::string> map)
{
    // Source: https://lodev.org/cgtutor/raycasting.html

    // NOTE: This code is a slightly modified version of the one in the link above.
    // The modifications were made to make the algorithm more readable. There is no
    // performance loss or gain from these modifications.

    // NOTE: Besides the perfomance gains, the DDA algorithm isn't appropriate for this
    // game because of the distortions in the walls that it causes while player is 
    // moving. The original castRay method is the best choice for this game.

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
    while (!hit)
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
            if (distance == 0)  distance = 0.1;
            hit = true;
        }
        else
        {
            points.push_back(std::make_pair(mapX, mapY));
        }
    }
}