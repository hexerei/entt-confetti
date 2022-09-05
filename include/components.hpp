#pragma once
//#include "config.hpp"
#include <SDL2/SDL.h>

struct Position {
    float x;
    float y;

    Position() = default;
    Position(const Position&) = default;
    Position(float px, float py)
        : x(px), y(py) {};
};

struct Velocity {
    float dx;
    float dy;

    Velocity() = default;
    Velocity(const Velocity&) = default;
    Velocity(float vx, float vy)
        : dx(vx), dy(vy) {};
};

struct Color {
    u_char r;
    u_char g;
    u_char b;
    u_char a;

    Color() = default;
    Color(const Color&) = default;
    Color(u_char cr, u_char cg, u_char cb)
        : r(cr), g(cg), b(cb), a(255) {};
    Color(u_char cr, u_char cg, u_char cb, u_char ca)
        : r(cr), g(cg), b(cb), a(ca) {};
};


/*
struct Transform {
    std::uint32_t height = config::TILE_SIZE;
    std::uint32_t width = config::TILE_SIZE;
    std::uint32_t scale = 1;
    std::uint32_t speed = 3;
};

struct Sprite {
    bool animated = false;
    std::uint32_t frames = 0;
    std::uint32_t speed = 100;
    std::uint32_t frame_index = 0;
    std::uint32_t texture_id = 0;
    std::uint32_t src_x = 0;
    std::uint32_t src_y = 0;
    std::uint32_t height = config::TILE_SIZE;
    std::uint32_t width = config::TILE_SIZE;
};
*/