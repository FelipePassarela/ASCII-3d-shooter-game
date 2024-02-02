#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include <vector>

class Ray
{
private:
    double angle = 0.0f;
    double distance = 0.0f;
    std::vector<std::pair<int, int>> points;

public:
    Ray() {}

    Ray(double angle) : angle(angle) {}

    ~Ray() {}

    /* <------------------------ Getters ------------------------> */

    double getAngle() const { return angle; }

    double getDistance() const { return distance; }

    std::vector<std::pair<int, int>> getPoints() const { return points; }

    /* <------------------------ Setters ------------------------> */

    void setAngle(double newAngle) { angle = newAngle; }

    void setDistance(double newDistance) { distance = newDistance; }

    void setPoints(std::vector<std::pair<int, int>> newPoints) { points = newPoints; }

    /* <------------------------ Methods ------------------------> */

    /**
     * Casts a ray from the player's position in a given direction and checks for collisions with the map.
     * 
     * @param[out] playerX The x-coordinate of the player's position.
     * @param[out] playerY The y-coordinate of the player's position.
     * @param[out] playerA The angle of the player's view.
     * @param[out] map The map containing the game environment.
     */
    void castRay(double playerX, double playerY, double playerA, std::vector<std::wstring> map);

};

#endif