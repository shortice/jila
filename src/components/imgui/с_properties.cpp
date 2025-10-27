#include "imgui.h"
#include "components/imgui/c_properties.hpp"
#include "components/properties/c_properties.hpp"

namespace Jila {



void _ImGui_SetNextItemAllowOverlap() {
    ImGui::SetNextItemAllowOverlap();
}



void _ImGui_PushStyleVar_Float(ImGuiStyleVar idx, float val) {
    ImGui::PushStyleVar(idx, val);
}

void _ImGui_PushStyleVar_Vec2(ImGuiStyleVar idx, ImVec2& val) {
    ImGui::PushStyleVar(idx, val);
}

void _ImGui_PopStyleVar(int count) {
    ImGui::PopStyleVar(count);
}

void _ImGui_PushStyleColor(ImGuiCol col, ImVec4& vec) {
    ImGui::PushStyleColor(col, vec);
}

void _ImGui_PopStyleColor() {
    ImGui::PopStyleColor();
}

// Общие свойства

ImVec2 _ImGui_GetContentRegionAvail() {
    return ImGui::GetContentRegionAvail();
}

void _ImGui_SetScrollX(float pos) {
    ImGui::SetScrollX(pos);
}

void _ImGui_SetScrollY(float pos) {
    ImGui::SetScrollY(pos);
}



void _ImGui_SetNextWindowSize_V1(ImVec2 &vec) {
    ImGui::SetNextWindowSize(vec);
}

void _ImGui_SetNextWindowSize_V2(float x, float y) {
    ImGui::SetNextWindowSize(ImVec2(x, y));
}

void _ImGui_SetNextWindowPos_V1(float x, float y) {
    ImGui::SetNextWindowPos(ImVec2(x, y));
}

void _ImGui_SetNextWindowPos_V2(ImVec2 &vec) {
    ImGui::SetNextWindowPos(vec);
}

void _ImGui_SetWindowPos_V1(float x, float y) {
    ImGui::SetWindowPos(ImVec2(x, y));
}

void _ImGui_SetWindowPos_V2(ImVec2& pos) {
    ImGui::SetWindowPos(pos);
}

void _ImGui_SetWindowSize_V1(float x, float y) {
    ImGui::SetWindowSize(ImVec2(x, y));
}

void _ImGui_SetWindowSize_V2(ImVec2& size) {
    ImGui::SetWindowSize(size);
}

void _ImGui_SetWindowCollapsed_V1(bool collapsed) {
    ImGui::SetWindowCollapsed(collapsed);
}

void _ImGui_SetWindowCollapsed_V2(BoolProperty& collapsed) {
    ImGui::SetWindowCollapsed(collapsed.data);
}

void bindImProps(sol::state* state) {
    // Global behavior of the widgets.

    state -> set_function(
        "SetNextItemAllowOverlap",
        &_ImGui_SetNextItemAllowOverlap
    );

    // Styles

    state -> set_function(
        "PushStyleColor",
        &_ImGui_PushStyleColor
    );

    state -> set_function(
        "PopStyleColor",
        &_ImGui_PopStyleColor
    );

    state->set_function(
        "PushStyleVar",
        sol::overload(
            &_ImGui_PushStyleVar_Float,
            &_ImGui_PushStyleVar_Vec2
        )
    );

    state->set_function(
        "PopStyleVar",
        &_ImGui_PopStyleVar
    );

    // Общие свойства

    state -> set_function(
        "SetScrollX",
        &_ImGui_SetScrollX
    );

    state -> set_function(
        "SetScrollY",
        &_ImGui_SetScrollY
    );

    state -> set_function(
        "PushItemWidth",
        &ImGui::PushItemWidth
    );

    state -> set_function(
        "PopItemWidth",
        &ImGui::PopItemWidth
    );

    state -> set_function(
        "SetCursorPos",
        &ImGui::SetCursorPos
    );

    state->set_function(
        "GetMousePos",
        &ImGui::GetMousePos
    );

    state->set_function(
        "GetContentRegionAvail",
        &_ImGui_GetContentRegionAvail
    );

    // Properties of Window (and ChildWindow)

    state -> set_function(
        "SetNextWindowSize",
        sol::overload(
            &_ImGui_SetNextWindowSize_V1,
            &_ImGui_SetNextWindowSize_V2
        )
    );

    state -> set_function(
        "SetNextWindowPos",
        sol::overload(
            &_ImGui_SetNextWindowPos_V1,
            &_ImGui_SetNextWindowPos_V2
        )
    );

    state->set_function(
        "SetWindowPos",
        sol::overload(
            &_ImGui_SetWindowPos_V1,
            &_ImGui_SetWindowPos_V2
        )
    );

    state->set_function(
        "SetWindowSize",
        sol::overload(
            &_ImGui_SetWindowSize_V1,
            &_ImGui_SetWindowSize_V2
        )
    );

    state->set_function(
        "SetWindowCollapsed",
        sol::overload(
            &_ImGui_SetWindowCollapsed_V1,
            &_ImGui_SetWindowCollapsed_V2
        )
    );

    state->set_function(
        "GetWindowSize",
        &ImGui::GetWindowSize
    );

    state->set_function(
        "GetWindowPos",
        &ImGui::GetWindowPos
    );
}
    
}
