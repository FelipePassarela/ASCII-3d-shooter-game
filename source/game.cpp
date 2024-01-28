#include "game.hpp"
#include <thread>
#include <chrono>

Game::Game()
{
    map[player.getY()][player.getX()] = player.getTile();
}

void Game::run()
{
    bool running = true;
    while (running)
    {
        draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        running = false;        // TODO: remove this line
    }
}

void Game::draw()
{
    for (std::size_t i = 0; i < MAP_HEIGHT; ++i)
    {
        for (std::size_t j = 0; j < MAP_WIDTH; ++j)
        {
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
