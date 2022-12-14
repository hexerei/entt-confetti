# Confetti Party using EnTT
Sample programm in C++ using SDL2 and EnTT libraries.

![Confetti Party Preview](https://www.hexerei-software.de/public/assets/github/entt-confetti/entt-confetti.jpg)

## Details

This sample programm was created as a starting point for developing applications in C++ using SDL2 and EnTT header-only
libraries. Specifically it shows the most essential usage of the [Entity Component System](https://en.wikipedia.org/wiki/Entity_component_system)
provided by the EnTT library, using small data structs as position, velocity and color components, to
**render and move 1000 colorful confettis** on the screen. Although *Entity* and *Component* are used here, the *System*
is not implemented as separate functions, but included in the update() and render() functions of the `Scene` class.

Most code repositories that I found implementing EnTT as their ECS base, actually had rather complex components, which
I found to be overloaded with functionality and not matching the raw data I would have expected to see in a component,
while functionality should be implemented by systems, in my humble opinion.

I hope this project might serve as a useful resource to others who are perhaps new to C++ and EnTT, and can not find
simple implementation templates as a starting point for own projects.

### Usage

You can just medidate and watch the confetti fly around, but if you want to be more interactive, use the arrow keys,
or A, W, S, D keys to blow some wind in chosen direction and make the confetti change direction. And if it all gets too
fast, just press the spacebar to freeze the confetti in position, and then gently press direction keys again, to give it
some velocity again. Beware, you could be doing this all day ;)

### Implementation

The `Game` class encapsulates all the SDL2 specifics to initialize SDL create a window, create the renderer, handle events and perform the actual rendering on screen.

The `Scene` class then actually uses EnTT to create the confetti entities, with their Position, Velocity and Color components. Updates their position in the `update()` function, and then renders them on screen in the `render()` function.

The Position, Velocity and Color components are defined in the `components.hpp` in the `include` directory.

This shows the most basic usage of the `entt::registry` and how to create entities, adding components to them, and how
to use `views` to retreive the data components of interest for modification.

#### Entities

Entities are just unique identifiers of type `entt::entity` which are used to group components for a single entity. You
retreive the entity identifier from the `entt::registry` as so:

```cpp
entt::registry m_registry;
const auto entity = m_registry.create();
```

#### Components

Components are just pure data structures, that are grouped to specific usage, and then can be added to an entity. To
define a component, just create a named struct with the desired elements, and ideally create constructors, that allow
initializing your struct with data, i.e.:

```cpp
// position component
struct Position
{
    float x;    // x position on screen
    float y;    // y position on screen

    // default constructor
    Position() = default;
    // initialize component when adding it to entity
    Position(float px, float py)
        : x(px), y(py) {};
};
```

You can then add such a component to an existing entity:

```cpp
m_registry.emplace<Position>(entity, 10.f, 10.f);
```
If your structs don't have a constructor to initialize their values, you may as well initialize them after adding them
to the entity, as the `emplace` call returns the component itself.

```cpp
auto& pos = m_registry.emplace<Position>(entity);
pos.x = 1.0f;
pos.y = 1.0f;
```

Components can be assigned to, or removed from entities at any time.

#### Systems

Systems then usually are just functions or classes, that work with the components of one or more entities, where as you
usually do your modifications on all components, regardless of the entity. As the components are packed in memory
optimized format, processing over a set of components is blazing fast.

There are several ways to access and group components, let me just hightlight the essential way of creating a view of
components from all entities, iterate over them and modify them.

Iterating over a single component type...

```cpp
auto view = m_registry.view<Position>();
for (auto [entity, pos]: view.each()) {
    pos.x = 0.f;
    pos.y = 0.f;
}
```

...or iterating over a set of components:

```cpp
auto view = m_registry.view<Position, Velocity>();
for (auto [entity, pos, vel]: view.each()) {
    pos.x += vel.dx;
    pos.y += vel.dy;
}
```

For a more in-depth insight into the entity-component systems functionality from the EnTT header-only library, check out
their [Crash Course: entity-component system](https://github.com/skypjack/entt/blob/master/docs/md/entity.md).

## Prerequisites

EnTT is included as a submodule in this repository, if you clone the repository with the --recursive flag:

```bash
git clone --recursive https://github.com/hexerei/entt-confetti.git
```

If you have already cloned the repository without the recursvie flag, you can still retreive the submodules. Within you project folder, run:

```bash
git submodule update --init --recursive
```

SDL2 can be installed easily with following commands depending on your platform:

- Linux using apt:
  ```bash
  apt-get install libsdl2-dev
  ```
- Mac OS X using [Homebrew](https://brew.sh):
  ```bash
  brew install sdl2
  ```
- Windows using [MSYS2](https://www.msys2.org) and Pacman:
  ```bash
  pacman -S mingw-w64-i686-SDL2
  ```

## Building and Running

This project uses the G++ compiler and GNU Make to build the desired target, but can also be buildt and debugged in
Visual Studio Code.

### Building from the terminal

You will find a simple makefile, that allows quick adaption of program name, compiler flags and included libraries.
All the other magic hapens in the included common.mk makefile, which auto adds all your sources, provides multi-platform
support, and allows building to separate debug and release folders, where debug is the default.

Calling `make` without paramaters, or `make debug` or `make all` will build the debug version for your target
environment into the `bin/debug` folder.

Calling `make run` will build the debug version and execute the target program file for fast testing. The program file
is executed in the projects root directory, so no need to copy assets into the build folders.

Calling `make release` will build the release version without debug information, and optimized for size.

Calling `make clean` will remove the program, all object files and other output created from the `bin/debug` and the
`bin/release` folders.

### Building from Visual Studio Code

For your convenience you will find a `.vscode` folder in the repository, which includes the `tasks.json` to build the
solution from within VSCode and `launch.json` to execute or debug the solution using the Run menu.

Note: The target application is named `main` in the launch and tasks JSON settings files, in contrary to the target name
`confetti` defined in the makefile, which is easier to modify. You can still change this in the JSON files, if desired.

## External Libraries

The only libraries used in the current code stack are SDL2 and EnTT. But makefiles include reference to SDL2_image,
SDL2_mixer and SDL2_ttf as a good starting point to continue your own journey adding images, sounds and fonts.

### EnTT
[EnTT](https://github.com/skypjack/entt) is a header-only, tiny and easy to use library for game programming and much
more written in modern C++. It provides an [Enitity Component System](https://en.wikipedia.org/wiki/Entity_component_system)
which is the focus of this project.

### SDL2
[SDL2](https://www.libsdl.org) (Simple DirectMedia Layer) is a cross-platform development library designed to provide
low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. Latest release can
be found at [SDL Releases](https://github.com/libsdl-org/SDL/releases) on libsdl-org's GitHub page.

#### SDL2_image
[SDL2 Image](https://github.com/libsdl-org/SDL_image/releases) is a simple library to load images of various formats
as SDL surfaces. It can load BMP, GIF, JPEG, LBM, PCX, PNG, PNM (PPM/PGM/PBM), QOI, TGA, XCF, XPM, and simple SVG
format images. AVIF, JPEG-XL, TIFF, and WebP images can be loaded, depending on build options.

#### SDL2_ttf
[SDL2 TTF](https://github.com/libsdl-org/SDL_ttf/releases) is a wrapper around the FreeType and Harfbuzz libraries,
allowing you to use TrueType fonts to render text in SDL applications.

#### SDL2_mixer
[SDL2 Mixer](https://github.com/libsdl-org/SDL_mixer/releases) is a simple multi-channel audio mixer. It supports 8
channels of 16 bit stereo audio, plus a single channel of music. It can load FLAC, MP3, Ogg, VOC, and WAV format audio.
It can also load MIDI, MOD, and Opus audio, depending on build options.

## License

Code and documentation Copyright (c) 2022 Daniel Vorhauer.

Code released under
[the MIT license](https://github.com/hexerei/entt-confetti/blob/main/LICENSE).

Documentation released under
[CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).

