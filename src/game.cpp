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
std::vector<std::pair<std::pair<int, int>, bool>> Game::collectibleStatus1;
std::vector<std::pair<std::pair<int, int>, bool>> Game::collectibleStatus2;
std::map<std::string, TTF_Font *> Game::fonts;

bool Game::isRunning = false;

int Game::playerID = 0 ;
int Game::num_of_collectibles1 = 0;
int Game::num_of_collectibles2 = 0;
bool Game::GameOver = false;
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
auto &gameOverLabel(manager.addEntity());

auto &P1wonLabel(manager.addEntity());
auto &P2wonLabel(manager.addEntity());

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders,
    groupCollectibles1,
    groupCollectibles2
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

    //std::cout << collectibleStatus1.size() << std::endl;
    num_of_collectibles1 = collectibleStatus1.size();
    num_of_collectibles2 = collectibleStatus2.size();

    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    }

    Player.addComponent<TransformComponent>(40,40,40,40,1);
    Player.addComponent<SpriteComponent>("Assets/xx.png",true);
    Player.addComponent<Controller>();
    Player.addComponent<ColliderComponent>("player");
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

    gameOverLabel.addComponent<UI>(480, 360, "GAME OVER", "Lobster", white);

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
    P1wonLabel.addComponent<UI>(550, 450, "player 1 won!", "Lobster", white);
    P2wonLabel.addComponent<UI>(550, 450, "player 2 won!", "Lobster", white);
}

auto &players(manager.getGroup(groupPlayers));
auto &tiles(manager.getGroup(groupMap));
auto &enemies(manager.getGroup(groupEnemies));
auto &collectibles1(manager.getGroup(groupCollectibles1));
auto &collectibles2(manager.getGroup(groupCollectibles2));

void Game::AddTile(int id, int x, int y)
{
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id); // size of input tile
    // 1 = wall, 2 = bg , 3 = foodstall
    if (id==1 || id==3 || id==4)
    {
        tile.addComponent<ColliderComponent>("obstacle");
    }
    if(id == 7){
        tile.addComponent<ColliderComponent>("End");
    }
    tile.addGroup(groupMap);
}

void Game::AddCollectible(int id, int x, int y)
{
    if (id == 5)
    {
        auto &collectibles1(manager.addEntity());
        collectibles1.addComponent<CollectibleComponent>(x, y, 32, 32, id);
        collectibles1.addComponent<ColliderComponent>("collectible1");
        collectibles1.addGroup(groupCollectibles1);
        collectibleStatus1.push_back(std::make_pair(std::make_pair(x, y), true));
    }
    else if (id == 6)
    {
        auto &collectibles2(manager.addEntity());
        collectibles2.addComponent<CollectibleComponent>(x, y, 32, 32, id);
        collectibles2.addComponent<ColliderComponent>("collectible2");
        collectibles2.addGroup(groupCollectibles2);
        collectibleStatus2.push_back(std::make_pair(std::make_pair(x, y), true));
    }
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
    if(!GameOver){
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
                else if(cc->tag == "collectible1"){
                    std::cout << "Encountered collectible1" << std::endl;
                    int xp = cc->transform->position.x;
                    int yp = cc->transform->position.y;
                    for (int j = 0; j < collectibleStatus1.size(); j++)
                    {
                        if (collectibleStatus1[j].first == make_pair(xp, yp))
                        {
                            collectibleStatus1[j].second = false;
                        }
                    }
                    colliders.erase(colliders.begin() + i);
                    num_of_collectibles1--;
                    render();
                    break;
                }
                else if(cc->tag == "End"){
                    if(num_of_collectibles1 == 0){
                        GameOver = true;
                    }
                }

            }
            if(Collision::coll(*cc, enemy.getComponent<ColliderComponent>())){
                if(cc->tag == "obstacle"){
                    enemy.getComponent<TransformComponent>().count = 30;
                    enemy.getComponent<TransformComponent>().crash = 1;
                    std::cout << "Encountered obstacle" << std::endl;
                }
                else if(cc->tag == "collectible2"){
                    std::cout << "Encountered collectible2" << std::endl;
                    int xp = cc->transform->position.x;
                    int yp = cc->transform->position.y;
                    for (int j = 0; j < collectibleStatus2.size(); j++)
                    {
                        if (collectibleStatus2[j].first == make_pair(xp, yp))
                        {
                            collectibleStatus2[j].second = false;
                        }
                    }
                    colliders.erase(colliders.begin() + i);
                    num_of_collectibles2--;
                    render();
                    break;
                }
                else if(cc->tag=="End"){
                    //std::cout << "End line " << num_of_collectibles2 << std::endl;
                    if(num_of_collectibles2 == 0){
                        GameOver = true;
                    }
                }
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
    if(!GameOver){

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

        for(auto& c : collectibles1){
            bool drawable = true;
            for (int j = 0; j < collectibleStatus1.size(); j++)
            {
                if (c->getComponent<TransformComponent>().position.x == collectibleStatus1[j].first.first and c->getComponent<TransformComponent>().position.y == collectibleStatus1[j].first.second)
                {
                    if (!collectibleStatus1[j].second)
                    {
                        drawable = false;
                    }
                }
            }
            if (drawable)
            {
                c->draw();
            }
        }

        for(auto& c : collectibles2){
            bool drawable = true;
            for (int j = 0; j < collectibleStatus2.size(); j++)
            {
                if (c->getComponent<TransformComponent>().position.x == collectibleStatus2[j].first.first and c->getComponent<TransformComponent>().position.y == collectibleStatus2[j].first.second)
                {
                    if (!collectibleStatus2[j].second)
                    {
                        drawable = false;
                    }
                }
            }
            if (drawable)
            {
                c->draw();
            }
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
    else{
        SDL_RenderClear(ren);
        for(auto& t : tiles){
            t->draw();
        }
        gameOverLabel.draw();
        if(num_of_collectibles1==0){
            P1wonLabel.draw();
        }
        else if(num_of_collectibles2==0){
            P2wonLabel.draw();
        }
        SDL_RenderPresent(ren);
    }    
}

void Game::clean()
{
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
    std::cout << "quit\n";
}
