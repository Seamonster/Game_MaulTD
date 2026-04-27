# Windows VS Code build path using the raylib installer layout.
# The portable CMake build remains available for environments with CMake.

PROJECT_NAME ?= maultd
BUILD_MODE ?= DEBUG

RAYLIB_PATH ?= C:/raylib/raylib
COMPILER_PATH ?= C:/raylib/w64devkit/bin
override CXX := $(COMPILER_PATH)/g++.exe
export PATH := $(COMPILER_PATH):$(PATH)

ifeq ($(BUILD_MODE),DEBUG)
    CONFIG_DIR := debug
    MODE_FLAGS := -g -O0 -DDEBUG
else
    CONFIG_DIR := release
    MODE_FLAGS := -O2 -DNDEBUG
endif

BUILD_DIR := build/vscode/$(CONFIG_DIR)
OBJ_DIR := $(BUILD_DIR)/obj
TARGET := $(BUILD_DIR)/$(PROJECT_NAME).exe

SOURCES := src/main.cpp \
    src/core/game_state.cpp \
    src/core/hex_grid.cpp

OBJECTS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
DEPENDS := $(OBJECTS:.o=.d)

CPPFLAGS := -Iinclude -I$(RAYLIB_PATH)/src -DPLATFORM_DESKTOP -DGRAPHICS_API_OPENGL_33
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic $(MODE_FLAGS)
LDFLAGS := $(RAYLIB_PATH)/src/libraylib.a -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++

.PHONY: all debug release clean

all: $(TARGET)

debug:
	$(MAKE) BUILD_MODE=DEBUG all

release:
	$(MAKE) BUILD_MODE=RELEASE all

$(TARGET): $(OBJECTS)
	powershell -NoProfile -Command "New-Item -ItemType Directory -Force -Path '$(subst /,\,$(dir $@))' | Out-Null"
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	powershell -NoProfile -Command "New-Item -ItemType Directory -Force -Path '$(subst /,\,$(dir $@))' | Out-Null"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	powershell -NoProfile -Command "if (Test-Path 'build/vscode') { Remove-Item -Recurse -Force 'build/vscode' }"

-include $(DEPENDS)
