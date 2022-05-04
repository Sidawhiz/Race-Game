#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
using namespace std;
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

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

private:
    bool isRunning;
    SDL_Window *win;
};

#endif //GAME_H
