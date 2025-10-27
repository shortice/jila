#include "imgui.h"
#include "components/imgui/c_imgui.hpp"

#include "components/imgui/c_flags.hpp"
#include "components/imgui/c_item_state.hpp"
#include "components/imgui/c_properties.hpp"
#include "components/imgui/c_utils.hpp"
#include "components/imgui/c_widgets.hpp"
#include "components/imgui/c_window.hpp"
#include "components/imgui/с_input.hpp"


namespace Jila {

namespace ImGuiComponent {

bool Init(sol::state* state) {
    state -> new_usertype<ImVec2>(
        "ImVec2",
        sol::constructors<ImVec2(float, float), ImVec2()>(),
        "x", &ImVec2::x,
        "y", &ImVec2::y
    );

    state -> new_usertype<ImVec4>(
        "ImVec4",
        sol::constructors<
            ImVec4(float, float, float, float), ImVec4()
        >(),
        "x", &ImVec4::x,
        "y", &ImVec4::y,
        "z", &ImVec4::z,
        "w", &ImVec4::w
    );

    Jila::bindImUtils(state);
    Jila::bindImState(state);
    Jila::bindImFlags(state);
    Jila::bindImInput(state);
    Jila::bindImWidgets(state);
    Jila::bindImWindow(state);
    Jila::bindImProps(state);

    return true;
}


void Quit(sol::state* state) {}

}

}
