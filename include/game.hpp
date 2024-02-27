/**
 * @file game.hpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Game class header file.
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
#include "AStar.hpp"
#include "objective.hpp"

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
    std::string map;
    const int MAP_WIDTH = 66;  
    const int MAP_HEIGHT = 27;     
    const int SCREEN_WIDTH = 120;           
    const int SCREEN_HEIGHT = 40;           
    double deltaTime = 0.0;                             // The time between frames.
    Player player;
    Objective objective;                                // The objective of the game.
    std::vector<std::pair<int, int>> pathToObjective;
    bool showMap = true;                                // Whether to show the map on the screen.
    bool showPathToObjective = false;                   // Whether to show the path to the objective on the map.
    bool running = true;    
    
    /* <------------------------ Methods ------------------------> */

    /**
     * @brief Performs the initial setup for the game.
     * 
     * This function initializes the game by setting up the necessary components and variables.
     * It should be called before starting the game loop.
     */
    void initialSetup();

    /**
     * @brief Resets the position of the mouse.
     */
    void resetMousePos();

    /**
     * @brief Reads the user input.
     * 
     * @param lastMousePos The last position of the mouse pointer.
     */
    void readInput(POINT& lastMousePos);

    /**
     * @brief Moves the player in the game.
     * 
     * This function is responsible for moving the player character in the game.
     * It updates the player's position based on user input.
     * 
     * @param mouseDeltaX The change in the x-coordinate of the mouse.
     */
    void movePlayer(int mouseDeltaX);

    /**
     * @brief Finds the path to the objective.
     * 
     * This function calculates the path from the current position to the objective.
     * It uses a A* algorithm to determine the optimal path.
     * 
     * @return void
     */
    void findPathToObjective();

    /**
     * Renders the 2D objects on the screen.
     *
     * @param screen The screen buffer to render the objects on.
     */
    void render2dObjects(wchar_t* screen);

    /**
     * Renders the player shots on the screen.
     * 
     * @param screen The screen buffer to render on.
     */
    void renderPlayerShots(wchar_t* screen);

    /**
     * @brief Displays debug information on the screen.
     * 
     * This function takes a pointer to the screen buffer and an offset value as parameters.
     * It displays debug information on the screen starting from the specified offset and
     * increments the offset value accordingly.
     * 
     * @param screen A pointer to the screen buffer.
     * @param yOffset The offset value for displaying the debug information.
     */
    void showDebugInfo(wchar_t * screen, size_t &yOffset);

    /**
     * @brief Creates a wall tile based on the informations of a ray.
     * 
     * This function takes a Ray object as input and calculates the appropriate wall tile
     * based on the informations of the ray. The wall tile is represented by a wide 
     * character (wchar_t).
     * 
     * @param ray The Ray object representing the ray to calculate the wall tile for.
     * @return The wall tile represented by a wide character (wchar_t).
     */
    wchar_t createWallTile(Ray& ray) const;

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
    Game();

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