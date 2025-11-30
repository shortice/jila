#include "imgui.h"
#include "imgui_internal.h"
#include "components/imgui/c_utils.hpp"

void ScrollWhenDragging()
{
    ImVec2& mouse_delta = ImGui::GetIO().MouseDelta;
    ImVec2 delta = ImVec2(0.0f, -mouse_delta.y);

    ImGuiContext& g = *ImGui::GetCurrentContext();
    ImGuiWindow* window = g.CurrentWindow;

    if (!g.HoveredWindow) return;

    if (
        g.HoveredWindow->ID == window->ID &&
        ImGui::IsMouseDragging(ImGuiMouseButton_Left) && delta.y != 0.0f
    )
        ImGui::SetScrollY(window, window->Scroll.y + delta.y);
}

void _ImGui_SameLine_V1() {
    ImGui::SameLine();
}

void _ImGui_SameLine_V2(float xOffset) {
    ImGui::SameLine(xOffset);
}

ImVec2 _ImGui_CalcTextSize_V1(std::string label) {
    return ImGui::CalcTextSize(label.data());
}

void _ImGui_Separator_V2(std::string text) {
    ImGui::SeparatorText(text.data());
}

void _ImGui_ShowDemoWindow() {
    ImGui::ShowDemoWindow();
}

void _ImGui_ShowMetricsWindow() {
    ImGui::ShowMetricsWindow();
}

namespace Jila {

void bindImUtils(sol::state* state) {
    state -> set_function(
        "ScrollWhenDragging", 
        &ScrollWhenDragging
    );

    state -> set_function(
        "SameLine",
        sol::overload(
            &_ImGui_SameLine_V1,
            &_ImGui_SameLine_V2
        )
    );

    state -> set_function(
        "CalcTextSize",
        &_ImGui_CalcTextSize_V1
    );


    state -> set_function(
        "Separator",
        sol::overload(
            &ImGui::Separator,
            &_ImGui_Separator_V2
        )
    );

    state->set_function(
        "ShowDemoWindow",
        &_ImGui_ShowDemoWindow
    );

    state->set_function(
        "ShowMetricsWindow",
        &_ImGui_ShowMetricsWindow
    );
}
    
}