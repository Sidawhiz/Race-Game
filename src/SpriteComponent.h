#pragma once
#include "Components.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include "game.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    const char* path1 ;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:

    std::map<const char*, Animation> animations;
    int animIndex = 0;
    int offsetX = 0;

    SpriteComponent() = default;

    SpriteComponent(const char* path)
    {
        setTexture(path);
    }  

    SpriteComponent(const char* path, bool isAnimated)
    {
        animated = isAnimated;
        setTexture(path);
        path1 = path;

        if (path == "Assets/xx.png")
        {
            Animation idleR = Animation(0, 1, 1, 100);
            Animation moveR = Animation(0, 0, 3, 150);
            Animation idleL = Animation(1, 1, 1, 100);
            Animation moveL = Animation(1, 0, 3, 150);
            Animation idleU = Animation(2, 1, 1, 100);
            Animation moveU = Animation(2, 0, 3, 150);
            Animation idleD = Animation(3, 1, 1, 100);
            Animation moveD = Animation(3, 0, 3, 150);
            Animation die = Animation(4, 2, 12, 140);

            animations.emplace("idleR", idleR);
            animations.emplace("idleL", idleL);
            animations.emplace("idleU", idleU);
            animations.emplace("idleD", idleD);
            animations.emplace("moveR", moveR);
            animations.emplace("moveL", moveL);
            animations.emplace("moveU", moveU);
            animations.emplace("moveD", moveD);
            animations.emplace("die", die);

            Play("idleR");
            setTexture(path);
        }
        if (path == "Assets/xx2.png")
        {
            Animation idleR1 = Animation(0, 1, 1, 100);
            Animation moveR1 = Animation(0, 0, 3, 150);
            Animation idleL1 = Animation(1, 1, 1, 100);
            Animation moveL1 = Animation(1, 0, 3, 150);
            Animation idleU1 = Animation(2, 1, 1, 100);
            Animation moveU1 = Animation(2, 0, 3, 150);
            Animation idleD1 = Animation(3, 1, 1, 100);
            Animation moveD1 = Animation(3, 0, 3, 150);
            Animation die1 = Animation(4, 2, 12, 140);

            animations.emplace("idleR1", idleR1);
            animations.emplace("idleL1", idleL1);
            animations.emplace("idleU1", idleU1);
            animations.emplace("idleD1", idleD1);
            animations.emplace("moveR1", moveR1);
            animations.emplace("moveL1", moveL1);
            animations.emplace("moveU1", moveU1);
            animations.emplace("moveD1", moveD1);
            animations.emplace("die1", die1);
            Play("idleR1");
            setTexture(path);
        }
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
        if (srcRect.x == 520 and srcRect.y == 160){
            
            Play("idleR");
            srcRect.x = srcRect.w * (offsetX + static_cast<int>((SDL_GetTicks() / speed) % frames));
            srcRect.y = animIndex * transform->height;
            // entity->getComponent<TransformComponent>().position = Game::initialPos;
            // Game::dead = false;
        }
        else {
            if (animated)
            {
                srcRect.x = srcRect.w * (offsetX + static_cast<int>((SDL_GetTicks() / speed) % frames));
            }

            srcRect.y = animIndex * transform->height;

            destRect.x = static_cast<int> (transform->position.x);
            destRect.y = static_cast<int> (transform->position.y);
            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;
            if(path1 == "Assets/xx.png" || path1=="Assets/xx2.png"){
                destRect.w = 20;
                destRect.h = 20;
            }
        }
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }

    void Play(const char* name)
    {
        frames = animations[name].frames;
        animIndex = animations[name].indexY;
        speed = animations[name].speed;
        offsetX = animations[name].indexX;
    }
};