#pragma once

#include "Components.h"
#include "Vector2D.h"
class TransformComponent : public Component
{

public:

    Vector2D position;
    Vector2D velocity;
    int speed = 2;
    std::string tagged = "";
    // float fx = 1.0f;
    // float fy = 1.0f;

    TransformComponent(){
        position.Zero();
    }

    // void setVelocity(float x, float y){
    //     velocity.x = x;
    //     velocity.y = y;
    // }

    TransformComponent(float x, float y){
        position.x = x;
        position.y = y;
    }

    TransformComponent(float x, float y, int spd)
    {
        position.x = x;
        position.y = y;
        speed = spd;
    }

    TransformComponent(float x, float y, std::string tag1)
    {
        position.x = x;
        position.y = y;
        tagged = tag1;
    }

    void init() override
    {
        velocity.Zero();
    }

    void update() override{
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};