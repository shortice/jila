#pragma once

#include "engine/component.hpp"

namespace Jila {

namespace FaIconsComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentFaIcons {
    "Font Awesome Icons",
    "Shortice",
    FaIconsComponent::Init,
    FaIconsComponent::Quit
};

}
