#include "imgui.h"
#include "components/imgui/c_item_state.hpp"

bool _ImGui_IsKeyPressed_V1(int key_code) {
    return ImGui::IsKeyPressed((ImGuiKey)key_code);
}

bool _ImGui_IsKeyPressed_V2(int key_code, bool repeat) {
    return ImGui::IsKeyPressed((ImGuiKey)key_code, repeat);
}

bool _ImGui_IsMouseDown(ImGuiMouseButton mouse_button) {
    return ImGui::IsMouseDown(mouse_button);
}

namespace Jila {

void bindImState(sol::state* state) {
    state -> set_function(
        "IsItemHovered",
        []() {
            return ImGui::IsItemHovered();
        }
    );

    state->set_function(
        "IsKeyPressed",
        sol::overload(
            &_ImGui_IsKeyPressed_V1,
            &_ImGui_IsKeyPressed_V2
        )
    );

    state->set_function(
        "IsMouseDown",
        &_ImGui_IsMouseDown
    );

    state -> set_function(
        "IsDoubleClicked",
        []() {
            return ImGui::IsMouseDoubleClicked(
                ImGuiMouseButton_Left
            );
        }
    );
}

}
