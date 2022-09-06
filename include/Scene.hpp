/**
 * @file Scene.hpp
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
#pragma once

#include <SDL2/SDL.h>
#include <entt/entt.hpp>

/**
 * @brief The Scene class holds all assets to manage and render the visual
 * and non-visual entities within the displayed scene on screen
 */
class Scene
{
public:
    // constructor and destructor implemented inline
    Scene() = default;
    ~Scene() { clean(); };

    // initialize assets and entities
    bool init();

    // delegates to the game loop
    void handleEvents(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

    // clear registry and release resources
    void clean();

private:
    // EnTT registry to register and manage all entities
    entt::registry m_registry;
};