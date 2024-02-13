/**
 * @file game.cpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Game class implementation file.
 * @version 1.0
 * @date 2024-02-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "game.hpp"
#include "constants.hpp"
#include <thread>
#include <chrono>
#include <cmath>

void Game::run()
{
    wchar_t* screen = new wchar_t[SCREEN_WIDTH * SCREEN_HEIGHT];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    auto previousTime = std::chrono::high_resolution_clock::now();
    while (running)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<double, std::milli>(currentTime - previousTime).count() / 1000;
        previousTime = currentTime;

        readInput();

        render3dScene(screen);
        render2dObjects(screen);

        screen[SCREEN_WIDTH * SCREEN_HEIGHT - 1] = '\0';
        WriteConsoleOutputCharacterW(hConsole, screen, SCREEN_WIDTH * SCREEN_HEIGHT, { 0, 0 }, &dwBytesWritten);
    }

    delete[] screen;
    CloseHandle(hConsole);
}

void Game::render3dScene(wchar_t* screen)
{
    player.clearRays();

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double rayAngle = (player.getAngle() + player.getFOV() / 2.0) - (x / float(SCREEN_WIDTH)) * player.getFOV();
        Ray ray(rayAngle);

        ray.castRay(player.getX(), player.getY(), map);
        player.addRay(ray);

        wchar_t wallTile = createWallTileByDistance(ray);

        renderScreenByHeight(ray, screen, x, wallTile);
    }
}

void Game::renderScreenByHeight(Ray& ray, wchar_t* screen, int x, wchar_t wallTile)
{
    int ceiling = SCREEN_HEIGHT / 2.0 - SCREEN_HEIGHT / ray.getDistance();
    int floor = SCREEN_HEIGHT - ceiling;

    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        if (y <= ceiling)                       screen[y * SCREEN_WIDTH + x] = ' ';
        else if (y > ceiling && y <= floor)     screen[y * SCREEN_WIDTH + x] = wallTile;
        else if (y > floor)
        {
            double floorDistance = 1.0 - (y - SCREEN_HEIGHT / 2.0) / (SCREEN_HEIGHT / 2.0);
            if (floorDistance < 0.25)           screen[y * SCREEN_WIDTH + x] = '#';
            else if (floorDistance < 0.5)       screen[y * SCREEN_WIDTH + x] = 'x';
            else if (floorDistance < 0.75)      screen[y * SCREEN_WIDTH + x] = '.';
            else                                screen[y * SCREEN_WIDTH + x] = ' ';
        }
    }
}

wchar_t Game::createWallTileByDistance(Ray& ray)
{
    wchar_t wallTile = ' ';
    
    if (ray.getDistance() < 0.75)                               wallTile = 0x2593;  // Closest
    else if (ray.getDistance() < ray.getMaxDepth() / 3.5)       wallTile = 0x2588;
    else if (ray.getDistance() < ray.getMaxDepth() / 3.0)       wallTile = 0x2593;
    else if (ray.getDistance() < ray.getMaxDepth() / 2.0)       wallTile = 0x2592;
    else if (ray.getDistance() < ray.getMaxDepth())             wallTile = 0x2591;  // Farthest
    else                                                        wallTile = ' ';

    if (ray.getHitBoundary())                                   wallTile = ' ';

    return wallTile;
}

void Game::readInput()
{
    movePlayer();

    // This is necessary to toggle buttons
    static bool wasMPressed = false;
    bool isMPressed = GetAsyncKeyState('M') & 0x8000;
    static bool wasEPressed = false;
    bool isEPressed = GetAsyncKeyState('E') & 0x8000;

    if (!wasEPressed && isEPressed)
    {
        // Toggle the player's FOV (initial or 2*PI)
        if (player.getFOV() == player.getInitialFOV())  player.setFOV(2 * PI);
        else                                            player.setFOV(player.getInitialFOV());
    }
    if (!wasMPressed && isMPressed)             showMap = !showMap;
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)    player.increaseFOV(deltaTime);
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)   running = false;

    wasMPressed = isMPressed;
    wasEPressed = isEPressed;
}

void Game::movePlayer()
{
    Direction direction = Direction::NONE;

    if (GetAsyncKeyState('W') & 0x8000)     direction = Direction::UP;
    if (GetAsyncKeyState('A') & 0x8000)     direction = Direction::LEFT;
    if (GetAsyncKeyState('S') & 0x8000)     direction = Direction::DOWN;
    if (GetAsyncKeyState('D') & 0x8000)     direction = Direction::RIGHT;

    player.move(direction, deltaTime);

    if (int(player.getX()) <= 0 || int(player.getX()) >= MAP_WIDTH ||
        int(player.getY()) <= 0 || int(player.getY()) >= MAP_HEIGHT ||
        map[int(player.getY())][int(player.getX())] == '#')
    {
        player.moveBack(direction, deltaTime);
    }
}

void Game::render2dObjects(wchar_t* screen)
{
    size_t debugOffset = 0;

    #ifdef DEBUG
    wchar_t* debug = new wchar_t[SCREEN_WIDTH];
    swprintf_s(debug, SCREEN_WIDTH, L"X=%3.2lf Y=%3.2lf A=%3.2lfpi FOV=%3.2lfpi FPS=%3.2lf", 
        player.getX(), player.getY(), player.getAngle() / PI, player.getFOV() / PI, 1.0f / deltaTime);
    for (std::size_t i = 0; i < wcslen(debug); ++i)
        screen[i] = debug[i];
    delete[] debug;
    debugOffset++;
    #endif

    if (showMap)
    {
        // Draw the map
        for (int i = 0; i < MAP_HEIGHT; ++i)
        {
            for (int j = 0; j < MAP_WIDTH; ++j)
            {
                screen[(i + debugOffset) * SCREEN_WIDTH + j] = map[i][j];
            }
        }

        // Draw the player's rays on map
        for (Ray ray : player.getRays())
        {
            for (std::pair<int, int>& point : ray.getPoints())
            {
                int rayX = point.first;
                int rayY = point.second;
                screen[(rayY + debugOffset) * SCREEN_WIDTH + rayX] = '-';
            }
        }

        std::vector<std::pair<int, int>> path = AStar::findPath(int(player.getX()), int(player.getY()), 10, 1, map);
        for (std::pair<int, int>& point : path)
        {
            int pathX = point.first;
            int pathY = point.second;
            screen[(pathY + debugOffset) * SCREEN_WIDTH + pathX] = '.';
        }

        // Draw the player on map
        screen[(int(player.getY()) + debugOffset) * SCREEN_WIDTH + int(player.getX())] = player.getTile();
    }
}