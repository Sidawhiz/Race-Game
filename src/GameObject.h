#pragma once
#include "game.h"

class GameObject
{
public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();

    void Update();
    void Render();

private:
    int xpos, ypos;
    SDL_Rect srcR , dstR;
    SDL_Texture *objTexture;

};