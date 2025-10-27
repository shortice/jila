#pragma once

#include <map>
#include <string>
#include <functional>
#include "sol/sol.hpp"

namespace Jila {

// TODO: make able to adding own/thrid-party components

/*
Lua component. 

Used for extend Lua functionality.
*/
struct LuaComponent {

    const char* name;
    const char* copyright;
    bool active;

    std::function<bool(sol::state*)> Init;
    std::function<void(sol::state*)> Quit;
};

struct LuaModule {
    static std::map<std::string, LuaModule*> modules;

    sol::table native;
    std::string name;
    std::string version;

    sol::function Begin;
    sol::function End;

    /*
    Load lua file from some path or string.

    Path param used for developoment, needs for hot-reloaded.
    Script param used for production ready build and embed code
    inside a executable (or shared lib for mobile).
    */
    static LuaModule* LoadFrom(
        const char* path,
        const char* script,
        sol::state* runtime
    );

    static sol::table GetModuleLuaAPI(std::string name);
    static LuaModule* GetModule(std::string name);

    static void UnloadModules();

    static LuaModule* FromLuaTable(sol::table module);

    // Only for 'main' module.
    sol::function BeginMainLoop;
    sol::function Render;
    sol::function Event;

};

}
