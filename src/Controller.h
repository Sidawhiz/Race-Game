#pragma once

#include "game.h"
#include "entity.h"
#include "Components.h"

class Controller : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    Game *game;

    Controller(Game *gameptr){
        game = gameptr;
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if(!Game::dead)
        {
            if (Game::event.type == SDL_KEYDOWN && Game::playerID == 1)
            {
                switch (Game::event.key.keysym.sym)
                {
                case SDLK_w:
                {
                    sprite->Play("moveU");
                    transform->velocity.y = -1;
                    transform->update();

                    Game::userInput = UserInput::W;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Yellow]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_a:
                {
                    sprite->Play("moveL");
                    transform->velocity.x = -1;
                    transform->update();
                    
                    Game::userInput = UserInput::A;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Yellow]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_s:
                {
                    sprite->Play("moveD");
                    transform->velocity.y = 1;
                    transform->update();
                    
                    Game::userInput = UserInput::S;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Yellow]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_d:
                {
                    sprite->Play("moveR");
                    transform->velocity.x = 1;
                    transform->update();
                    
                    Game::userInput = UserInput::D;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Yellow]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                default:
                {
                    break;
                }
                }
            }

            else if (Game::event.type == SDL_KEYUP && Game::playerID == 1)
            {
                switch (Game::event.key.keysym.sym)
                {
                case SDLK_w:
                {
                    sprite->Play("idleU");
                    transform->velocity.Zero();
                    transform->update();
                    
                    Game::userInput = UserInput::W_UP;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Yellow]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_a:
                {
                    sprite->Play("idleL");
                    transform->velocity.Zero();
                    transform->update();
                    
                    Game::userInput = UserInput::A_UP;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Yellow]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_s:
                {
                    sprite->Play("idleD");
                    transform->velocity.Zero();
                    transform->update();
                    
                    Game::userInput = UserInput::S_UP;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Yellow]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_d:
                {
                    sprite->Play("idleR");
                    transform->velocity.Zero();
                    transform->update();
                    
                    Game::userInput = UserInput::D_UP;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Yellow]: Sent input: " << int(Game::userInput) << "\n";
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
            else if(Game::playerID == 1){
                Game::userInput = UserInput::DUMMY;
            }
            else{
                UserInput k = Game::otherUserInput;
                if(Game::playerID==2){
                    if(k == UserInput::W){
                        sprite->Play("moveU");
                        transform->velocity.y = -1;
                        transform->update();
                    }
                    else if(k == UserInput::A){
                        sprite->Play("moveL");
                        transform->velocity.x = -1;
                        transform->update();
                    }
                    else if(k == UserInput::S){
                        sprite->Play("moveD");
                        transform->velocity.y = 1;
                        transform->update();
                    }
                    else if(k == UserInput::D){
                        sprite->Play("moveR");
                        transform->velocity.x = 1;
                        transform->update();
                    }
                    else if(k == UserInput::W_UP){
                        sprite->Play("idleU");
                        transform->velocity.Zero();
                        transform->update();
                    }
                    else if(k == UserInput::A_UP){
                        sprite->Play("idleL");
                        transform->velocity.Zero();
                        transform->update();
                    }
                    else if(k == UserInput::S_UP){
                        sprite->Play("idleD");
                        transform->velocity.Zero();
                        transform->update();
                    }
                    else if(k == UserInput::D_UP){
                        sprite->Play("idleR");
                        transform->velocity.Zero();
                        transform->update();
                    }
                }
                Game::otherUserInput = UserInput::DUMMY;
            }
        }    
    }
};    