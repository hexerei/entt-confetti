#pragma once

#include <SDL2/SDL.h>
#include <entt/entt.hpp>
#include "config.hpp"

class Game
{
public:
    Game() : m_running(false), m_window(nullptr), m_renderer(nullptr) {}
    ~Game() { clean(); }

    bool init(const char* title = "SDL2 Window",
        int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED,
        int w = config::WINDOW_WIDTH, int h = config::WINDOW_HEIGHT,
        bool fullscreen = false);

    void handleEvents();
    void update();
    void render();
    void clean();

    inline bool running() { return m_running; }

private:
    void initCustom();
    bool m_running = false;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Event m_event;
    entt::registry m_registry;
};