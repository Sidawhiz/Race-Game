#include "game.h"
#include "TextureManager.h"
#include <sstream>
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

SDL_Renderer *Game::ren = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent *> Game::colliders;

Map* map;

Manager manager;

auto& Player(manager.addEntity());
auto& wall(manager.addEntity());
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    }
    win = SDL_CreateWindow("game", xpos, ypos, width, height, flags);
    if (win == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
    }
    ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == NULL)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
    }
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    isRunning = true;

    map = new Map();

    Player.addComponent<TransformComponent>(50,50);
    Player.addComponent<SpriteComponent>("Assets/luigi.png");
    Player.addComponent<Controller>();
    Player.addComponent<ColliderComponent>("player");
    // Player.getComponent<TransformComponent>().setVelocity(1,0);

    wall.addComponent<TransformComponent>(100,100,32,5,8);
    wall.addComponent<SpriteComponent>("Assets/bg.png");
    wall.addComponent<ColliderComponent>("wall");

    tile0.addComponent<TileComponent>(200,200,32, 32, 3);
    tile0.addComponent<ColliderComponent>("tile0");
    tile1.addComponent<TileComponent>(250,250,32, 32, 3);
    tile1.addComponent<ColliderComponent>("tile1");
    tile2.addComponent<TileComponent>(300,300,32, 32, 3);
    tile2.addComponent<ColliderComponent>("tile2");


}

void Game ::handleEvents()
{

    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update()
{
    //count++;
    manager.update();
    //Player.getComponent<TransformComponent>().position.Add(Vector2D(2,0));
    // if(Player.getComponent<TransformComponent>().position.x > 75.0f){
    //     Player.getComponent<SpriteComponent>().setTexture("Assets/bg.png");
    // }
    ColliderComponent a = Player.getComponent<ColliderComponent>();
    ColliderComponent b = wall.getComponent<ColliderComponent>();
    for(auto cc : colliders){
        if(Collision::coll(a,*cc)){
            // Player.getComponent<TransformComponent>().scale=1;
            // Player.getComponent<TransformComponent>().velocity*-1;
            std::cout << "Collision Detected" << std::endl;
        }
    }    
}

void Game::render()
{
    SDL_RenderClear(ren);
    //map->DrawMap();
    manager.draw();
    SDL_RenderPresent(ren);
}

void Game::clean()
{
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
    std::cout << "quit\n";
}
