/**
 * @file Game.cpp
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
#include <iostream>
#include <random>

#include "Game.hpp"
#include "config.hpp"
#include "components.hpp"

/**
 * @brief Initialize all subsystems and create game window
 *
 * This is our main game class, where all the SDL subsystems are
 * managed and the main game loop is run.
 *
 * @param title title for the window. Default: "SDL2 Window"
 * @param x x position on screen. Default centered.
 * @param y y position on screen. Default centered.
 * @param w window width. Default as stated in config.
 * @param h window height. Default as stated in config.
 * @param fullscreen open window in fullscreen. Default false.
 * @return true if game is initialized and running
 * @return false if game could not be initialized
 */
bool Game::init(const char* title, int x, int y, int w, int h, bool fullscreen)
{
    m_running = false;

    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL. SDL_Error: %s", SDL_GetError());
        #ifdef DEBUG
            std::cerr << "Could not initialize SDL. SDL_Error: " << SDL_GetError() << std::endl;
        #endif
        return false;
    }

    #ifdef DEBUG
        std::cout << "Subsystems initialized..." << std::endl;
    #endif

    // create window
    Uint32 flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
    /*SDL_WindowFlags window_flags = (SDL_WindowFlags)(
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | flags
    );*/
    m_window = SDL_CreateWindow(title, x, y, w, h, flags); //window_flags);
    if (m_window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create Window. SDL_Error: %s", SDL_GetError());
        #ifdef DEBUG
            std::cerr << "Could not create Window. SDL_Error: " << SDL_GetError() << std::endl;
        #endif
        return false;
    }

    #ifdef DEBUG
        std::cout << "Window created..." << std::endl;
    #endif

    // create SDL_Renderer instance
    m_renderer = SDL_CreateRenderer(m_window, -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
    );
    if (m_renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create Renderer. SDL_Error: %s", SDL_GetError());
        #ifdef DEBUG
            std::cerr << "Could not create Renderer. SDL_Error: " << SDL_GetError() << std::endl;
        #endif
        return false;
    }

    #ifdef DEBUG
        std::cout << "Renderer created..." << std::endl;
        SDL_RendererInfo info;
        SDL_GetRendererInfo(m_renderer, &info);
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Current SDL_Renderer: %s", info.name);
    #endif

    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);

    m_running = true;

    initCustom();

    return m_running;
}

/**
 * @brief initialize entites for the scene
 */
void Game::initCustom()
{
    // initialize random distributors for color, position and velocity
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<u_char> distrgb(80, 255);
    std::uniform_int_distribution<float> distxpos(10, config::WINDOW_WIDTH - 10);
    std::uniform_int_distribution<float> distypos(10, config::WINDOW_HEIGHT - 10);
    std::uniform_int_distribution<float> distvel(1, 5);

    // create entities, with position, velocity and color components
    for(int i = 0; i < 1000; ++i) {
        // create new entity
        const auto entity = m_registry.create();
        // add components with random position, velocity and color
        m_registry.emplace<Position>(entity, distxpos(eng), distypos(eng));
        float dx = (i % 2) ? distvel(eng) : -distvel(eng);
        float dy =  (i % 3) ? distvel(eng) : -distvel(eng);
        m_registry.emplace<Velocity>(entity, dx, dy);
        m_registry.emplace<Color>(entity, distrgb(eng), distrgb(eng), distrgb(eng));
    }
}

/**
 * @brief handle events to check if window was closed
 */
void Game::handleEvents()
{
    SDL_PollEvent(&m_event);
	switch (m_event.type)
	{
	case SDL_QUIT:
		m_running = false;
		break;

    case SDL_WINDOWEVENT:
        if (m_event.window.event == SDL_WINDOWEVENT_CLOSE
            && m_event.window.windowID == SDL_GetWindowID(m_window))
            m_running = false;
        break;

	case SDL_KEYDOWN:
		if (m_event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_running = false;
		}
		break;

	default:
		break;
	}
}

/**
 * @brief update all game entities
 */
void Game::update()
{
    // update entities
    auto view = m_registry.view<Position, Velocity>();
    for (auto [entity, pos, vel]: view.each()) {
        //std::cout << "Pos (" << pos.x << "," << pos.y << ") moved to ";
        if (pos.x >= config::WINDOW_WIDTH || pos.x <= 0)
            vel.dx *= -1.f;
        pos.x += vel.dx;
        if (pos.y >= config::WINDOW_HEIGHT || pos.y <= 0)
            vel.dy *= -1.f;
        pos.y += vel.dy;
        //std::cout << "Pos (" << pos.x << "," << pos.y << ")" << std::endl;
    }
}

/**
 * @brief render game entities
 */
void Game::render()
{
    SDL_RenderClear(m_renderer);

    // draw entities
    auto view = m_registry.view<Position, Color>();
    for (auto [entity, pos, col]: view.each()) {
        //std::cout << "Draw point at (" << pos.x << "," << pos.y << ")" << std::endl;
        SDL_Rect dRect = {(int)pos.x, (int)pos.y, 4, 4};
        SDL_SetRenderDrawColor(m_renderer, col.r, col.g, col.b, col.a);

        //SDL_RenderDrawPoint(m_renderer, pos.x, pos.y);
        SDL_RenderFillRect(m_renderer, &dRect);
        //SDL_RenderDrawRect(m_renderer, &dRect);
    }
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    SDL_RenderPresent(m_renderer);
}

/**
 * @brief free assets and release subsystems
 */
void Game::clean()
{
    m_running = false;

    m_registry.clear();

    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
    std::cout << "Subsystems released!" << std::endl;
}