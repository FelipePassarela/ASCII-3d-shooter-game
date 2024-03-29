/**
 * @file AStar.hpp
 * @author Felipe Passarela (feliepassarela11@gmail.com)
 * @brief A* pathfinding algorithm header file.
 * @date 2024-02-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// TODO: Optimize the A* algorithm by using a priority queue for the open list and a hash set for the closed list.

#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <string>
#include <memory>

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
        std::shared_ptr<Node> parent;

        Node(int x, int y, double gCost, double hCost, std::shared_ptr<Node> parent) :
             x(x), y(y), gCost(gCost), hCost(hCost), fCost(gCost + hCost), parent(parent) {}

        bool operator==(const Node& other) const { return x == other.x && y == other.y; }
    }; // struct Node

    using NodePtr = std::shared_ptr<Node>;  // Shared pointer to a Node
    using NodeList = std::vector<NodePtr>;  // Vector of shared pointers to Nodes

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
         * Checks if a given node is present in a list of nodes.
         *
         * @param node The node to check.
         * @param list The list of nodes to search in.
         * @return True if the node is found in the list, false otherwise.
         */
        bool isNodeInList(const NodePtr node, const NodeList& list);

        /**
         * Reconstructs the path from the start node to the end node.
         * 
         * @param endNode The end node of the path.
         * @return A vector of pairs representing the coordinates of the nodes in the path.
         */
        std::vector<std::pair<int, int>> reconstructPath(NodePtr endNode);

        /**
         * @brief Finds the 8 neighboring nodes of a given node.
         * 
         * @param node The node for which to find neighbors.
         * @param mapWidth The width of the map.
         * @param mapHeight The height of the map.
         * @param map The map containing the nodes.
         * @return The list of neighboring nodes.
         */
        NodeList findNeighbours(const NodePtr node, int mapWidth, int mapHeight, const std::string & map);

        /**
         * @brief Evaluates a neighbor node in the A* algorithm.
         * 
         * This function calculates the cost and heuristic values for a neighbor node,
         * and updates its parent and total cost if necessary. It also adds the neighbor
         * node to the open list if it is not already in the closed list.
         * 
         * @param neighbour The neighbor node to evaluate.
         * @param currentNode The current node being evaluated.
         * @param endNode The end node of the path.
         * @param openList The list of nodes to be evaluated.
         * @param closedList The list of nodes that have already been evaluated.
         */
        void evaluateNeighbour(NodePtr neighbour, NodePtr currentNode, const NodePtr endNode,
                               NodeList& openList, const NodeList& closedList);
    } // namespace Utils

    /**
     * Finds a path from the starting position to the ending position on the given map.
     * 
     * @param startX The x-coordinate of the starting position.
     * @param startY The y-coordinate of the starting position.
     * @param endX The x-coordinate of the ending position.
     * @param endY The y-coordinate of the ending position.
     * @param mapWidth The width of the map.
     * @param mapHeight The height of the map.
     * @param map The map represented as a vector of strings.
     * @return A vector of pairs (x, y) representing the path from the starting position to the ending position.
     */
    std::vector<std::pair<int, int>> findPath(int startX, int startY, int endX, int endY, int mapWidth, int mapHeight, const std::string& map);
} // namespace AStar

#endif // ASTAR_HPP