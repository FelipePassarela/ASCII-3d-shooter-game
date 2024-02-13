/**
 * @file game.hpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Game class header file.
 * @version 1.0
 * @date 2024-02-04
 * 
 * @copyright Copyright (c) 2024
 */
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "player.hpp"

/**
 * @class Game
 * @brief Represents the game logic and rendering.
 * 
 * The Game class encapsulates the game logic and rendering functionality.
 * It handles the game loop, player movement, and rendering of the game objects.
 */
class Game
{
private:
    std::vector<std::string> map = {
        {"##################################################################"},
        {"#                             #                                  #"},
        {"#    #    #    ##########     #     #########################    #"},
        {"#    #    #    #              #                             #    #"},
        {"#    #    #####################    #####################    #    #"},
        {"#    #                             #                   #    #    #"},
        {"#    ###################################     ###########    #    #"},
        {"#    #              #                        #         #    #    #"},
        {"#    ##########     #    #    ###########    #    #    #    ######"},
        {"#    #              #    #    #         #    #    #    #         #"},
        {"#    #     ##########    #    #####     #    #    #    #    #    #"},
        {"#    #                   #    #         #    #    #    #    #    #"},
        {"#    #####################    #     #####    #    #    #    #    #"},
        {"#                             #              #    #    #    #    #"},
        {"##########################    ################    #    ######    #"},
        {"#              #         #    #                   #    #         #"},
        {"#    #    #    #    #    #    #    ################    #####     #"},
        {"#    #    #    #    #    #    #    #              #              #"},
        {"#    #    #    #    #    #    #    #     ####################    #"},
        {"#    #    #         #    #    #    #                        #    #"},
        {"#    #    ################    #    #    ###########    #    #    #"},
        {"#    #                        #    #    #         #    #    #    #"},
        {"#    ##########################    #    #    #    #    #    #    #"},
        {"#    #         #              #    #    #    #    #    #    #    #"},
        {"#    #    #    ##########     #    #    ######    #    ######    #"},
        {"#         #                   #    #              #              #"},
        {"##################################################################"},
    };    
    const int MAP_WIDTH = map[0].size();    
    const int MAP_HEIGHT = map.size();      
    const int SCREEN_WIDTH = 120;           
    const int SCREEN_HEIGHT = 40;           
    double deltaTime;           ///< The time between frames.
    Player player;              ///< The player object in the game.
    bool showMap = true;        ///< Whether to show the map on the screen.
    bool running = true;    
    
    /* <------------------------ Methods ------------------------> */

    /**
     * @brief Reads the user input.
     * 
     * This function is responsible for reading the user input and updating the game state.
     */
    void readInput();

    /**
     * @brief Moves the player in the game.
     * 
     * This function is responsible for moving the player character in the game.
     * It updates the player's position based on user input.
     */
    void movePlayer();

    /**
     * Renders the 2D objects on the screen.
     *
     * @param screen The screen buffer to render the objects on.
     */
    void render2dObjects(wchar_t* screen);

    /**
     * @brief Creates a wall tile based on the distance of a ray.
     * 
     * This function takes a Ray object as input and calculates the appropriate wall tile
     * based on the distance of the ray. The wall tile is represented by a wide character (wchar_t).
     * 
     * @param ray The Ray object representing the ray to calculate the wall tile for.
     * @return The wall tile represented by a wide character (wchar_t).
     */
    wchar_t createWallTileByDistance(Ray& ray);

    /**
     * Renders the 3D scene on the screen.
     *
     * @param screen The screen buffer to render the scene on.
     */
    void render3dScene(wchar_t* screen);

    /**
     * Renders a column of the screen based on the height of the ray.
     * 
     * @param ray The ray used for rendering.
     * @param screen The screen buffer to render on.
     * @param x The x-coordinate of the column to render.
     * @param wallTile The character representing the wall tile.
     */
    void renderScreenByHeight(Ray& ray, wchar_t* screen, int x, wchar_t wallTile);

public:
    Game() {}

    ~Game() {}

    /**
     * @brief Executes the game loop.
     * 
     * This function is responsible for running the game loop, which handles the game logic and rendering.
     * It continuously updates the game state and renders the game until the game is over.
     */
    void run();
};

#endif  // GAME_HPP