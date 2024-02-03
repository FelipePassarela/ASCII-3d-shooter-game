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

        movePlayer();
        player.castRays(map);

        draw(screen, hConsole, dwBytesWritten);

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            running = false;
        }
    }

    delete[] screen;
    CloseHandle(hConsole);
}

void Game::movePlayer()
{
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
    if (map[(int)player.getY()][(int)player.getX()] == '#' ||
        (int)player.getX() < 0 || (int)player.getX() >= MAP_WIDTH ||
        (int)player.getY() < 0 || (int)player.getY() >= MAP_HEIGHT)
    {
        player.moveBack(direction, deltaTime);
    }
}

void Game::draw(wchar_t* screen, HANDLE hConsole, DWORD dwBytesWritten)
{
    size_t linesWritten = 0;

    // Draw the map
    for (std::size_t i = 0; i < MAP_HEIGHT; ++i)
    {
        for (std::size_t j = 0; j < MAP_WIDTH; ++j)
        {
            screen[i * SCREEN_WIDTH + j] = map[i][j];
        }
        linesWritten++;
    }

    // Draw the player's rays
    for (Ray ray : player.getRays())
    {
        for (std::pair<int, int> point : ray.getPoints())
        {
            int rayX = point.first;
            int rayY = point.second;

            int dx = static_cast<int> (rayX - player.getX());
            int dy = static_cast<int> (rayY - player.getY());
            double distance = sqrt(dx * dx + dy * dy);

            if (distance > 2.5)           // Draw only points that are far enough from the player
                screen[rayY * SCREEN_WIDTH + rayX] = '-';
        }
    }

    screen[(int)player.getY() * SCREEN_WIDTH + (int)player.getX()] = player.getTile();

    #ifdef DEBUG
    wchar_t* debug = new wchar_t[40];
    swprintf_s(debug, 40, L"X=%05.2f Y=%05.2f A=%05.2fpi FPS=%3.2f", player.getX(), player.getY(), player.getAngle() / PI, 1.0f / deltaTime);
    for (std::size_t i = 0; i < wcslen(debug); ++i)
        screen[linesWritten * SCREEN_WIDTH + i] = debug[i];
    linesWritten++;
    delete[] debug;
    #endif

    screen[SCREEN_WIDTH * SCREEN_HEIGHT - 1] = '\0';
    WriteConsoleOutputCharacterW(hConsole, screen, SCREEN_WIDTH * SCREEN_HEIGHT, { 0, 0 }, &dwBytesWritten);
}
