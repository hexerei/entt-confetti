#
# included from makefile
# Cross Platform - compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# Made for use of SDL2 (http://www.libsdl.org):
# Linux:
#   apt-get install libsdl2-dev
# Mac OS X:
#   brew install sdl2
# MSYS2:
#   pacman -S mingw-w64-i686-SDL2
#

##---------------------------------------------------------------------
## DEFAULTS CONFIGURATION
##---------------------------------------------------------------------

SHELL = /bin/sh
RM=rm -rf
UNAME_S := $(shell uname -s)

.SUFFIXES:
.SUFFIXES: .cpp .o

CC=gcc
CXX=g++

OUT = bin
SRCDIR = src
INCDIR = include
ENTT_DIR = vendor/entt/src

vpath %.cpp $(SRCDIR)
vpath %.hpp $(INCDIR):$(ENTT_DIR)
vpath %.h $(INCDIR):$(ENTT_DIR)

CXXFLAGS += -std=c++17 -I. -I$(SRCDIR) -I$(INCDIR) -I$(ENTT_DIR)

ifndef SOURCES
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
endif


##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux)
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL -ldl `sdl2-config --libs`
	CXXFLAGS += `sdl2-config --cflags`
	CFLAGS = $(CXXFLAGS)
	LDFLAGS = $(LIBS)
endif

ifeq ($(UNAME_S), Darwin)
	ECHO_MESSAGE = "macOS"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo `sdl2-config --libs`
	LIBS += -L/usr/local/lib
	CXXFLAGS += `sdl2-config --cflags`
	CXXFLAGS += -I/usr/local/include
	CFLAGS = $(CXXFLAGS)
	LDFLAGS = $(LIBS)
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "Windows"
	LIBS += -lgdi32 -lopengl32 -limm32 `pkg-config --static --libs sdl2`
	CXXFLAGS += `pkg-config --cflags sdl2`
	CFLAGS = $(CXXFLAGS)
	LDFLAGS = $(LIBS)
endif

##---------------------------------------------------------------------
## BUILD RULES FOR DEBUG AND RELEASE
##---------------------------------------------------------------------

# check for release version
ifeq ($(MAKECMDGOALS),release)

OUT = bin/release
OBJS = $(addprefix $(OUT)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))

# compiling other source files.
$(OUT)/%.o: %.cpp $(DEPS)
	@mkdir -p $(OUT)
	$(CXX) -O3 -DNDEBUG $(CXXFLAGS) -c -o $@ $<

# linking the program.
$(PROG): $(OBJS)
	$(CXX) -o $(OUT)/$(PROG) $^ $(LIBS)

release: $(PROG)
	@echo Build complete for $(ECHO_MESSAGE) release version

# default to debug version
else

OUT = bin/debug
OBJS = $(addprefix $(OUT)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))

# compiling other source files.
$(OUT)/%.o: %.cpp $(DEPS)
	@mkdir -p $(OUT)
	$(CXX) -g -DDEBUG $(CXXFLAGS) -c -o $@ $<

# linking the program.
$(PROG): $(OBJS)
	$(CXX) -o $(OUT)/$(PROG) $^ $(LIBS)

debug: $(PROG)
	@echo Build complete for $(ECHO_MESSAGE) debug version

# run only executes debug version
run: debug
	./$(OUT)/$(PROG)

endif

##---------------------------------------------------------------------
## SHARED BUILD RULES
##---------------------------------------------------------------------

# top-level rule to create the program.
all: $(PROG)

# remove all objects created with make
killbin:
	@$(RM) bin
	@echo Removed bin directory and subfolders

cleanrelease:
	@$(RM) bin/release/*.o bin/release/$(PROG)
	@echo Cleaned bin/release directory

cleandebug:
	@$(RM) bin/debug/*.o bin/debug/$(PROG) bin/debug/*.dSYM
	@echo Cleaned bin/debug directory

clean: cleandebug cleanrelease

