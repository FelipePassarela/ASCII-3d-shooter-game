#include <iostream>
#include "game.hpp"

int main()
{
    Game game;

    game.run();

    #ifdef DEBUG
    std::cout << "Press ENTER to continue...";
    std::cin.get();
    #endif

    return 0;
}
