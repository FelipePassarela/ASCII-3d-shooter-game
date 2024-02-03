#include "game.hpp"
#include "constants.hpp"
#include <thread>
#include <chrono>
#include <cmath>
#include <iomanip>

void Game::run()
{
    wchar_t* screen = new wchar_t[SCREEN_WIDTH * SCREEN_HEIGHT];
    std::fill(screen, screen + SCREEN_WIDTH * SCREEN_HEIGHT, L' ');
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    draw(screen, hConsole, dwBytesWritten);

    bool running = true;
    auto previousTime = std::chrono::high_resolution_clock::now();
    while (running)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<double, std::milli>(currentTime - previousTime).count() / 1000;
        previousTime = currentTime;

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)    running = false;

        movePlayer();
        
        // Render the 3D scene
        player.clearRays();
        for (std::size_t x = 0; x < SCREEN_WIDTH; x++)
        {
            double rayAngle = (player.getAngle() + player.getFOV() / 2.0) - (x / float(SCREEN_WIDTH)) * player.getFOV();
            Ray ray(rayAngle);

            ray.castRay(player.getX(), player.getY(), map);
            player.addRay(ray);

            short wallTile = ' ';
            if (ray.getDistance() <= ray.getMaxDepth() / 4.0)           wallTile = 0x2588;  // Full block (closest)
            else if (ray.getDistance() < ray.getMaxDepth() / 3.0)       wallTile = 0x2593;
            else if (ray.getDistance() < ray.getMaxDepth() / 2.0)       wallTile = 0x2592;
            else if (ray.getDistance() < ray.getMaxDepth())             wallTile = 0x2591;
            else                                                        wallTile = ' ';     // Space (farthest)

            int ceiling = (SCREEN_HEIGHT / 2.0) - (SCREEN_HEIGHT / ray.getDistance());
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

        draw(screen, hConsole, dwBytesWritten);
    }

    delete[] screen;
    CloseHandle(hConsole);
}

void Game::movePlayer()
{
    // FIXME: The player can move through walls when the game starts

    Direction direction = Direction::NONE;

    if (GetAsyncKeyState('W') & 0x8000)
    {
        direction = Direction::UP;
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        direction = Direction::LEFT;
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        direction = Direction::DOWN;
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        direction = Direction::RIGHT;
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        player.increaseFOV(deltaTime); 
    }

    player.move(direction, deltaTime);
    if (map[int(player.getY())][int(player.getX())] == '#' ||
        int(player.getX()) < 0 || int(player.getX()) >= MAP_WIDTH ||
        int(player.getY()) < 0 || int(player.getY()) >= MAP_HEIGHT)
    {
        player.moveBack(direction, deltaTime);
    }
}

void Game::draw(wchar_t* screen, HANDLE hConsole, DWORD dwBytesWritten)
{
    size_t debugOffset = 0;

    #ifdef DEBUG
    wchar_t* debug = new wchar_t[40];
    swprintf_s(debug, 40, L"X=%05.2f Y=%05.2f A=%05.2fpi FPS=%3.2f", player.getX(), player.getY(), player.getAngle() / PI, 1.0f / deltaTime);
    for (std::size_t i = 0; i < wcslen(debug); ++i)
        screen[i] = debug[i];
    delete[] debug;
    debugOffset++;
    #endif

    // Draw the map
    for (std::size_t i = 0; i < MAP_HEIGHT; ++i)
    {
        for (std::size_t j = 0; j < MAP_WIDTH; ++j)
        {
            screen[(i + debugOffset) * SCREEN_WIDTH + j] = map[i][j];
        }
    }

    // Draw the player's rays
    for (Ray ray : player.getRays())
    {
        for (std::pair<int, int> point : ray.getPoints())
        {
            int rayX = point.first;
            int rayY = point.second;
            screen[(rayY + debugOffset) * SCREEN_WIDTH + rayX] = '-';
        }
    }

    // Draw the player
    screen[(int(player.getY()) + debugOffset) * SCREEN_WIDTH + int(player.getX())] = player.getTile();

    screen[SCREEN_WIDTH * SCREEN_HEIGHT - 1] = '\0';
    WriteConsoleOutputCharacterW(hConsole, screen, SCREEN_WIDTH * SCREEN_HEIGHT, { 0, 0 }, &dwBytesWritten);
}
