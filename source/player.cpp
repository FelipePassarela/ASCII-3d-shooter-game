#include "player.hpp"
#include "constants.hpp"
#include <cmath>

void Player::move(Direction direction, double deltaTime)
{
    double correctedRotationSpeed = rotationSpeed * deltaTime;
    double correctedSpeed = speed * deltaTime;

    if (direction == Direction::LEFT)           angle += (PI / 20) * correctedRotationSpeed;
    else if (direction == Direction::RIGHT)     angle -= (PI / 20) * correctedRotationSpeed;
    else if (direction == Direction::UP)
    {
        x = x + (correctedSpeed * 2) * cosf(angle);     // Multiplying by 2 because horizontal movement is slower than vertical on console.                                           
        y = y - correctedSpeed * sinf(angle);           // Formula: X = X0 + t * Dx. Source: https://en.wikipedia.org/wiki/Ray_casting  
    }                                                   // X0 is the initial position, t is the parameter (speed in this context), and
    else if (direction == Direction::DOWN)              // Dx is the direction vector
    {
        x = x - (correctedSpeed * 2) * cosf(angle);     
        y = y + correctedSpeed * sinf(angle);
    }

    if (angle > 2 * PI)         angle -= 2 * PI;
    else if (angle < 0)         angle += 2 * PI;

    updateTile();
}

void Player::moveBack(Direction direction, double deltaTime)
{
    if (direction == Direction::UP)
    {
       this->move(Direction::DOWN, deltaTime);
    }
    else if (direction == Direction::DOWN)
    {
        this->move(Direction::UP, deltaTime);
    }
}

void Player::updateTile()
{
    if (angle >= 7 * PI / 4 || angle < PI / 4)      tile = '>';
    else if (angle < 3 * PI / 4)                    tile = '^';
    else if (angle < 5 * PI / 4)                    tile = '<';
    else if (angle < 7 * PI / 4)                    tile = 'v';
}

void Player::increaseFOV(double deltaTime)
{
    FOV += PI / 16 * deltaTime * rotationSpeed;
    if (FOV > 2 * PI)   FOV = 0;
}

void Player::castRays(std::vector<std::wstring> map)
{
    rays.clear();

    double angleOffset = angle - FOV / 2;
    while (angleOffset < angle + FOV / 2)
    {
        Ray ray(angleOffset);
        ray.castRay(x, y, angle, map);
        rays.push_back(ray);
        angleOffset += PI / 180;
    }
}
