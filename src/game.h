#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "SDL2/SDL_ttf.h"
#include "Vector2D.h"
#include <map>


class ColliderComponent;

class Game 
{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; };
    int count = 0;
    
    static SDL_Renderer *ren;
    static SDL_Event event;
    static std::vector<ColliderComponent *> colliders;
    static void AddTile(int id, int x, int y);
    static void AddCollectible(int id, int x, int y);

private:
    bool isRunning;
    SDL_Window *win;
};

#endif //GAME_H
