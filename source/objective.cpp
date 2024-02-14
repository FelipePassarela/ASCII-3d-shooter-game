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

void Objective::randomizePosition(int mapWidth, int mapHeight, const std::string& map)
{
    bool isAtWall = true;
    while (isAtWall)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> disX(1, mapWidth - 2);
        std::uniform_int_distribution<> disY(1, mapHeight - 2);
        
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
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0x0530, 0x058F); // Unicode range for Armenian characters
    std::uniform_int_distribution<> dis2(1, int(rayDistance) * 40 + 10); 

    int random = dis2(gen);

    if (random == 1)    wallTile = noiseChar;
    else                wallTile = dis(gen); 
}