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