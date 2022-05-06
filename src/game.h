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
    static std::vector<std::pair<std::pair<int, int>, bool>> collectibleStatus;
    static void AddTile(int id, int x, int y);
    static void AddCollectible(int id, int x, int y);
    static bool isRunning;
    static void AddFont(std::string id, std::string path, int fontSize);
    static TTF_Font *GetFont(std::string id);
    static std::map<std::string, TTF_Font *> fonts;
    static int playerID;
    static Vector2D initialPos;
    static bool dead;
    static bool GameOver;
    static bool restart;
    static Vector2D crashVelocityPlayer;
    static Vector2D crashVelocityEnemy;
    

private:
    SDL_Window *win;
};

#endif //GAME_H
