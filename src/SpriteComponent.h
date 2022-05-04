#pragma once
#include "Components.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
// //#include "Game/Animation.h"
// #include <map>
// #include "game.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent() = default;

    SpriteComponent(const char* path)
    {
        setTexture(path);
    }  

    void setTexture(const char* path){
        texture = TextureManager::LoadTexture(path);
    } 

    void init() override
    {   
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;

    } 

    void update() override
    {
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->scale * transform->width;
        destRect.h = transform->scale * transform->height;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }
};