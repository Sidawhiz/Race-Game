#pragma once

#include "game.h"
#include "entity.h"
#include "Components.h"

class EnemyController : public Component
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
            case SDLK_UP:
            {
                sprite->Play("moveU1");
                transform->velocity.y = -1;
                transform->update();
                break;
            }
            case SDLK_LEFT:
            {
                sprite->Play("moveL1");
                transform->velocity.x = -1;
                transform->update();
                break;
            }
            case SDLK_DOWN:
            {
                sprite->Play("moveD1");
                transform->velocity.y = 1;
                transform->update();
                break;
            }
            case SDLK_RIGHT:
            {
                sprite->Play("moveR1");
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
            case SDLK_UP:
            {
                sprite->Play("idleU1");
                transform->velocity.Zero();
                transform->update();
                break;
            }
            case SDLK_LEFT:
            {
                sprite->Play("idleL1");
                transform->velocity.Zero();
                transform->update();
                break;
            }
            case SDLK_DOWN:
            {
                sprite->Play("idleD1");
                transform->velocity.Zero();
                transform->update();
                break;
            }
            case SDLK_RIGHT:
            {
                sprite->Play("idleR1");
                transform->velocity.Zero();
                transform->update();
                break;
            }
            case SDLK_ESCAPE:
            {
                Game::isRunning=false;
            }
            default:
            {
                break;
            }
            }
        }
    }
};    