#pragma once

#include "imgui.h"
#include "sol/sol.hpp"
#include "SDL3/SDL_render.h"

namespace Jila {

/*
The Lua runtime.
*/
struct LuaRuntime {
    sol::state* state;
    const char* path;

    LuaRuntime(const char* path);

    ~LuaRuntime();
};

/*
App state struct.
*/
struct AppState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    LuaRuntime* state;
    ImGuiIO* io;
};

/*
This code init Lua runtime.
*/
LuaRuntime* InitRuntime(const char* path);

/*
[!internal code]
*/
void SetState(AppState* _state);

/*
Get current AppState.
*/
AppState* GetState();

/*
[!internal code]
*/
void loadFiles(LuaRuntime* runtime);

/*
Reload all Lua files.
*/
void ReloadAll();

/*
Quit Lua runtime.
*/
void QuitRuntime();

}
