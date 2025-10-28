#include <cstdio>
#include "engine/component.hpp"
#include "engine/runtime.hpp"
#include "engine/logger.hpp"
#include "SDL3/SDL_error.h"
#ifndef JILA_RELEASE
#include <filesystem>
#include "engine/hot_reloader.hpp"
#else
#include "app/jila_app.hpp"
#endif
#include "components/components.hpp"

namespace Jila {

#ifdef JILA_RELEASE
using namespace LuaApplication;
#endif

#ifndef JILA_RELEASE
static efsw::FileWatcher* fileWatcher;
static UpdateListener* listener;
#endif

static LuaRuntime* runtime;
static AppState* state;

void SetState(AppState* _state) {
    Jila::state = _state;
}

AppState* GetState() {
    return Jila::state;
}

void Error() {
    Logger::named("Runtime") \
    .error(
        std::string("Error: \n") + SDL_GetError()
    );
}

void IterComponentEnable(LuaComponent& component) {
    Logger::named("Runtime").info(
        std::string("Loading Lua component: ") + component.name
    );

    if (!component.Init(runtime->state)) Error();
}

void IterComponentQuit(LuaComponent& component) {
    component.Quit(runtime->state);
}

//
void loadFiles(LuaRuntime* runtime) {
    #ifndef JILA_RELEASE
    for (const auto& _ :
        std::filesystem::recursive_directory_iterator(runtime->path)
    ) {
        auto path = _.path();

        if (path.extension() != ".lua") continue;

        LuaModule::LoadFrom(path.c_str(), NULL, runtime->state);
    }
    #else
    auto _codes = GetCode();
    for (auto code : _codes) {
        LuaModule::LoadFrom(NULL, code, runtime->state);
    }
    #endif

    if (!LuaModule::GetModule("main")) {
        Logger::named("Runtime").error(
            "The 'main' module not found."
            "You not receive any events or able render gui."
        );
    }
}

LuaRuntime::LuaRuntime(const char* path) : path(path) {
    state = new sol::state();

    state->create_table("Scope");
}

LuaRuntime::~LuaRuntime() {
    delete state;
}

LuaRuntime* InitRuntime(const char* path) {
    runtime = new LuaRuntime(path);

    runtime->state->open_libraries(
        sol::lib::base,
        sol::lib::table,
        sol::lib::math,
        sol::lib::string,
        sol::lib::bit32
    );

    #ifndef JILA_RELEASE
    Logger::named("Runtime") \
        .debug("Hot reload enabled.");

    fileWatcher = new efsw::FileWatcher(true);
    listener = new UpdateListener();

    fileWatcher->addWatch(path, listener, true);

    fileWatcher->watch();
    #endif

    for (auto component : components) {
        IterComponentEnable(component);
    }

    return runtime;
}

void ReloadAll() {
    LuaModule::UnloadModules();
    loadFiles(runtime);

    Jila::LuaModule* module = Jila::LuaModule::GetModule("main");

    if (module) module->BeginMainLoop();
}

void QuitRuntime() {
    for (auto component : components) {
        IterComponentQuit(component);
    }

    #ifndef JILA_RELEASE
    delete listener;
    delete fileWatcher;
    #endif

    delete runtime;
}

}
