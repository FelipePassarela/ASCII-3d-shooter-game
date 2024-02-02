#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"

class Game
{
private:
    std::vector<std::string> map = {
        {"########################################################"},
        {"#                                        ###           #"},
        {"#                                        ###           #"},
        {"#                                        ###           #"},
        {"#                                        ###           #"},
        {"#                                        ###           #"},
        {"#                                        ###           #"},
        {"#                     ####                             #"},
        {"#                        #               ###           #"},
        {"#                     ####               ###           #"},
        {"#                                        ###           #"},
        {"#                                        ###           #"},
        {"#                                        ###           #"},
        {"#                                                      #"},
        {"#                                                      #"},
        {"#                                                      #"},
        {"#                                                      #"},
        {"#  ##  ##  ####         ##                    ##       #"},
        {"#            ##         ##                    ##       #"},
        {"#            ##         ##                    ##       #"},
        {"#            ##         ##                    ##       #"},
        {"#            ##         ##                    ##       #"},
        {"#            ##         ##                    ##       #"},
        {"#            ##         ##                    ##       #"},
        {"#            ##         ##                    ##       #"},
        {"#            ##         ##                    ##       #"},
        {"########################################################"}
    };
        
    const std::size_t MAP_WIDTH = map[0].size();
    const std::size_t MAP_HEIGHT = map.size();
    Player player;
    
    void movePlayer(char input);

    void draw();

    void resetCursor() const;

public:
    Game() {}

    ~Game() {}

    void run();
};

#endif