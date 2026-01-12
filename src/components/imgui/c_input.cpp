#include "imgui.h"
#include "components/properties/c_properties.hpp"
#include "components/imgui/c_input.hpp"
#include "components/imgui/c_io.hpp"
#include "imgui_stdlib.h"

namespace Jila {

// TODO: Need args they limits v_max/v_min in InputInt/Drag/InputText/etc
// Example: if user input size in bytes > int size, they create UB. 
// We don't want this.

bool _ImGui_SliderInt_V1(
    std::string_view label,
    IntProperty& property,
    int v_min,
    int v_max
) {
    return ImGui::SliderInt(
        label.data(),
        &property.data,
        v_min,
        v_max
    );
}

bool _ImGui_SliderInt_V2(
    std::string_view label,
    IntProperty& property,
    int v_min, int v_max,
    std::string_view format
) {
    return ImGui::SliderInt(
        label.data(),
        &property.data,
        v_min,
        v_max,
        format.data()
    );
}

bool _ImGui_SliderInt_V3(
    std::string_view label,
    IntProperty& property,
    int v_min,
    int v_max,
    std::string_view format,
    ImGuiSliderFlags flags
) {
    return ImGui::SliderInt(
        label.data(),
        &property.data,
        v_min,
        v_max,
        format.data(),
        flags
    );
}

bool _ImGui_InputText_V1(
    std::string_view label,
    CharProperty& property
) {
    bool _ = ImGui::InputText(
        label.data(),
        &property.str,
        ImGuiInputTextFlags_AllowTabInput
    );
    UpdateSelectedText(property.str.data());
    return _;
}

bool _ImGui_InputText_V2(
    std::string_view label,
    CharProperty& property,
    ImGuiInputTextFlags flags
) {
    bool _ = ImGui::InputText(
        label.data(),
        &property.str,
        flags
    );
    UpdateSelectedText(property.str.data());
    return _;
}

bool _ImGui_InputTextMultiline_V1(
    std::string_view label,
    CharProperty& property
) {
    bool _ = ImGui::InputTextMultiline(
        label.data(),
        &property.str,
        ImVec2()
    );
    UpdateSelectedText(property.str.data());
    return _;
}

bool _ImGui_InputTextMultiline_V2(
    std::string_view label,
    CharProperty& property,
    ImVec2& size
) {
    bool _ = ImGui::InputTextMultiline(
        label.data(),
        &property.str,
        size
    );
    UpdateSelectedText(property.str.data());
    return _;
}

bool _ImGui_InputTextMultiline_V3(
    std::string_view label,
    CharProperty& property,
    ImVec2& size,
    ImGuiInputTextFlags flags
) {
    bool _ = ImGui::InputTextMultiline(
        label.data(),
        &property.str,
        size,
        flags
    );
    UpdateSelectedText(property.str.data());
    return _;
}

bool _ImGui_InputInt_V1(
    std::string_view label,
    IntProperty& property
) {
    return ImGui::InputInt(
        label.data(),
        &property.data
    );
}

bool _ImGui_InputInt_V2(
    std::string_view label,
    IntProperty& property,
    int step
) {
    return ImGui::InputInt(
        label.data(),
        &property.data,
        step
    );
}

bool _ImGui_InputInt_V3(
    std::string_view label,
    IntProperty& property,
    int step,
    int step_fast
) {
    return ImGui::InputInt(
        label.data(),
        &property.data,
        step,
        step_fast
    );
}

bool _ImGui_SliderFloat_V1(
    std::string_view label,
    FloatProperty& property,
    float v_min,
    float v_max
) {
    return ImGui::SliderFloat(
        label.data(),
        &property.data,
        v_min,
        v_max
    );
}

bool _ImGui_SliderFloat_V2(
    std::string_view label,
    FloatProperty& property,
    float v_min, float v_max,
    std::string_view format
) {
    return ImGui::SliderFloat(
        label.data(),
        &property.data,
        v_min,
        v_max,
        format.data()
    );
}

bool _ImGui_SliderFloat_V3(
    std::string_view label,
    FloatProperty& property,
    float v_min,
    float v_max,
    std::string_view format,
    ImGuiSliderFlags flags
) {
    return ImGui::SliderFloat(
        label.data(),
        &property.data,
        v_min,
        v_max,
        format.data(),
        flags
    );
}

bool _ImGui_DragFloat_V1(
    std::string_view label,
    FloatProperty& property
) {
    return ImGui::DragFloat(label.data(), &property.data);
}

bool _ImGui_DragFloat_V2(
    std::string_view label,
    FloatProperty& property,
    float speed
) {
    return ImGui::DragFloat(label.data(), &property.data, speed);
}

bool _ImGui_DragFloat_V3(
    std::string_view label,
    FloatProperty& property,
    float speed,
    float v_min,
    float v_max
) {
    return ImGui::DragFloat(label.data(), &property.data, speed, v_min, v_max);
}

bool _ImGui_ColorEdit3_V1(std::string_view label, ImVec4& color) {
    return ImGui::ColorEdit3(label.data(), &color.x);
}

bool _ImGui_ColorEdit3_V2(std::string_view label, ImVec4& color, ImGuiColorEditFlags flags) {
    return ImGui::ColorEdit3(label.data(), &color.x, flags);
}

bool _ImGui_ColorEdit4_V1(std::string_view label, ImVec4& color) {
    return ImGui::ColorEdit4(label.data(), &color.x);
}

bool _ImGui_ColorEdit4_V2(std::string_view label, ImVec4& color, ImGuiColorEditFlags flags) {
    return ImGui::ColorEdit4(label.data(), &color.x, flags);
}

void bindImInput(sol::state* state) {
    state -> set_function(
        "SliderInt",
        sol::overload(
            &_ImGui_SliderInt_V1,
            &_ImGui_SliderInt_V2,
            &_ImGui_SliderInt_V3
        )
    );

    state -> set_function(
        "InputText",
        sol::overload(
            &_ImGui_InputText_V1,
            &_ImGui_InputText_V2
        )
    );

    state -> set_function(
        "InputTextMultiline",
        sol::overload(
            &_ImGui_InputTextMultiline_V1,
            &_ImGui_InputTextMultiline_V2,
            &_ImGui_InputTextMultiline_V3
        )
    );

    state->set_function(
        "InputInt",
        sol::overload(
            &_ImGui_InputInt_V1,
            &_ImGui_InputInt_V2,
            &_ImGui_InputInt_V3
        )
    );

    state->set_function(
        "SliderFloat",
        sol::overload(
            &_ImGui_SliderFloat_V1,
            &_ImGui_SliderFloat_V2,
            &_ImGui_SliderFloat_V3
        )
    );

    state->set_function(
        "DragFloat",
        sol::overload(
            &_ImGui_DragFloat_V1,
            &_ImGui_DragFloat_V2,
            &_ImGui_DragFloat_V3
        )
    );

    state->set_function(
        "ColorEdit3",
        sol::overload(
            &_ImGui_ColorEdit3_V1,
            &_ImGui_ColorEdit3_V2
        )
    );

    state->set_function(
        "ColorEdit4",
        sol::overload(
            &_ImGui_ColorEdit4_V1,
            &_ImGui_ColorEdit4_V2
        )
    );
}

}
