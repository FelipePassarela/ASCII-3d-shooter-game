#include "game.hpp"
#include "constants.hpp"
#include <thread>
#include <chrono>
#include <conio.h>
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
    while (running)
    {
        movePlayer();

        draw(screen, hConsole, dwBytesWritten);

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
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
        player.setFOV(player.getFOV() > 2 * PI ? 0 : player.getFOV() + PI / 16);
    }

    player.move(direction);
    if (map[(int)player.getY()][(int)player.getX()] == '#')
    {
        player.moveBack(direction);
    }

    player.castRays(map);
}

void Game::draw(wchar_t* screen, HANDLE hConsole, DWORD dwBytesWritten)
{
    // Draw the map
    for (std::size_t i = 0; i < MAP_HEIGHT; ++i)
    {
        for (std::size_t j = 0; j < MAP_WIDTH; ++j)
        {
            screen[i * SCREEN_WIDTH + j] = map[i][j];
        }
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
    wchar_t* debug = new wchar_t[SCREEN_WIDTH];
    swprintf_s(debug, SCREEN_WIDTH, L"X=%05.2f Y=%05.2f A=%05.2fpi", player.getX(), player.getY(), player.getAngle() / PI);
    for (std::size_t i = 0; i < wcslen(debug); ++i)
    {
        screen[MAP_HEIGHT * SCREEN_WIDTH + i] = debug[i];
    }
    #endif

    screen[SCREEN_WIDTH * SCREEN_HEIGHT - 1] = '\0';
    WriteConsoleOutputCharacterW(hConsole, screen, SCREEN_WIDTH * SCREEN_HEIGHT, { 0, 0 }, &dwBytesWritten);
}

void Game::resetCursor() const
{
    #ifdef _WIN32
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    #else
    std::cout << "\033[0;0H";
    #endif
}
