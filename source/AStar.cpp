#include "AStar.hpp"
#include <algorithm>
#include <cmath>

using namespace AStar;
using namespace AStar::Utils;

std::vector<std::pair<int, int>> AStar::findPath(int startX, int startY, int endX, int endY, const std::vector<std::string>& map)
{
    NodeList openList;
    NodeList closedList;

    Node startNode(startX, startY, 0, heuristic(startX, startY, endX, endY), nullptr);
    Node endNode(endX, endY, 0, 0, nullptr);

    openList.push_back(startNode);

    while (!openList.empty())
    {
        Node currentNode = chooseCurrentNode(openList);

        if (currentNode.x == endNode.x && currentNode.y == endNode.y)
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

Node& AStar::Utils::chooseCurrentNode(AStar::NodeList& openList)
{
    Node& currentNode = openList.front();
    for (auto& node : openList)
    {
        if (node.fCost < currentNode.fCost || (node.fCost == currentNode.fCost && node.hCost < currentNode.hCost))
        {
            currentNode = node;
        }
    }
    return currentNode;
}

bool AStar::Utils::isNodeInList(const Node& node, const NodeList& list)
{
    for (auto& n : list)
    {
        if (n.x == node.x && n.y == node.y)
        {
            return true;
        }
    }
    return false;
}

std::vector<std::pair<int, int>> AStar::Utils::reconstructPath(Node& endNode)
{
    std::vector<std::pair<int, int>> path;
    Node* currentNode = &endNode;

    while (currentNode->parent != nullptr)
    {
        path.push_back(std::make_pair(currentNode->x, currentNode->y));
        currentNode = currentNode->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

NodeList AStar::Utils::findNeighbours(const Node& node, const std::vector<std::string>& map)
{
    NodeList neighbours;

    int numRows = map.size();
    int numCols = map[0].size();

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0) continue;

            int x = node.x + i;
            int y = node.y + j;

            if (map[x][y] != ' ')                               continue;
            if (x < 0 || x >= numRows || y < 0 || y >= numCols) continue;

            neighbours.push_back(Node(x, y, 0, 0, nullptr));
        }
    }

    return neighbours;
}

void AStar::Utils::evaluateNeighbour(Node& neighbour, Node& currentNode, const Node& endNode, NodeList& openList, const NodeList& closedList)
{
    if (isNodeInList(neighbour, closedList)) return;

    double gCost = currentNode.gCost + heuristic(currentNode.x, currentNode.y, neighbour.x, neighbour.y);
    bool gCostIsBest = false;

    if (!isNodeInList(neighbour, openList))
    {
        gCostIsBest = true;
        neighbour.hCost = heuristic(neighbour.x, neighbour.y, endNode.x, endNode.y);
        openList.push_back(neighbour);
    }
    else if (gCost < neighbour.gCost)
    {
        gCostIsBest = true;
    }

    if (gCostIsBest)
    {
        neighbour.parent = &currentNode;
        neighbour.gCost = gCost;
        neighbour.fCost = neighbour.gCost + neighbour.hCost;
    }
}

