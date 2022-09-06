/*
Distributed using the MIT License

Copyright (c) 2022 Daniel Vorhauer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file main.cpp
 * @author Daniel Vorhauer (daniel@hexerei.net)
 * @brief This sample programm was created as a starting point for developing
 * applications in C++ using SDL2 and EnTT libraries. Specifically it shows the
 * most essential usage of the Entity Component System provided by the EnTT
 * library, using small data structs as position, velocity and color components,
 * to render and move 1000 colorful confettis on the screen.
 * @version 0.3
 * @date 2022-09-06
 *
 * @copyright Copyright (c) 2022 Daniel Vorhauer
 *
 */
#include <iostream>
#include <SDL2/SDL.h>
#include "Game.hpp"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error SDL Version 2.0.17+ is required
#endif

/**
 * @brief main function initiallizes Game class and runs game loop. Calling
 * SDL_Delay to reduce rendering rates and destress the CPU usage.
 *
 * @return int - 0 on success, as required by SDL2
 */
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
        return 1;

    }

    return 0;
}