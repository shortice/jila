#include "imgui.h"
#include "components/imgui/c_imgui.hpp"

#include "components/imgui/c_flags.hpp"
#include "components/imgui/c_item_state.hpp"
#include "components/imgui/c_properties.hpp"
#include "components/imgui/c_utils.hpp"
#include "components/imgui/c_widgets.hpp"
#include "components/imgui/c_window.hpp"
#include "components/imgui/c_input.hpp"
#include "components/imgui/c_io.hpp"


namespace Jila {

namespace ImGuiComponent {

bool Init(sol::state* state) {
    state->set_function("Create_ImVec2", sol::overload(
        [](float x, float y) { 
            return ImVec2(x, y); 
        },
        []() { 
            return ImVec2(); 
        }
    ));

    state -> new_usertype<ImVec2>(
        "ImVec2",
        "x", &ImVec2::x,
        "y", &ImVec2::y
    );

    state->set_function("Create_ImVec4", sol::overload(
        [](float x, float y, float z, float w) { 
            return ImVec4(x, y, z, w);
        },
        []() { 
            return ImVec4(); 
        }
    ));

    state -> new_usertype<ImVec4>(
        "ImVec4",
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
    Jila::bindImIO(state);

    return true;
}


void Quit(sol::state* state) {}

}

}
