#include "AStar.hpp"
#include <algorithm>
#include <cmath>

using namespace AStar;
using namespace AStar::Utils;

std::vector<std::pair<int, int>> AStar::findPath(int startX, int startY, int endX, int endY, const std::vector<std::string>& map)
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

        auto neighbours = findNeighbours(currentNode, map);
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
    return sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY));
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
    for (auto& n : list)
    {
        if (n->x == node->x && n->y == node->y)
        {
            return true;
        }
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

NodeList AStar::Utils::findNeighbours(const NodePtr node, const std::vector<std::string>& map)
{
    NodeList neighbours;

    int numRows = map.size();
    int numCols = map[0].size();

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0) continue;

            int x = node->x + i;
            int y = node->y + j;

            if (map[x][y] != ' ')                               continue;
            if (x < 0 || x >= numRows || y < 0 || y >= numCols) continue;

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
