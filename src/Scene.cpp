/**
 * @file Scene.cpp
 * @author Daniel Vorhauer (daniel@hexerei.net)
 * @brief This class wraps all assets used in the scene, and is a delegate for
 * game loop functions to handle keyboard events, update all assets and render
 * them to the window.
 * @version 0.3
 * @date 2022-09-06
 *
 * @copyright Copyright (c) 2022 Daniel Vorhauer
 *
 */
#include <random>
#include <iostream>

#include "Scene.hpp"
#include "components.hpp"
#include "config.hpp"

// change to see more or less confetti on screen
constexpr int NUM_CONFETTI = 1000;

/**
 * @brief initialize all assets and entities used in the scene
 *
 * @return true if successfully initialized
 * @return false if initialization failed
 */
bool Scene::init()
{
    // initialize random distributors for color, position and velocity
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<u_char> distrgb(80, 255);
    std::uniform_int_distribution<float> distxpos(10, config::WINDOW_WIDTH - 10);
    std::uniform_int_distribution<float> distypos(10, config::WINDOW_HEIGHT - 10);
    std::uniform_int_distribution<float> distvel(1, 5);

    // create entities, with position, velocity and color components
    for(int i = 0; i < NUM_CONFETTI; ++i) {
        // create new entity
        const auto entity = m_registry.create();
        // add components with random position, velocity and color
        m_registry.emplace<Position>(entity, distxpos(eng), distypos(eng));
        float dx = (i % 2) ? distvel(eng) : -distvel(eng);
        float dy =  (i % 3) ? distvel(eng) : -distvel(eng);
        m_registry.emplace<Velocity>(entity, dx, dy);
        m_registry.emplace<Color>(entity, distrgb(eng), distrgb(eng), distrgb(eng));
    }

    return true;
}

void Scene::handleEvents(SDL_Event& event)
{
    // velocity to add to all velocities
    Velocity addvel{0.f,0.f};

    // calculate velocity boost depending on key
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
        case SDLK_LEFT:
            addvel.dx--;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            addvel.dx++;
            break;
        case SDLK_w:
        case SDLK_UP:
            addvel.dy--;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            addvel.dy++;
            break;
        case SDLK_SPACE:
            {
                // sudden halt to all confetti
                auto view = m_registry.view<Velocity>();
                for (auto [entity, vel]: view.each()) {
                    vel.dx = 0.f;
                    vel.dy = 0.f;
                }
            }
            break;
        default:
            break;
        }
    }
    /*
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
        case SDLK_LEFT:
            addvel.dx++;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            addvel.dx--;
            break;
        case SDLK_w:
        case SDLK_UP:
            addvel.dy++;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            addvel.dy--;
            break;
        default:
            break;
        }
    }
*/
    if (addvel.dx != 0.f || addvel.dy != 0.f)
    {
        // update velocity on all entities
        auto view = m_registry.view<Velocity>();
        for (auto [entity, vel]: view.each()) {
            vel.dx += addvel.dx;
            vel.dy += addvel.dy;
        }
    }
}

/**
 * @brief update entities positions on screen
 */
void Scene::update()
{
    // update entities positions
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
 * @brief renderr entities on screen
 *
 * @param renderer - the renderer passed from the game loop
 */
void Scene::render(SDL_Renderer* renderer)
{
    // draw entities
    auto view = m_registry.view<Position, Color>();
    for (auto [entity, pos, col]: view.each()) {
        //std::cout << "Draw confetti at (" << pos.x << "," << pos.y << ")" << std::endl;
        SDL_Rect dRect = {(int)pos.x, (int)pos.y, 4, 4};
        SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
        SDL_RenderFillRect(renderer, &dRect);
    }

    // reset color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

/**
 * @brief release all entities, components and assets
 */
void Scene::clean()
{
    // clear all entities and components
    m_registry.clear();
}
