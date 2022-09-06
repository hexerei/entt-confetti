################################################
# `make run` to build and run the debug version
# `make all` or make debug makes the debug version
# `make release` to make the release version
################################################

PROG = confetti

CXXFLAGS = -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -Wformat
LIBS = -lSDL2_mixer -lSDL2_image -lSDL2_ttf

DEPS = config.hpp

include common.mk
