/**
 * @file game.cpp
 * @author Felipe Passarela (felipepassarela11@gmail.com)
 * @brief Game class implementation file.
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
#include <random>

Game::Game() {
    map += "##################################################################";
    map += "#                             #                                  #";
    map += "#    #    #    ##########     #     #########################    #";
    map += "#    #    #    #              #                             #    #";
    map += "#    #    #####################    #####################    #    #";
    map += "#    #                             #                   #    #    #";
    map += "#    ###################################     ###########    #    #";
    map += "#    #              #                        #         #    #    #";
    map += "#    ##########     #    #    ###########    #    #    #    ######";
    map += "#    #              #    #    #         #    #    #    #         #";
    map += "#    #     ##########    #    #####     #    #    #    #    #    #";
    map += "#    #                   #    #         #    #    #    #    #    #";
    map += "#    #####################    #     #####    #    #    #    #    #";
    map += "#                             #              #    #    #    #    #";
    map += "##########################    ################    #    ######    #";
    map += "#              #         #    #  X                #    #         #";
    map += "#    #    #    #    #    #    #    ################    #####     #";
    map += "#    #    #    #    #    #    #    #              #              #";
    map += "#    #    #    #    #    #    #    #     ####################    #";
    map += "#    #    #         #    #    #    #                        #    #";
    map += "#    #    ################    #    #    ###########    #    #    #";
    map += "#    #                        #    #    #         #    #    #    #";
    map += "#    ##########################    #    #    #    #    #    #    #";
    map += "#    #         #              #    #    #    #    #    #    #    #";
    map += "#    #    #    ##########     #    #    ######    #    ######    #";
    map += "#         #                   #  ^ #              #              #";
    map += "##################################################################";
}

void Game::run()
{
    initialSetup();

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

        player.updateShots(map, MAP_WIDTH, deltaTime);

        if (showPathToObjective)                                        findPathToObjective();
        if (player.isAtPosition(objective.getX(), objective.getY()))    objective.randomizePosition(MAP_WIDTH, MAP_HEIGHT, map);

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

        ray.castRay(player.getX(), player.getY(), MAP_WIDTH, MAP_HEIGHT, map, objective);
        player.addRay(ray);

        wchar_t wallTile = createWallTileByRay(ray);

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

        renderPlayerShots(screen, x, y);
    }
}

wchar_t Game::createWallTileByRay(Ray& ray)
{
    wchar_t wallTile = ' ';
    
    if (ray.getHitWall())
    {
        if (ray.getDistance() < 0.75)                           wallTile = 0x2593;  // Closest
        else if (ray.getDistance() < ray.getMaxDepth() / 3.5)   wallTile = 0x2588;
        else if (ray.getDistance() < ray.getMaxDepth() / 3.0)   wallTile = 0x2593;
        else if (ray.getDistance() < ray.getMaxDepth() / 2.0)   wallTile = 0x2592;
        else if (ray.getDistance() < ray.getMaxDepth())         wallTile = 0x2591;  // Farthest
    }
    else if (ray.getHitObjective())
    {
        objective.randomizeWallTile(wallTile, ray.getDistance());
    }

    if (ray.getHitBoundary())                       wallTile = ' ';    
    if (ray.getDistance() >= ray.getMaxDepth())     wallTile = ' ';

    return wallTile;
}

void Game::initialSetup()
{
    for (int i = 0; i < MAP_HEIGHT; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            char mapTile = map[i * MAP_WIDTH + j];
            if (mapTile == '<' || mapTile == '>' || mapTile == '^' || mapTile == 'v')
            {
                player.setX(j);
                player.setY(i);
                player.setAngle(PI / 2);
                player.setTile(mapTile);
                map[i * MAP_WIDTH + j] = ' ';
            }
            else if (mapTile == 'X')
            {
                objective.setX(j);
                objective.setY(i);
                objective.setTile(mapTile);
                map[i * MAP_WIDTH + j] = ' ';
            }
        }
    }
}

void Game::readInput()
{
    movePlayer();

    // This is necessary to toggle buttons
    static bool wasMPressed = false;
    static bool wasEPressed = false;
    static bool wasPPressed = false;

    bool isMPressed = GetAsyncKeyState('M') & 0x8000;
    bool isEPressed = GetAsyncKeyState('E') & 0x8000;
    bool isPPressed = GetAsyncKeyState('P') & 0x8000;

    if (!wasEPressed && isEPressed)
    {
        // Toggle the player's FOV (initial or 2*PI)
        if (player.getFOV() == player.getInitialFOV())  player.setFOV(2 * PI);
        else                                            player.setFOV(player.getInitialFOV());
    }
    if (!wasMPressed && isMPressed)             showMap = !showMap;
    if (!wasPPressed && isPPressed && showMap)  showPathToObjective = !showPathToObjective; // Only show path if map is shown
    if (GetAsyncKeyState('Q') & 0x8000)         player.increaseFOV(deltaTime);
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)    player.shoot();
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)   running = false;

    wasMPressed = isMPressed;
    wasEPressed = isEPressed;
    wasPPressed = isPPressed;
}

void Game::movePlayer()
{
    Direction direction = Direction::NONE;

    if (GetAsyncKeyState('W') & 0x8000)     direction = Direction::UP;
    if (GetAsyncKeyState('A') & 0x8000)     direction = Direction::LEFT;
    if (GetAsyncKeyState('S') & 0x8000)     direction = Direction::DOWN;
    if (GetAsyncKeyState('D') & 0x8000)     direction = Direction::RIGHT;

    player.move(direction, deltaTime);

    int playerX = int(player.getX());
    int playerY = int(player.getY());

    if (playerX <= 0 || playerX >= MAP_WIDTH ||
        playerY <= 0 || playerY >= MAP_HEIGHT ||
        map[playerY * MAP_WIDTH + playerX] == '#')
    {
        player.moveBack(direction, deltaTime);
    }
}

void Game::renderPlayerShots(wchar_t* screen, int x, int y)
{
    for (Shot& shot : player.getShots())
    {
        const int MAX_SHOT_RADIUS = 20;
        double shotDistance = sqrt(pow(shot.x - player.getX(), 2) + pow(shot.y - player.getY(), 2));
        double shotRadius = MAX_SHOT_RADIUS / shotDistance;

        if (shotRadius > MAX_SHOT_RADIUS) continue;

        int dx = SCREEN_WIDTH / 2 - x;
        int dy = (SCREEN_HEIGHT / 2 - y) * 2;   // Multiply by 2 to make the shots look more circular 
        double distanceFromCenter = sqrt(dx * dx + dy * dy);

        if (distanceFromCenter <= shotRadius)
        {
            wchar_t tile = ' ';
            if (shotDistance < 0.75)                           tile = 0x2593;  // Closest
            else if (shotDistance < MAX_SHOT_RADIUS / 5.0)     tile = 0x2588;
            else if (shotDistance < MAX_SHOT_RADIUS / 3.0)     tile = 0x2593;
            else if (shotDistance < MAX_SHOT_RADIUS / 1.5)     tile = 0x2592;
            else if (shotDistance < MAX_SHOT_RADIUS)           tile = 0x2591;  // Farthest
            screen[y * SCREEN_WIDTH + x] = tile;
        }
    }
}

void Game::findPathToObjective()
{
    static int previousPlayerX = -1;
    static int previousPlayerY = -1;
    int playerX = int(player.getX());
    int playerY = int(player.getY());

    if (previousPlayerX != playerX || previousPlayerY != playerY)   // Only find path if the player has moved
    {
        int objectiveX = int(objective.getX());
        int objectiveY = int(objective.getY());

        pathToObjective = AStar::findPath(playerX, playerY, objectiveX, objectiveY, MAP_WIDTH, MAP_HEIGHT, map);
    }

    previousPlayerX = int(player.getX());
    previousPlayerY = int(player.getY());
}

void Game::render2dObjects(wchar_t* screen)
{
    size_t yOffset = 0;

    showDebugInfo(screen, yOffset);

    if (showMap)
    {
        // Draw the map
        for (int i = 0; i < MAP_HEIGHT; ++i)
        {
            for (int j = 0; j < MAP_WIDTH; ++j)
            {
                screen[(i + yOffset) * SCREEN_WIDTH + j] = map[i * MAP_WIDTH + j];
            }
        }

        // Draw the player's rays
        for (Ray ray : player.getRays())
        {
            for (std::pair<int, int>& point : ray.getPoints())
            {
                int rayX = point.first;
                int rayY = point.second;
                screen[(rayY + yOffset) * SCREEN_WIDTH + rayX] = '-';
            }
        }

        // Draw the path to the objective
        if (showPathToObjective)
        {
            for (std::pair<int, int>& point : pathToObjective)
            {
                int pathX = point.first;
                int pathY = point.second;
                screen[(pathY + yOffset) * SCREEN_WIDTH + pathX] = '.';
            }
        }

        // Draw the player's shoots on map.
        for (Shot& shot : player.getShots())
        {
            screen[(int(shot.y) + yOffset) * SCREEN_WIDTH + int(shot.x)] = '*';
        }

        // Draw the objective and the player
        screen[int((objective.getY()) + yOffset) * SCREEN_WIDTH + int(objective.getX())] = objective.getTile();
        screen[(int(player.getY()) + yOffset) * SCREEN_WIDTH + int(player.getX())] = player.getTile();
    }
}

void Game::showDebugInfo(wchar_t* screen, size_t& yOffset)
{
    #ifdef DEBUG
    static auto previous = std::chrono::high_resolution_clock::now();
    auto current = std::chrono::high_resolution_clock::now();

    static double fps = 0.0;

    wchar_t* debug = new wchar_t[SCREEN_WIDTH];
    swprintf_s(debug, SCREEN_WIDTH, L"X=%3.2lf Y=%3.2lf A=%3.2lfpi FOV=%3.2lfpi FPS=%3.2lf",
               player.getX(), player.getY(), player.getAngle() / PI, player.getFOV() / PI, fps);
    for (std::size_t i = 0; i < wcslen(debug); ++i)
    {
        screen[i] = debug[i];
    }

    std::chrono::duration<double> elapsed = current - previous;
    if (elapsed.count() > 1/6.0)
    {
        fps = 1.0 / deltaTime;
        previous = current;
    }

    delete[] debug;
    yOffset++;
    #endif
}
