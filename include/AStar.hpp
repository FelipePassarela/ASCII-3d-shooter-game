#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <string>

namespace AStar
{
    struct Node
    {
        int x;
        int y;
        double gCost;
        double hCost;
        double fCost;
        Node* parent;

        Node(int x, int y, double gCost, double hCost, Node* parent) :
             x(x), y(y), gCost(gCost), hCost(hCost), fCost(gCost + hCost), parent(parent) {}
    }; // struct Node

    using NodeList = std::vector<Node>;

    namespace Utils
    {
        double heuristic(int startX, int startY, int endX, int endY);

        Node& chooseCurrentNode(NodeList& openList);

        bool isNodeInList(const Node& node, const NodeList& list);

        std::vector<std::pair<int, int>> reconstructPath(Node& endNode);

        NodeList findNeighbours(const Node& node, const std::vector<std::string>& map);

        void evaluateNeighbour(Node& neighbour, Node& currentNode, const Node& endNode,
                               NodeList& openList, const NodeList& closedList);
    } // namespace Utils

    std::vector<std::pair<int, int>> findPath(int startX, int startY, int endX, int endY, const std::vector<std::string>& map);
} // namespace AStar

#endif // ASTAR_HPP