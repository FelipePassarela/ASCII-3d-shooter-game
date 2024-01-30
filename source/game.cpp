#include "game.hpp"
#include "constants.hpp"
#include <thread>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <cmath>

void Game::run()
{
    draw();

    bool running = true;
    while (running)
    {
        char input = tolower(_getch());

        movePlayer(input);

        draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void Game::movePlayer(char input)
{
    Direction direction;

    switch (input)
    {
        case 'w':
            direction = Direction::UP;
            player.move(direction);
            break;
        case 'a':
            direction = Direction::LEFT;
            player.move(direction);
            break;
        case 's':
            direction = Direction::DOWN;
            player.move(direction);
            break;
        case 'd':
            direction = Direction::RIGHT;
            player.move(direction);
            break;
    }

    if (map[(int)player.getY()][(int)player.getX()] == '#')
    {
        player.moveBack(direction);
    }

    if (player.getAngle() > PI / 2 && player.getAngle() < 3 * PI / 2)
    {
        player.setTile('<');
    } else
    {
        player.setTile('>');
    }

    player.getRay().castRay(player.getX(), player.getY(), player.getFOV(), map);

    // if (_kbhit())                // NOTE: Util for going through portals
}

void Game::draw()
{
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

    std::vector<std::string> mapCopy = map;

    for (std::pair<double, double> point : player.getRay().getPoints())
    {
        int x = (int)point.first;
        int y = (int)point.second;
        mapCopy[point.second][point.first] = 'o';
    }
    mapCopy[player.getY()][player.getX()] = player.getTile();

    for (std::size_t i = 0; i < MAP_HEIGHT; ++i)
    {
        for (std::size_t j = 0; j < MAP_WIDTH; ++j)
        {
            std::cout << mapCopy[i][j] << " ";
        }
        std::cout << std::endl;
    }

    #ifdef DEBUG
    std::cout << "X: " << player.getX() << std::endl;
    std::cout << "Y: " << player.getY() << std::endl;
    std::cout << "Angle: " << player.getAngle() / PI << "pi " << "Sin: " << sinf(player.getAngle()) << " Cos: " << cosf(player.getAngle()) << std::endl;
    std::cout << "Ray Angle:" << player.getRay().getAngle() << std::endl;
    std::cout << "Ray Distance: " << player.getRay().getDistance() << std::endl;
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
