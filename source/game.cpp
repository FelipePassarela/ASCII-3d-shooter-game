#include "game.hpp"
#include <thread>
#include <chrono>
#include <conio.h>

void Game::run()
{
    draw();

    bool running = true;
    while (running)
    {
        char input = tolower(_getch());

        movePlayer(input);

        draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void Game::movePlayer(char input)
{
    switch (input)
    {
    case 'w':
        if (map[player.getY() - 1][player.getX()] != '#' && player.getY() > 0)
            player.move(Direction::UP);
        break;
    case 'a':
        if (map[player.getY()][player.getX() - 1] != '#' && player.getX() > 0)
            player.move(Direction::LEFT);
        break;
    case 's':
        if (map[player.getY() + 1][player.getX()] != '#' && player.getY() < MAP_HEIGHT - 1)
            player.move(Direction::DOWN);
        break;
    case 'd':
        if (map[player.getY()][player.getX() + 1] != '#' && player.getX() < MAP_WIDTH - 1)
            player.move(Direction::RIGHT);
        break;
    }

    // if (_kbhit())            // NOTE: Util for going through portals
}

void Game::draw()
{
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
    
    for (std::size_t i = 0; i < MAP_HEIGHT; ++i)
    {
        for (std::size_t j = 0; j < MAP_WIDTH; ++j)
        {
            if (player.getX() == j && player.getY() == i)
                std::cout << player.getTile() << " ";
            else
                std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
