#include "game.h"

Game *game = nullptr;
int main()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Race Game",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 640, false);
    while (game->running())
    {   
        //std::cout << game->count << std::endl;
        frameStart = SDL_GetTicks();
        game->handleEvents();
        // std::cout << 1 << std::endl;
        game->update();
        // std::cout << 2 << std::endl;
        game->render();
        // std::cout << 3 << std::endl;
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();
    return 0;
}