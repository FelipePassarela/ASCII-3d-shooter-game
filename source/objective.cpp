/**
 * @file objective.cpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Objective class implementation file.
 * @date 2024-02-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "objective.hpp"

std::mt19937 gen(std::random_device{}());

void Objective::randomizePosition(int mapWidth, int mapHeight, const std::string& map)
{
    bool isAtWall = true;
    std::uniform_int_distribution<> disX(1, mapWidth - 2);
    std::uniform_int_distribution<> disY(1, mapHeight - 2);
    
    while (isAtWall)
    {
        x = disX(gen);
        y = disY(gen);

        if (map[int(y) * mapWidth + int(x)] == ' ')
        {
            isAtWall = false;
        }
    }        
}

void Objective::randomizeWallTile(wchar_t& wallTile, double rayDistance)
{
    wchar_t noiseChar = '\t';
    std::uniform_int_distribution<> dis(0x1200, 0x137F); // Unicode range for ethiopic scripts
    std::uniform_int_distribution<> dis2(1, int(rayDistance * rayDistance * rayDistance) + 10); 

    int random = dis2(gen);

    if (random == 1)    wallTile = noiseChar;
    else                wallTile = dis(gen); 
}