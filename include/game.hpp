#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "player.hpp"

class Game
{
private:
    std::vector<std::wstring> map = {
        {L"##############################"},
        {L"#                    ###     #"},
        {L"#                    ###     #"},
        {L"#                    ###     #"},
        {L"#    ###################    ##"},
        {L"#                           ##"},
        {L"#    ###################    ##"},
        {L"#                    ###     #"},
        {L"#                    ###     #"},
        {L"#                    ###     #"},
        {L"###  ##   #######    ###     #"},
        {L"#    ##   ##                 #"},
        {L"#    ##   ##                 #"},
        {L"#    ##   ##                 #"},
        {L"#    ##   ##                 #"},
        {L"##############################"}
    };    
    const int MAP_WIDTH = map[0].size();
    const int MAP_HEIGHT = map.size();
    const int SCREEN_WIDTH = 120;
    const int SCREEN_HEIGHT = 40;
    double deltaTime;
    Player player;
    
    void movePlayer();

    void render2dObjects(wchar_t* screen);

    wchar_t createWallTileByDistance(Ray& ray);

    void render3dScene(wchar_t* screen);

    void renderScreenByHeight(Ray& ray, wchar_t* screen, int x, wchar_t wallTile);

public:
    Game() {}

    ~Game() {}

    void run();
};

#endif