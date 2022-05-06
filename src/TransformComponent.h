#pragma once

#include "Components.h"
#include "Vector2D.h"
class TransformComponent : public Component
{

public:

    Vector2D position;
    Vector2D velocity;
    std::string tagged = "";
    int height = 40;
    int width = 40;
    int scale = 1;
    int speed = 2;
    int count = 0;
    int crash = 0;

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

    TransformComponent(int sc)
    {
        position.Zero();
        scale = sc;
    }

    TransformComponent(float x, float y, int h, int w, int sc)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
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
        if(crash){
            if(count>15 && count<=30){
                count--;
                speed=-2;
                // velocity = Game::crashVelocityPlayer;
                //std::cout << count << std::endl;
            }
            if(count <=15){
                count--;
                speed = 0;
            }
            if(count == 1 && speed == 0){
                speed=2;
                crash = 0;
            }
        }
    }

};