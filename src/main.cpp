#include <iostream>
#include <SDL2/SDL.h>
#include "Game.hpp"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error SDL Version 2.0.17+ is required
#endif

int main(int, char**)
{
    Uint32 frameStart;
    Uint32 frameTime;

    Game* game = new Game();

    if (game->init("EnTT Confetti Party"))
    {
        // game loop
        while (game->running())
        {
            frameStart = SDL_GetTicks();

            game->handleEvents();
            game->update();
            game->render();

            // delay rendering to not overstress CPU
            frameTime = SDL_GetTicks() - frameStart;
            if (config::FRAME_DELAY > frameTime)
                SDL_Delay(config::FRAME_DELAY - frameTime);
        }

        // Cleanup
        game->clean();

    } else {

        std::cout << "Could not start game! Check logs for details..." << std::endl;

    }

    return 0;
}