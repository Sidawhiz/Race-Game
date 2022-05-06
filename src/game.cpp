#include "game.h"
#include "TextureManager.h"
#include <sstream>
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "UI.h"
#include <SDL2/SDL_mixer.h>

SDL_Renderer *Game::ren = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent *> Game::colliders;
std::map<std::string, TTF_Font *> Game::fonts;

bool Game::isRunning = false;

int Game::playerID = 0 ;
Vector2D Game::initialPos;
bool Game::GameOver = false;
bool Game::dead = false;
bool Game::restart = false;

Map* MAP;
Manager manager;

auto& Player(manager.addEntity());
auto& enemy(manager.addEntity());
auto &label(manager.addEntity());
auto &P1wonLabel(manager.addEntity());
auto &P2wonLabel(manager.addEntity());

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders,
    groupCollectibles
};

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

    MAP = new Map();

    Map::LoadMap();

    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    }

    Player.addComponent<TransformComponent>(40,40,40,40,1);
    Player.addComponent<SpriteComponent>("Assets/xx.png",true);
    Player.addComponent<Controller>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);

    enemy.addComponent<TransformComponent>(40,64,40,40,1);
    enemy.addComponent<SpriteComponent>("Assets/xx2.png",true);
    enemy.addComponent<ColliderComponent>("enemy");
    enemy.addComponent<EnemyController>();
    enemy.addGroup(groupEnemies);

    SDL_Color white = {255, 255, 255, 255};
    AddFont("Lobster", "Assets/Lobster.ttf", 22);
    label.addComponent<UI>(246, 5, "Lives left: 3", "Lobster", white);
    // Player.getComponent<TransformComponent>().setVelocity(1,0);

    // wall.addComponent<TransformComponent>(100,100,32,5,8);
    // wall.addComponent<SpriteComponent>("Assets/bg.png");
    // wall.addComponent<ColliderComponent>("wall");
    // wall.addGroup(groupMap);

    // tile0.addComponent<TileComponent>(200,200,32, 32, 3);
    // tile0.addComponent<ColliderComponent>("tile0");
    // tile1.addComponent<TileComponent>(250,250,32, 32, 3);
    // tile1.addComponent<ColliderComponent>("tile1");
    // tile2.addComponent<TileComponent>(300,300,32, 32, 3);
    // tile2.addComponent<ColliderComponent>("tile2");


}

auto &players(manager.getGroup(groupPlayers));
auto &tiles(manager.getGroup(groupMap));
auto &enemies(manager.getGroup(groupEnemies));
auto &collectibles(manager.getGroup(groupCollectibles));

void Game::AddTile(int id, int x, int y)
{
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id); // size of input tile
    // 1 = wall, 2 = bg , 3 = foodstall
    if (id >= 1 && id<=5 && id!=2)
    {
        tile.addComponent<ColliderComponent>("obstacle");
    }
    tile.addGroup(groupMap);
}

void Game::AddCollectible(int id, int x, int y)
{
    auto &collectibles(manager.addEntity());
    collectibles.addComponent<CollectibleComponent>(x, y, 32, 32, id);
    if (id == 2)
    {
        collectibles.addComponent<ColliderComponent>("collectible");
    }
    collectibles.addGroup(groupCollectibles);
    // collectibleStatus.push_back(std::make_pair(std::make_pair(x, y), true));
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
    label.getComponent<UI>().SetText("Lives Left", "Lobster");
    ColliderComponent a = Player.getComponent<ColliderComponent>();
    for(auto cc : colliders){
        if(cc->tag=="obstacle" && Collision::coll(a,*cc)){
            //Player.getComponent<TransformComponent>().scale=1;
            Player.getComponent<TransformComponent>().velocity*-1;
            std::cout << "Collision Detected" << std::endl;
        }
    }    
}

void Game::AddFont(std::string id, std::string path, int fontSize)
{
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font *Game::GetFont(std::string id)
{
    return fonts[id];
}


void Game::render()
{

    SDL_RenderClear(ren);
    
    //map->DrawMap();
    for(auto& t : tiles){
        t->draw();
        //sssstd::cout << "Bi" << std::endl;
    }
    for(auto& e : enemies){
        e->draw();
    }
    for(auto& p : players){
        p->draw();
    }

    for(auto& c : collectibles){
        c->draw();
    }

    label.draw();

    SDL_RenderPresent(ren);
}

void Game::clean()
{
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
    std::cout << "quit\n";
}
