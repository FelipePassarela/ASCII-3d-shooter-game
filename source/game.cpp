#include "game.hpp"
#include "constants.hpp"
#include <thread>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <iomanip>

void Game::run()
{
    draw();

    bool running = true;
    while (running)
    {
        char input = tolower(_getch());
        movePlayer(input);

        draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Game::movePlayer(char input)
{
    Direction direction = Direction::UP;

    switch (input)
    {
        case 'w':
            direction = Direction::UP;
            break;
        case 'a':
            direction = Direction::LEFT;
            break;
        case 's':
            direction = Direction::DOWN;
            break;
        case 'd':
            direction = Direction::RIGHT;
            break;
    }

    player.move(direction);
    if (map[(int)player.getY()][(int)player.getX()] == '#')
    {
        player.moveBack(direction);
    }

    player.getRay().castRays(player.getX(), player.getY(), player.getAngle(), player.getFOV(), map);

    // if (_kbhit())                // NOTE: Util for going through portals
}

void Game::draw()
{
    resetCursor();

    std::vector<std::string> mapCopy = map;
    mapCopy[player.getY()][player.getX()] = player.getTile();

    // Draw the player's ray
    for (std::pair<int, int> point : player.getRay().getPoints())
    {
        int x = point.first;
        int y = point.second;

        double dx = x - player.getX();
        double dy = y - player.getY();
        double distance = sqrt(dx * dx + dy * dy);

        if (distance > 2.5)           // Draw only points that are far enough from the player
            mapCopy[y][x] = '-';
    }

    // Draw the map
    for (std::size_t i = 0; i < MAP_HEIGHT; ++i)
    {
        for (std::size_t j = 0; j < MAP_WIDTH; ++j)
        {
            std::cout << mapCopy[i][j] << " ";
        }
        std::cout << std::endl;
    }

    #ifdef DEBUG
    std::cout << std::setprecision(2);    // FIXME: Pi is displaying as 'pii'
    std::cout << "X=" << player.getX() << " Y=" << player.getY() << " A=" << player.getAngle() / PI << "pi" << std::endl;
    #endif
}

void Game::resetCursor() const
{
    #ifdef _WIN32
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    #else
    std::cout << "\033[0;0H";
    #endif
}
