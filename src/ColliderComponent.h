#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;

    TransformComponent* transform;

    ColliderComponent(std::string t)
    {
        tag = t;
    }

    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
        Game::colliders.push_back(this);
    }

    void update() override
    {
        collider.x = static_cast<int> (transform->position.x) ;
        collider.y = static_cast<int> (transform->position.y) ;
        collider.w = transform->scale * transform->width;
        collider.h = transform->scale * transform->height;
        if (tag == "collectible"){
            collider.x = static_cast<int> (transform->position.x) +10;
            collider.y = static_cast<int> (transform->position.y) +10;
            collider.w = 10;
            collider.h = 10;
        }
        else if(tag == "obstacle") {
            collider.x = static_cast<int> (transform->position.x) +3;
            collider.y = static_cast<int> (transform->position.y) +3;
            collider.w = 26;
            collider.h = 26;
        }
        else if(tag == "enemy" || tag=="player"){
            collider.w = 20;
            collider.h = 20;
        }
    }

    void Destroy()
    {
        entity->destroy();
    }


};