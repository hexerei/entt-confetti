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
#include "Game.hpp"

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

    // add and initialize scene
    m_scene = new Scene();
    m_running = m_scene->init();

    #ifdef DEBUG
        if (m_running) {
            std::cout << "Scene initialized..." << std::endl;
        } else {
            std::cerr << "Could not initialize Scene..." << std::endl;
        }
    #endif

    return m_running;
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

    m_scene->handleEvents(m_event);
}

/**
 * @brief update scene
 */
void Game::update()
{
    m_scene->update();
}

/**
 * @brief render scene
 */
void Game::render()
{
    SDL_RenderClear(m_renderer);

    m_scene->render(m_renderer);

    SDL_RenderPresent(m_renderer);
}

/**
 * @brief free assets and release subsystems
 */
void Game::clean()
{
    m_running = false;

    m_scene->clean();

    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
    std::cout << "Subsystems released!" << std::endl;
}