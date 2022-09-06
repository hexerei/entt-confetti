/**
 * @file components.hpp
 * @author Daniel Vorhauer (daniel@hexerei.net)
 * @brief Header only implementation of the components assignable to entities.
 * @version 0.3
 * @date 2022-09-06
 *
 * @copyright Copyright (c) 2022 Daniel Vorhauer
 *
 */
#pragma once
#include <SDL2/SDL.h>

// position component
struct Position
{
    float x;    // x position on screen
    float y;    // y position on screen

    // default constructors
    Position() = default;
    Position(const Position&) = default;
    // constructor to initialize component when adding it to entity
    Position(float px, float py)
        : x(px), y(py) {};
};

// velocity component
struct Velocity
{
    float dx;   // x velocity
    float dy;   // y velocity

    // default constructors
    Velocity() = default;
    Velocity(const Velocity&) = default;
    // constructor to initialize component when adding it to entity
    Velocity(float vx, float vy)
        : dx(vx), dy(vy) {};
};

// color component
struct Color
{
    u_char r;   // red color component
    u_char g;   // green color component
    u_char b;   // blue color component
    u_char a;   // transparency color component

    // default constructors
    Color() = default;
    Color(const Color&) = default;
    // constructor to initialize component when adding it to entity
    Color(u_char cr, u_char cg, u_char cb)
        : r(cr), g(cg), b(cb), a(255) {};
    Color(u_char cr, u_char cg, u_char cb, u_char ca)
        : r(cr), g(cg), b(cb), a(ca) {};
};
