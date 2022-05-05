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
                sprite->Play("moveU");
                transform->velocity.y = -1;
                transform->update();
                break;
            }
            case SDLK_a:
            {
                sprite->Play("moveL");
                transform->velocity.x = -1;
                transform->update();
                break;
            }
            case SDLK_s:
            {
                sprite->Play("moveD");
                transform->velocity.y = 1;
                transform->update();
                break;
            }
            case SDLK_d:
            {
                sprite->Play("moveR");
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
                sprite->Play("idleU");
                transform->velocity.Zero();
                transform->update();
                break;
            }
            case SDLK_a:
            {
                sprite->Play("idleL");
                transform->velocity.Zero();
                transform->update();
                break;
            }
            case SDLK_s:
            {
                sprite->Play("idleD");
                transform->velocity.Zero();
                transform->update();
                break;
            }
            case SDLK_d:
            {
                sprite->Play("idleR");
                transform->velocity.Zero();
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