# Confetti Party using EnTT
Sample programm in C++ using SDL2 and EnTT libraries.

## Details

This sample programm was created as a starting point for developing applications in C++ using SDL2 and EnTT libraries.
Specifically it shows the most essential usage of the [Entity Component System](https://en.wikipedia.org/wiki/Entity_component_system) provided by the EnTT library, using small data structs as components. Although Entity and Component are used here, the System is not implemented as separate function, but included in the update() and render() functions of the Game class.

Most code repositories that I found implementing EnTT as their ECS base, actually had rather complex components, which I found to be overloaded with functionality and not matching the raw data I would have expected to see in a component, while functionality should be implemented by systems, in my humble opinion.

I hope this project might serve as a useful resource to others who are perhaps new to C++ and EnTT, and can not find simple implementation templates as a starting point for own projects.

## Prerequisites

EnTT is included as a submodule in this repository, if you clone the repository with the --recursive flag:

```bash
git clone --recursive https://github.com/hexerei/entt-confetti.git
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

This project uses the G++ compiler and GNU Make to build the desired target, but can also be buildt and debugged in Visual Studio Code.

### Building from the terminal

You will find a simple makefile, that allows quick adaption of program name, compiler flags and included libraries. All the other magic hapens in the included common.mk makefile, which auto adds all your sources, provides multi-platform support, and allows building to separate debug and release folders, where debug is the default.

Calling `make` without paramaters, or `make debug` or `make all` will build the debug version for your target environment into the `bin/debug` folder.

Calling `make run` will build the debug version and execute the target program file for fast testing. The program file is executed in the projects root directory, so no need to copy assets into the build folders.

Calling `make release` will build the release version without debug information, and optimized for size.

Calling `make clean` will remove the program, all object files and other output created from the `bin/debug` and the `bin/release` folders.

### Building from Visual Studio Code

For your convenience you will find a `.vscode` folder in the repository, which includes the `tasks.json` to build the solution from within VSCode and `launch.json` to execute or debug the solution using the Run menu.

Note: The target application is named `main` in the launch and tasks JSON settings files, in contrary to the target name `confetti` defined in the makefile, which is easier to modify. You can still change this in the JSON files, if desired.

## External Libraries

The only libraries used in the current code stack are SDL2 and EnTT. But makefiles include reference to SDL2_image, SDL2_mixer and SDL2_ttf as a good starting point to continue your own journey adding images, sounds and fonts.

### EnTT
[EnTT](https://github.com/skypjack/entt) is a header-only, tiny and easy to use library for game programming and much more written in modern C++. It provides an [Enitity Component System](https://en.wikipedia.org/wiki/Entity_component_system) that is the focus of this project.

### SDL2
[SDL2](https://www.libsdl.org) (Simple DirectMedia Layer) is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. Latest release can be found at [SDL Releases](https://github.com/libsdl-org/SDL/releases) on libsdl-org's GitHub page.

#### SDL2_image
[SDL2 Image](https://github.com/libsdl-org/SDL_image/releases) is a simple library to load images of various formats as SDL surfaces. It can load BMP, GIF, JPEG, LBM, PCX, PNG, PNM (PPM/PGM/PBM), QOI, TGA, XCF, XPM, and simple SVG format images. AVIF, JPEG-XL, TIFF, and WebP images can be loaded, depending on build options.

#### SDL2_ttf
[SDL2 TTF](https://github.com/libsdl-org/SDL_ttf/releases) is a wrapper around the FreeType and Harfbuzz libraries, allowing you to use TrueType fonts to render text in SDL applications.

#### SDL2_mixer
[SDL2 Mixer](https://github.com/libsdl-org/SDL_mixer/releases) is a simple multi-channel audio mixer. It supports 8 channels of 16 bit stereo audio, plus a single channel of music. It can load FLAC, MP3, Ogg, VOC, and WAV format audio. It can also load MIDI, MOD, and Opus audio, depending on build options.
