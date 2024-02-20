/**
 * @file player.cpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Player class implementation file.
 * @date 2024-02-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "player.hpp"
#include "constants.hpp"
#include <cmath>
#include <chrono>

void Player::move(Direction direction, double deltaTime)
{
    double correctedSpeed = speed * deltaTime;
    if (direction == Direction::LEFT || direction == Direction::RIGHT)
    {
        correctedSpeed /= 1.5;  // There are spaces between the columns in console, so it's necessary to reduce the speed in x-axis
    }

    if (direction == Direction::LEFT)
    {
        x = x - correctedSpeed * sinf(angle);
        y = y - correctedSpeed * cosf(angle);
    }
    else if (direction == Direction::RIGHT)
    {
        x = x + correctedSpeed * sinf(angle);
        y = y + correctedSpeed * cosf(angle);
    }
    else if (direction == Direction::UP)
    {
        x = x + correctedSpeed * cosf(angle);           // Formula: X = X0 + t * Dx. Source: https://en.wikipedia.org/wiki/Ray_casting                                           
        y = y - correctedSpeed * sinf(angle);           // X0 is the initial position, t is the parameter (speed in this context), and  
    }                                                   // Dx is the direction vector
    else if (direction == Direction::DOWN)
    {
        x = x - correctedSpeed * cosf(angle);     
        y = y + correctedSpeed * sinf(angle);
    }

    if (angle > 2 * PI)         angle -= 2 * PI;
    else if (angle < 0)         angle += 2 * PI;

    if (direction != Direction::NONE)   fixFloatingPointImprecision();  // Necessary when player starts in (1, 1)
}

void Player::rotate(Direction direction, double deltaTime)
{
    double correctedRotationSpeed = rotationSpeed * deltaTime;

    if (direction == Direction::LEFT)           angle += correctedRotationSpeed;
    else if (direction == Direction::RIGHT)     angle -= correctedRotationSpeed;

    if (angle > 2 * PI)         angle -= 2 * PI;
    else if (angle < 0)         angle += 2 * PI;

    updateTile();
}

void Player::shoot()
{
    static auto lastShotTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    double elapsedTime = std::chrono::duration<double>(currentTime - lastShotTime).count();

    if (elapsedTime > 0.3)
    {
        double shotAngle = angle + (rand() % 100 - 50) / 1000.0; // Add a random angle between -0.05 and 0.05 radians to the shot
        Shot shot(x, y, shotAngle, speed + 4.0);
        shots.push_back(shot);
        lastShotTime = currentTime;
    }  
}

void Player::updateShots(const std::string& map, int mapWidth, double deltaTime)
{
    for (auto it = shots.begin(); it != shots.end();)
    {
        it->move(deltaTime);
        if (map[int(it->y) * mapWidth + int(it->x)] == '#')
        {
            it = shots.erase(it); // erase returns the iterator to the next element
        }
        else
        {
            ++it; // Only increment if no erasure happened
        }
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
    FOV += deltaTime * rotationSpeed;
    if (FOV > 2 * PI)   FOV = 0;
}

void Player::fixFloatingPointImprecision()
{
    const int decimalPlaces = 6;
    const double multiplier = std::pow(10.0, decimalPlaces);
    
    x = std::round(x * multiplier) / multiplier;
    y = std::round(y * multiplier) / multiplier;
}
