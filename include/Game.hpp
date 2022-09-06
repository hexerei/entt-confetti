/**
 * @file Game.hpp
 * @author Daniel Vorhauer (daniel@hexerei.net)
 * @brief This class wraps all SDL2 calls to initialize SDL2, create the window,
 * create the renderer and assets used in the scene, and implements the main
 * game loop functions to handle keyboard events, update all assets and render
 * them to the window.
 * @version 0.3
 * @date 2022-09-06
 *
 * @copyright Copyright (c) 2022 Daniel Vorhauer
 *
 */
#pragma once

#include <SDL2/SDL.h>
#include "Scene.hpp"
#include "config.hpp"

/**
 * @brief Game class as wrapper to SDL2 functionality
 */
class Game
{
public:
    // constructor and destructure defined inline
    Game() : m_running(false), m_window(nullptr), m_renderer(nullptr), m_scene(nullptr) {}
    ~Game() { clean(); }

    // initialize SDL2, create window and renderer
    bool init(const char* title = "SDL2 Window",
        int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED,
        int w = config::WINDOW_WIDTH, int h = config::WINDOW_HEIGHT,
        bool fullscreen = false);

    // game loop functions to handle events, update assets and render them
    void handleEvents();
    void update();
    void render();

    // clean up resources at game end
    void clean();

    // check if game is still running
    inline bool running() { return m_running; }

private:
    // other private class members
    bool m_running = false;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Event m_event;
    Scene* m_scene;
};