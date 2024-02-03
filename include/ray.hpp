#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include <vector>
#include <cmath>

class Ray
{
private:
    double angle = 0.0f;
    double distance = 0.0f;
    double maxDepth = 16.0f;
    bool hitBoundary = false;
    std::vector<std::pair<int, int>> points;

public:
    Ray() {}

    Ray(double angle) : angle(angle) {}

    ~Ray() {}

    /* <------------------------ Getters ------------------------> */

    double getAngle() const { return angle; }

    double getDistance() const { return distance; }

    double getMaxDepth() const { return maxDepth; }

    bool getHitBoundary() const { return hitBoundary; }

    std::vector<std::pair<int, int>> getPoints() const { return points; }

    /* <------------------------ Setters ------------------------> */

    void setAngle(double newAngle) { angle = newAngle; }

    void setDistance(double newDistance) { distance = newDistance; }

    void setMaxDepth(double newMaxDepth) { maxDepth = newMaxDepth; }

    void setHitBoundary(bool newHitBoundary) { hitBoundary = newHitBoundary; }

    void setPoints(std::vector<std::pair<int, int>> newPoints) { points = newPoints; }

    /* <------------------------ Methods ------------------------> */

    /**
     * Casts a ray from the player's position in a given direction and checks for collisions with the map.
     * 
     * @param[out] playerX The x-coordinate of the player's position.
     * @param[out] playerY The y-coordinate of the player's position.
     * @param[out] map The map containing the game environment.
     */
    void castRay(double playerX, double playerY, std::vector<std::wstring> map);

    void castRayDDA(double playerX, double playerY, std::vector<std::wstring> map);

    void verifyBoundary(int mapX, int mapY, double playerX, double playerY);

    void fixFishEyeEffect(double playerA) { distance *= cosf(angle - playerA); }
};

#endif