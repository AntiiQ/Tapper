.PHONY: all clean

# Define required raylib variables
PROJECT_NAME       ?= main
BUILD_MODE         ?= DEBUG
RAYLIB_VERSION     ?= 4.5.0
RAYLIB_PATH        ?= C:/raylib/raylib
COMPILER_PATH      ?= C:/raylib/w64devkit/bin
EXT				   ?= .exe
PLATFORM           ?= PLATFORM_DESKTOP
# One of PLATFORM_DESKTOP, PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB

DESTDIR ?= /usr/local
RAYLIB_INSTALL_PATH ?= $(DESTDIR)/lib
RAYLIB_H_INSTALL_PATH ?= $(DESTDIR)/include


PLATFORM_OS=WINDOWS
export PATH := $(COMPILER_PATH):$(PATH)

RAYLIB_RELEASE_PATH 	?= $(RAYLIB_PATH)/src
EXAMPLE_RUNTIME_PATH   ?= $(RAYLIB_RELEASE_PATH)

# NOTE: define g++ compiler if using C++
CC = gcc

MAKE = mingw32-make

# Define compiler flags:
#  -O0                  defines optimization level (no optimization, better for debugging)
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -s                   strip unnecessary data from build -> do not use in debug builds
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -std=gnu99           defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
#  -D_DEFAULT_SOURCE    use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
CFLAGS += -Wall -std=c99 -D_DEFAULT_SOURCE 

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -s -O1
endif

INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -I./include

LDFLAGS = -L. -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src

LDFLAGS += $(RAYLIB_PATH)/src/raylib.rc.data
ifeq ($(BUILD_MODE),RELEASE)
    # -Wl,--subsystem,windows hides the console window
    LDFLAGS += -Wl,--subsystem,windows
endif

LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
# Required for physac examples
#LDLIBS += -static -lpthread

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MAKEFILE_PARAMS = $(PROJECT_NAME)


all:
	$(MAKE) $(MAKEFILE_PARAMS)

$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_NAME)$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

clean:
	del *.o *.exe /s

	@echo Cleaning done