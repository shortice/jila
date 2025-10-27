#pragma once

#include "engine/component.hpp"

namespace Jila {

namespace ImGuiComponent {

bool Init(sol::state* state);
void Quit(sol::state* state);

}

static LuaComponent ComponentImGui {
    "Dear ImGui",
    "Shortice",
    false,
    ImGuiComponent::Init,
    ImGuiComponent::Quit
};

}
