#pragma once

#include "engine/component.hpp"

namespace Jila {

namespace ThreadsComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentThreads {
    "Threads",
    "Shortice",
    false,
    ThreadsComponent::Init,
    ThreadsComponent::Quit
};

}
