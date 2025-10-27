#include "imgui.h"
#include "components/properties/c_properties.hpp"
#include "components/imgui/c_window.hpp"

namespace Jila {

bool _ImGui_Begin_V1(std::string name) {
    return ImGui::Begin(name.data());
}

bool _ImGui_Begin_V2(
    std::string name,
    BoolProperty& opened
) {
    return ImGui::Begin(name.data(), opened.data);
}

bool _ImGui_Begin_V3(
    std::string name,
    BoolProperty& opened,
    ImGuiWindowFlags flags
) {
    return ImGui::Begin(name.data(), opened.data, flags);
}

bool _ImGui_Begin_V4(
    std::string name,
    ImGuiWindowFlags flags
) {
    return ImGui::Begin(name.data(), NULL, flags);
}

bool _ImGui_BeginChild_V1(std::string id) {
    return ImGui::BeginChild(id.data());
}

bool _ImGui_BeginChild_V2(std::string id, ImVec2& size) {
    return ImGui::BeginChild(id.data(), size);
}

bool _ImGui_BeginChild_V3(
    std::string id,
    ImVec2& size,
    ImGuiChildFlags childFlags
) {
    return ImGui::BeginChild(id.data(), size, childFlags);
}

bool _ImGui_BeginChild_V4(
    std::string id,
    ImVec2& size,
    ImGuiChildFlags childFlags,
    ImGuiWindowFlags windowFlags
) {
    return ImGui::BeginChild(
        id.data(),
        size,
        childFlags,
        windowFlags
    );
}



void bindImWindow(sol::state* state) {
    state -> set_function(
        "Begin",
        sol::overload(
            &_ImGui_Begin_V1,
            &_ImGui_Begin_V2,
            &_ImGui_Begin_V3,
            &_ImGui_Begin_V4
        )
    );

    state -> set_function(
        "End",
        &ImGui::End
    );

    state -> set_function(
        "BeginChild",
        sol::overload(
            &_ImGui_BeginChild_V1,
            &_ImGui_BeginChild_V2,
            &_ImGui_BeginChild_V3,
            &_ImGui_BeginChild_V4
        )
    );

    state -> set_function(
        "EndChild", &ImGui::EndChild
    );
}

}
