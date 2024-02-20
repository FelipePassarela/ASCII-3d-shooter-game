/**
 * @file ray.hpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Ray class header file.
 * @date 2024-02-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "objective.hpp"

/**
 * @class Ray
 * @brief Represents a ray in the game.
 * 
 * The Ray class encapsulates the functionality of a ray in the game. It is used to cast rays from the 
 * player's position and check for collisions with the game map.
 */
class Ray
{
private:
    double angle = 0.0f;
    double distance = 0.0f;
    double maxDepth = 16.0f;
    bool hitWall = false;
    bool hitObjective = false;
    bool hitBoundary = false;

public:
    Ray() {}

    Ray(double angle) : angle(angle) {}

    ~Ray() {}

    /* <------------------------ Getters ------------------------> */

    double getAngle() const { return angle; }

    double getDistance() const { return distance; }

    double getMaxDepth() const { return maxDepth; }

    bool getHitWall() const { return hitWall; }

    bool getHitObjective() const { return hitObjective; }

    bool getHitBoundary() const { return hitBoundary; }

    /* <------------------------ Setters ------------------------> */

    void setAngle(double newAngle) { angle = newAngle; }

    void setDistance(double newDistance) { distance = newDistance; }

    void setMaxDepth(double newMaxDepth) { maxDepth = newMaxDepth; }

    void setHitWall(bool newHitWall) { hitWall = newHitWall; }

    void setHitObjective(bool newHitObjective) { hitObjective = newHitObjective; }

    void setHitBoundary(bool newHitBoundary) { hitBoundary = newHitBoundary; }

    /* <------------------------ Methods ------------------------> */

    /**
     * Casts a ray from the player's position in a given direction and checks for collisions with the map.
     * 
     * @param playerX The x-coordinate of the player's position.
     * @param playerY The y-coordinate of the player's position.
     * @param mapWidth The width of the map.
     * @param mapHeight The height of the map.
     * @param map The map containing the game environment.
     * @param objective The objective of the game.
     */
    void castRay(double playerX, double playerY, int mapWidth, int mapHeight, const std::string& map, const Objective& objective);

    /**
     * This function is deprecated.
     * 
     * Casts a ray using the Digital Differential Analyzer (DDA) algorithm.
     * 
     * Besides the perfomance gains, the DDA algorithm isn't appropriate for this game because of the 
     * distortions in the walls that it causes while player is moving. The original castRay method is 
     * the best choice for this game.
     * 
     * @param playerX The X coordinate of the player's position.
     * @param playerY The Y coordinate of the player's position.
     * @param map The map containing the game world.
     */
    void castRayDDA(double playerX, double playerY, std::vector<std::string> map);

    /**
     * Verifies if the ray hits a boundary of a cell in the game map.
     * 
     * @param mapX The map cell's x-coordinate.
     * @param mapY The map cell's y-coordinate.
     * @param playerX The x-coordinate of the player's position.
     * @param playerY The y-coordinate of the player's position.
     */
    void verifyBoundary(int mapX, int mapY, double playerX, double playerY);

    /**
     * Fixes the fish-eye effect caused by the player's perspective.
     * The distance is adjusted based on the angle between the ray and the player's view angle.
     * 
     * @param playerA The player's view angle in radians.
     */
    void fixFishEyeEffect(double playerA) { distance *= cosf(angle - playerA); }
};

#endif  // RAY_HPP