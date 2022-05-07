#pragma once

#include "game.h"
#include "entity.h"
#include "Components.h"

class EnemyController : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    Game *game;

    EnemyController(Game *gameptr){
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
            if (Game::event.type == SDL_KEYDOWN && Game::playerID == 2)
            {
                switch (Game::event.key.keysym.sym)
                {
                case SDLK_UP:
                {
                    sprite->Play("moveU1");
                    transform->velocity.y = -1;
                    transform->update();

                    Game::userInput = UserInput::W;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Red]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_LEFT:
                {
                    sprite->Play("moveL1");
                    transform->velocity.x = -1;
                    transform->update();
                    
                    Game::userInput = UserInput::A;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Red]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_DOWN:
                {
                    sprite->Play("moveD1");
                    transform->velocity.y = 1;
                    transform->update();
                    
                    Game::userInput = UserInput::S;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Red]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_RIGHT:
                {
                    sprite->Play("moveR1");
                    transform->velocity.x = 1;
                    transform->update();
                    
                    Game::userInput = UserInput::D;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Red]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                default:
                {
                    break;
                }
                }
            }

            else if (Game::event.type == SDL_KEYUP && Game::playerID == 2)
            {
                switch (Game::event.key.keysym.sym)
                {
                case SDLK_UP:
                {
                    sprite->Play("idleU1");
                    transform->velocity.Zero();
                    transform->update();
                    
                    Game::userInput = UserInput::W_UP;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Red]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_LEFT:
                {
                    sprite->Play("idleL1");
                    transform->velocity.Zero();
                    transform->update();
                    
                    Game::userInput = UserInput::A_UP;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Red]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_DOWN:
                {
                    sprite->Play("idleD1");
                    transform->velocity.Zero();
                    transform->update();
                    
                    Game::userInput = UserInput::S_UP;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Red]: Sent input: " << int(Game::userInput) << "\n";
                    break;
                }
                case SDLK_RIGHT:
                {
                    sprite->Play("idleR1");
                    transform->velocity.Zero();
                    transform->update();
                    
                    Game::userInput = UserInput::D_UP;
                    Game::toUpdate = true;

                    message<GameMsg> msg;
                    msg.header.id = GameMsg::Game_UserInput;
                    msg << Game::userInput;
                    game->Send(msg);
                    std::cout << "[Red]: Sent input: " << int(Game::userInput) << "\n";
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
            else if(Game::playerID == 2){
                Game::userInput = UserInput::DUMMY;
            }
            else{
                UserInput k = Game::otherUserInput;
                if(Game::playerID==1){
                    if(k == UserInput::UP){
                        sprite->Play("moveU1");
                        transform->velocity.y = -1;
                        transform->update();
                    }
                    else if(k == UserInput::LEFT){
                        sprite->Play("moveL1");
                        transform->velocity.x = -1;
                        transform->update();
                    }
                    else if(k == UserInput::DOWN){
                        sprite->Play("moveD1");
                        transform->velocity.y = 1;
                        transform->update();
                    }
                    else if(k == UserInput::RIGHT){
                        sprite->Play("moveR1");
                        transform->velocity.x = 1;
                        transform->update();
                    }
                    else if(k == UserInput::UP_UP){
                        sprite->Play("idleU1");
                        transform->velocity.Zero();
                        transform->update();
                    }
                    else if(k == UserInput::LEFT_UP){
                        sprite->Play("idleL1");
                        transform->velocity.Zero();
                        transform->update();
                    }
                    else if(k == UserInput::DOWN_UP){
                        sprite->Play("idleD1");
                        transform->velocity.Zero();
                        transform->update();
                    }
                    else if(k == UserInput::RIGHT_UP){
                        sprite->Play("idleR1");
                        transform->velocity.Zero();
                        transform->update();
                    }
                }
                Game::otherUserInput = UserInput::DUMMY;
            }
        }    
    }
};    