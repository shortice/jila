#pragma once

#include "engine/component.hpp"

namespace Jila {

enum _StatusCode : uint8_t { 
    STARTING, 
    RUNNING, 
    COMPLETED, 
    ERROR 
};

struct ThreadMessage {
    std::string threadName;
    std::variant<double, std::string, sol::lua_nil_t> var;
    _StatusCode statusCode;
};

namespace ThreadsComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentThreads {
    "Threads",
    "Shortice",
    ThreadsComponent::Init,
    ThreadsComponent::Quit
};

}
