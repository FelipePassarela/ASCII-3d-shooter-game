#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <string>

/**
 * @namespace AStar
 * @brief The AStar namespace contains the functionality for the A* pathfinding algorithm.
 */
namespace AStar
{
    /**
     * @struct Node
     * @brief Represents a node in the A* algorithm.
     * 
     * The Node struct represents a node in the A* algorithm. It contains the x and y coordinates of the node, 
     * the gCost, hCost, and fCost of the node, and a pointer to the parent node.
     */
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

        bool operator==(const Node& other) const { return x == other.x && y == other.y; }
    }; // struct Node

    using NodeList = std::vector<Node>;

    /**
     * @namespace Utils
     * @brief The Utils namespace contains utility functions for the A* pathfinding algorithm.
     */
    namespace Utils
    {
        /**
         * Calculates the heuristic value between two points.
         * The heuristic value is based on the euclidean distance between the two points.
         *
         * @param startX The x-coordinate of the start point.
         * @param startY The y-coordinate of the start point.
         * @param endX The x-coordinate of the end point.
         * @param endY The y-coordinate of the end point.
         * @return The heuristic value between the two points.
         */
        double heuristic(int startX, int startY, int endX, int endY);

        /**
         * @brief Chooses the current node from the open list based on a specific criteria.
         * 
         * This function selects the current node from the open list based on a specific criteria.
         * It takes in an open list of nodes and returns a reference to the chosen node.
         * 
         * @param openList The list of nodes from which to choose the current node.
         * @return A reference to the chosen node.
         */
        Node& chooseCurrentNode(NodeList& openList);

        /**
         * Checks if a given node is present in a list of nodes.
         *
         * @param node The node to check.
         * @param list The list of nodes to search in.
         * @return True if the node is found in the list, false otherwise.
         */
        bool isNodeInList(const Node& node, const NodeList& list);

        /**
         * Reconstructs the path from the start node to the end node.
         * 
         * @param endNode The end node of the path.
         * @return A vector of pairs representing the coordinates of the nodes in the path.
         */
        std::vector<std::pair<int, int>> reconstructPath(Node& endNode);

        /**
         * Finds the 8 neighboring nodes of the given node.
         *
         * @param node The node for which to find neighbors.
         * @param map The map containing the nodes.
         * @return A list of neighboring nodes.
         */
        NodeList findNeighbours(const Node& node, const std::vector<std::string>& map);

        /**
         * Evaluates a neighbor node in the A* algorithm.
         * 
         * @param neighbour The neighbor node to evaluate.
         * @param currentNode The current node being evaluated.
         * @param endNode The end node of the path.
         * @param openList The list of open nodes.
         * @param closedList The list of closed nodes.
         */
        void evaluateNeighbour(Node& neighbour, Node& currentNode, const Node& endNode,
                               NodeList& openList, const NodeList& closedList);
    } // namespace Utils

    /**
     * Finds a path from the starting position to the ending position on the given map.
     * 
     * @param startX The x-coordinate of the starting position.
     * @param startY The y-coordinate of the starting position.
     * @param endX The x-coordinate of the ending position.
     * @param endY The y-coordinate of the ending position.
     * @param map The map represented as a vector of strings.
     * @return A vector of pairs (x, y) representing the path from the starting position to the ending position.
     */
    std::vector<std::pair<int, int>> findPath(int startX, int startY, int endX, int endY, const std::vector<std::string>& map);
} // namespace AStar

#endif // ASTAR_HPP