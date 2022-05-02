#pragma once
#include <string>

#include "TextureManager.h"

class Map
{
public:
    Map();
    ~Map();
    void LoadMap(int arr[20][25]);
    void DrawMap();

private:
    SDL_Rect src, dst;
    SDL_Texture* wall;
    SDL_Texture* background;
    int map[20][25];
};