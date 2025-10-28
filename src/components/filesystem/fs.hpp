#pragma once
#include "engine/component.hpp"

namespace Jila {

namespace FileSystemComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentFileSystem {
    "FileSystem",
    "Shortice",
    FileSystemComponent::Init,
    FileSystemComponent::Quit
};

}
