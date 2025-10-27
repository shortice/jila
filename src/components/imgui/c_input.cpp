#include "imgui.h"
#include "components/properties/c_properties.hpp"
#include "components/imgui/с_input.hpp"

namespace Jila {

bool _ImGui_SliderInt_V1(
    std::string label,
    IntProperty& property,
    int v_min,
    int v_max
) {
    return ImGui::SliderInt(
        label.data(),
        property.data,
        v_min,
        v_max
    );
}

bool _ImGui_SliderInt_V2(
    std::string label,
    IntProperty& property,
    int v_min, int v_max,
    std::string format
) {
    return ImGui::SliderInt(
        label.data(),
        property.data,
        v_min,
        v_max,
        format.data()
    );
}

bool _ImGui_SliderInt_V3(
    std::string label,
    IntProperty& property,
    int v_min,
    int v_max,
    std::string format,
    ImGuiSliderFlags flags
) {
    return ImGui::SliderInt(
        label.data(),
        property.data,
        v_min,
        v_max,
        format.data(),
        flags
    );
}

bool _ImGui_InputText_V1(
    std::string label,
    CharProperty& property
) {
    return ImGui::InputText(
        label.data(),
        property.str,
        property.size,
        ImGuiInputTextFlags_AllowTabInput
    );
}

bool _ImGui_InputText_V2(
    std::string label,
    CharProperty& property,
    ImGuiInputTextFlags flags
) {
    return ImGui::InputText(
        label.data(),
        property.str,
        property.size,
        flags
    );
}

bool _ImGui_InputTextMultiline_V1(
    std::string label,
    CharProperty& property
) {
    return ImGui::InputTextMultiline(
        label.data(),
        property.str,
        property.size,
        ImVec2()
    );
}

bool _ImGui_InputTextMultiline_V2(
    std::string label,
    CharProperty& property,
    ImVec2& size
) {
    return ImGui::InputTextMultiline(
        label.data(),
        property.str,
        property.size,
        size
    );
}

bool _ImGui_InputTextMultiline_V3(
    std::string label,
    CharProperty& property,
    ImVec2& size,
    ImGuiInputTextFlags flags
) {
    return ImGui::InputTextMultiline(
        label.data(),
        property.str,
        property.size,
        size,
        flags
    );
}

bool _ImGui_InputInt_V1(
    std::string label,
    IntProperty& property
) {
    return ImGui::InputInt(
        label.data(),
        property.data
    );
}

bool _ImGui_InputInt_V2(
    std::string label,
    IntProperty& property,
    int step
) {
    return ImGui::InputInt(
        label.data(),
        property.data,
        step
    );
}

bool _ImGui_InputInt_V3(
    std::string label,
    IntProperty& property,
    int step,
    int step_fast
) {
    return ImGui::InputInt(
        label.data(),
        property.data,
        step,
        step_fast
    );
}

bool _ImGui_SliderFloat_V1(
    std::string label,
    FloatProperty& property,
    float v_min,
    float v_max
) {
    return ImGui::SliderFloat(
        label.data(),
        property.data,
        v_min,
        v_max
    );
}

bool _ImGui_SliderFloat_V2(
    std::string label,
    FloatProperty& property,
    float v_min, float v_max,
    std::string format
) {
    return ImGui::SliderFloat(
        label.data(),
        property.data,
        v_min,
        v_max,
        format.data()
    );
}

bool _ImGui_SliderFloat_V3(
    std::string label,
    FloatProperty& property,
    float v_min,
    float v_max,
    std::string format,
    ImGuiSliderFlags flags
) {
    return ImGui::SliderFloat(
        label.data(),
        property.data,
        v_min,
        v_max,
        format.data(),
        flags
    );
}

bool _ImGui_DragFloat_V1(
    std::string label,
    FloatProperty& property
) {
    return ImGui::DragFloat(label.data(), property.data);
}

bool _ImGui_DragFloat_V2(
    std::string label,
    FloatProperty& property,
    float speed
) {
    return ImGui::DragFloat(label.data(), property.data, speed);
}

bool _ImGui_DragFloat_V3(
    std::string label,
    FloatProperty& property,
    float speed,
    float v_min,
    float v_max
) {
    return ImGui::DragFloat(label.data(), property.data, speed, v_min, v_max);
}

bool _ImGui_ColorEdit3_V1(std::string label, ImVec4& color) {
    return ImGui::ColorEdit3(label.data(), &color.x);
}

bool _ImGui_ColorEdit3_V2(std::string label, ImVec4& color, ImGuiColorEditFlags flags) {
    return ImGui::ColorEdit3(label.data(), &color.x, flags);
}

bool _ImGui_ColorEdit4_V1(std::string label, ImVec4& color) {
    return ImGui::ColorEdit4(label.data(), &color.x);
}

bool _ImGui_ColorEdit4_V2(std::string label, ImVec4& color, ImGuiColorEditFlags flags) {
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
