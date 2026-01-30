#include "components/engine/c_engine.hpp"
#include "engine/logger.hpp"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_timer.h"

namespace Jila {

namespace EngineComponent {

bool Init(sol::state* state) {
    state->set_function(
        "Create_Logger", 
        [](std::string name) { 
            return Logger(name); 
        }
    );

    state->new_usertype<Logger>(
        "Jila_Logger", 
        "name", sol::property(&Logger::name),
        "Warn", &Logger::warn,
        "Error", &Logger::error,
        "Debug", &Logger::debug,
        "Info", &Logger::info
    );

    state->set_function(
        "Jila_GetModule",
        &LuaModule::GetModuleLuaAPI
    );

    state->set_function(
        "Jila_GetError",
        &SDL_GetError
    );

    state->set_function(
        "Jila_Sleep",
        [](Uint64 seconds) {
            SDL_Delay(seconds * 1000);
        }
    );

    return true;
}

void Quit(sol::state* state) {}

}

}
