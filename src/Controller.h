#pragma once

#include "game.h"
#include "entity.h"
#include "Components.h"

class Controller : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
            {
                transform->velocity.y = -1;
                transform->velocity.x = 0;
                transform->update();
                break;
            }
            case SDLK_a:
            {
                transform->velocity.y = 0;
                transform->velocity.x = -1;
                transform->update();
                break;
            }
            case SDLK_s:
            {
                transform->velocity.y = 1;
                transform->velocity.x = 0;
                transform->update();
                break;
            }
            case SDLK_d:
            {
                transform->velocity.y = 0;
                transform->velocity.x = 1;
                transform->update();
                break;
            }
            default:
            {
                break;
            }
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
            {
                transform->velocity.y = 0;
                transform->velocity.x = 0;
                transform->update();
                break;
            }
            case SDLK_a:
            {
                transform->velocity.y = 0;
                transform->velocity.x = 0;
                transform->update();
                break;
            }
            case SDLK_s:
            {
                transform->velocity.y = 0;
                transform->velocity.x = 0;
                transform->update();
                break;
            }
            case SDLK_d:
            {
                transform->velocity.y = 0;
                transform->velocity.x = 0;
                transform->update();
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
};    