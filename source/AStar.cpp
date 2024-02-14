/**
 * @file AStar.cpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief A* pathfinding algorithm implementation file.
 * @date 2024-02-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "AStar.hpp"
#include <algorithm>
#include <cmath>

using namespace AStar;
using namespace AStar::Utils;

std::vector<std::pair<int, int>> AStar::findPath(int startX, int startY, int endX, int endY, int mapWidth, int mapHeight, const std::string& map)
{
    NodeList openList;
    NodeList closedList;

    NodePtr startNode = std::make_shared<Node>(startX, startY, 0, heuristic(startX, startY, endX, endY), nullptr);
    NodePtr endNode = std::make_shared<Node>(endX, endY, 0, 0, nullptr);

    openList.push_back(startNode);

    while (!openList.empty())
    {
        NodePtr currentNode = chooseCurrentNode(openList);

        if (*currentNode == *endNode)
        {
            return reconstructPath(currentNode);
        }

        closedList.push_back(currentNode);
        openList.erase(std::remove(openList.begin(), openList.end(), currentNode), openList.end());

        auto neighbours = findNeighbours(currentNode, mapWidth, mapHeight, map);
        for (auto& neighbour : neighbours)
        {
            evaluateNeighbour(neighbour, currentNode, endNode, openList, closedList);
        }
    }

    return {};
}

/* <----------------------------------------------- Utils -----------------------------------------------> */

double AStar::Utils::heuristic(int startX, int startY, int endX, int endY)
{
    // Manhattan distance
    // return std::abs(endX - startX) + std::abs(endY - startY);

    // Euclidean distance
    return std::sqrt(std::pow(endX - startX, 2) + std::pow(endY - startY, 2));

    // Diagonal distance
    // return std::max(std::abs(endX - startX), std::abs(endY - startY));

    // Octile distance
    // int dx = std::abs(endX - startX);
    // int dy = std::abs(endY - startY);
    // return std::max(dx, dy) + (std::sqrt(2) - 1) * std::min(dx, dy);

    // Chebyshev distance
    // return std::max(std::abs(endX - startX), std::abs(endY - startY));
}

NodePtr AStar::Utils::chooseCurrentNode(AStar::NodeList& openList)
{
    NodePtr currentNode = openList[0];
    for (auto& node : openList)
    {
        if (node->fCost < currentNode->fCost || (node->fCost == currentNode->fCost && node->hCost < currentNode->hCost))
        {
            currentNode = node;
        }
    }
    return currentNode;
}

bool AStar::Utils::isNodeInList(const NodePtr node, const NodeList& list)
{
    for (auto n : list)
    {
        if (*n == *node) return true;
    }
    return false;
}

std::vector<std::pair<int, int>> AStar::Utils::reconstructPath(NodePtr endNode)
{
    std::vector<std::pair<int, int>> path;
    NodePtr currentNode = endNode;

    while (currentNode->parent != nullptr)
    {
        path.push_back(std::make_pair(currentNode->x, currentNode->y));
        currentNode = currentNode->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

NodeList AStar::Utils::findNeighbours(const NodePtr node, int mapWidth, int mapHeight, const std::string& map)
{
    NodeList neighbours;

    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (dx == 0 && dy == 0) continue;

            int x = node->x + dx;
            int y = node->y + dy;

            if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight)  continue;
            if (map[y * mapWidth + x] != ' ')                       continue;

            neighbours.push_back(std::make_shared<Node>(x, y, 0, 0, nullptr));
        }
    }

    return neighbours;
}

void AStar::Utils::evaluateNeighbour(NodePtr neighbour, NodePtr currentNode, const NodePtr endNode, NodeList& openList, const NodeList& closedList)
{
    if (isNodeInList(neighbour, closedList)) return;

    double gCost = currentNode->gCost + heuristic(currentNode->x, currentNode->y, neighbour->x, neighbour->y);
    bool gCostIsBest = false;

    if (!isNodeInList(neighbour, openList))
    {
        gCostIsBest = true;
        neighbour->hCost = heuristic(neighbour->x, neighbour->y, endNode->x, endNode->y);
        openList.push_back(neighbour);
    }
    else if (gCost < neighbour->gCost)
    {
        gCostIsBest = true;
    }

    if (gCostIsBest)
    {
        neighbour->parent = currentNode;
        neighbour->gCost = gCost;
        neighbour->fCost = neighbour->gCost + neighbour->hCost;
    }
}
