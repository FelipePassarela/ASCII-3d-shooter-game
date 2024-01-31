#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include <vector>

class Ray
{
private:
    double angle = 0.0f;
    double distance = 0.0f;
    const double stepDistance = 0.1f;
    const double stepAngle = 0.01f;
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

    void castRays(double playerX, double playerY, double playerA, double FOV, std::vector<std::string> map);

};

#endif