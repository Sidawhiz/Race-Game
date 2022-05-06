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
Vector2D Game::crashVelocityPlayer;
Vector2D Game::crashVelocityEnemy;

Map* MAP;
Manager manager;

auto& Player(manager.addEntity());
auto& enemy(manager.addEntity());

auto &label(manager.addEntity());
auto &Himadrilabel(manager.addEntity());
auto &footballlabel(manager.addEntity());
auto &LHClabel(manager.addEntity());
auto &SAClabel(manager.addEntity());
auto &Nalandalabel(manager.addEntity());
auto &Nilgirilabel(manager.addEntity());
auto &blocklabel(manager.addEntity());
auto &Amullabel(manager.addEntity());
auto &Redlabel(manager.addEntity());

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
    initialPos = Player.getComponent<TransformComponent>().position;
    Player.addGroup(groupPlayers);

    enemy.addComponent<TransformComponent>(64,40,40,40,1);
    enemy.addComponent<SpriteComponent>("Assets/xx2.png",true);
    enemy.addComponent<ColliderComponent>("enemy");
    enemy.addComponent<EnemyController>();
    enemy.addGroup(groupEnemies);

    SDL_Color white = {255, 255, 255, 255};
    AddFont("Lobster", "Assets/Lobster.ttf", 22);
    SDL_Color black = {0, 0, 0, 255};
    AddFont("Lobster", "Assets/Lobster.ttf", 22);


    label.addComponent<UI>(246, 5, "Lives left: 3", "Lobster", white);
    Himadrilabel.addComponent<UI>(64, 165, "Himadri", "Lobster", white);
    LHClabel.addComponent<UI>(490, 96, "LHC", "Lobster", white);
    footballlabel.addComponent<UI>(586, 96, "LHC", "Lobster", white);
    SAClabel.addComponent<UI>(830, 96, "LHC", "Lobster", white);
    Nalandalabel.addComponent<UI>(1034, 96, "LHC", "Lobster", white);
    Nilgirilabel.addComponent<UI>(1184, 96, "LHC", "Lobster", white);
    blocklabel.addComponent<UI>(128, 647, "LHC", "Lobster", white);
    Amullabel.addComponent<UI>(426, 627, "LHC", "Lobster", black);
    Redlabel.addComponent<UI>(650, 627, "LHC", "Lobster", white);
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
    manager.refresh();
    manager.update();
    Vector2D playerpos = Player.getComponent<TransformComponent>().position;
    label.getComponent<UI>().SetText("Lives Left", "Lobster");
    Himadrilabel.getComponent<UI>().SetText("Himadri", "Lobster");
    LHClabel.getComponent<UI>().SetText("LHC", "Lobster");
    footballlabel.getComponent<UI>().SetText("Football", "Lobster");
    SAClabel.getComponent<UI>().SetText("SAC", "Lobster");
    Nalandalabel.getComponent<UI>().SetText("Nalanda", "Lobster");
    Nilgirilabel.getComponent<UI>().SetText("Nilgiri", "Lobster");
    blocklabel.getComponent<UI>().SetText("Blocks", "Lobster");
    Amullabel.getComponent<UI>().SetText("Amul", "Lobster");
    Redlabel.getComponent<UI>().SetText("Red Square", "Lobster");

    for(int i = 0; i<colliders.size(); i++){
        auto &cc = colliders[i];
        if(Collision::coll(*cc, Player.getComponent<ColliderComponent>())){
            if(cc->tag == "obstacle"){
                Player.getComponent<TransformComponent>().count = 30;
                Player.getComponent<TransformComponent>().crash = 1;
                //Player.getComponent<TransformComponent>().speed = 0;
                // Game::crashVelocityPlayer = Player.getComponent<TransformComponent>().velocity;
            }
        }
        if(Collision::coll(*cc, enemy.getComponent<ColliderComponent>())){
            if(cc->tag == "obstacle"){
                enemy.getComponent<TransformComponent>().count = 30;
                enemy.getComponent<TransformComponent>().crash = 1;
                //Player.getComponent<TransformComponent>().speed = 0;
                // Game::crashVelocityEnemy = enemy.getComponent<TransformComponent>().velocity;
            }
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
    Himadrilabel.draw();
    LHClabel.draw();
    footballlabel.draw();
    SAClabel.draw();
    Nalandalabel.draw();
    Nilgirilabel.draw();
    blocklabel.draw();
    Amullabel.draw();
    Redlabel.draw();

    SDL_RenderPresent(ren);
}

void Game::clean()
{
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
    std::cout << "quit\n";
}
