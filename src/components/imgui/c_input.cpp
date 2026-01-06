#include "imgui.h"
#include "components/properties/c_properties.hpp"
#include "components/imgui/c_input.hpp"

namespace Jila {

bool _ImGui_SliderInt_V1(
    std::string_view label,
    IntProperty& Property,
    int v_min,
    int v_max
) {
    return ImGui::SliderInt(
        label.data(),
        Property.data,
        v_min,
        v_max
    );
}

bool _ImGui_SliderInt_V2(
    std::string_view label,
    IntProperty& Property,
    int v_min, int v_max,
    std::string_view format
) {
    return ImGui::SliderInt(
        label.data(),
        Property.data,
        v_min,
        v_max,
        format.data()
    );
}

bool _ImGui_SliderInt_V3(
    std::string_view label,
    IntProperty& Property,
    int v_min,
    int v_max,
    std::string_view format,
    ImGuiSliderFlags flags
) {
    return ImGui::SliderInt(
        label.data(),
        Property.data,
        v_min,
        v_max,
        format.data(),
        flags
    );
}

bool _ImGui_InputText_V1(
    std::string_view label,
    CharProperty& Property
) {
    return ImGui::InputText(
        label.data(),
        Property.str.data(),
        Property.size,
        ImGuiInputTextFlags_AllowTabInput
    );
}

bool _ImGui_InputText_V2(
    std::string_view label,
    CharProperty& Property,
    ImGuiInputTextFlags flags
) {
    return ImGui::InputText(
        label.data(),
        Property.str.data(),
        Property.size,
        flags
    );
}

bool _ImGui_InputTextMultiline_V1(
    std::string_view label,
    CharProperty& Property
) {
    return ImGui::InputTextMultiline(
        label.data(),
        Property.str.data(),
        Property.size,
        ImVec2()
    );
}

bool _ImGui_InputTextMultiline_V2(
    std::string_view label,
    CharProperty& Property,
    ImVec2& size
) {
    return ImGui::InputTextMultiline(
        label.data(),
        Property.str.data(),
        Property.size,
        size
    );
}

bool _ImGui_InputTextMultiline_V3(
    std::string_view label,
    CharProperty& Property,
    ImVec2& size,
    ImGuiInputTextFlags flags
) {
    return ImGui::InputTextMultiline(
        label.data(),
        Property.str.data(),
        Property.size,
        size,
        flags
    );
}

bool _ImGui_InputInt_V1(
    std::string_view label,
    IntProperty& Property
) {
    return ImGui::InputInt(
        label.data(),
        Property.data
    );
}

bool _ImGui_InputInt_V2(
    std::string_view label,
    IntProperty& Property,
    int step
) {
    return ImGui::InputInt(
        label.data(),
        Property.data,
        step
    );
}

bool _ImGui_InputInt_V3(
    std::string_view label,
    IntProperty& Property,
    int step,
    int step_fast
) {
    return ImGui::InputInt(
        label.data(),
        Property.data,
        step,
        step_fast
    );
}

bool _ImGui_SliderFloat_V1(
    std::string_view label,
    FloatProperty& Property,
    float v_min,
    float v_max
) {
    return ImGui::SliderFloat(
        label.data(),
        Property.data,
        v_min,
        v_max
    );
}

bool _ImGui_SliderFloat_V2(
    std::string_view label,
    FloatProperty& Property,
    float v_min, float v_max,
    std::string_view format
) {
    return ImGui::SliderFloat(
        label.data(),
        Property.data,
        v_min,
        v_max,
        format.data()
    );
}

bool _ImGui_SliderFloat_V3(
    std::string_view label,
    FloatProperty& Property,
    float v_min,
    float v_max,
    std::string_view format,
    ImGuiSliderFlags flags
) {
    return ImGui::SliderFloat(
        label.data(),
        Property.data,
        v_min,
        v_max,
        format.data(),
        flags
    );
}

bool _ImGui_DragFloat_V1(
    std::string_view label,
    FloatProperty& Property
) {
    return ImGui::DragFloat(label.data(), Property.data);
}

bool _ImGui_DragFloat_V2(
    std::string_view label,
    FloatProperty& Property,
    float speed
) {
    return ImGui::DragFloat(label.data(), Property.data, speed);
}

bool _ImGui_DragFloat_V3(
    std::string_view label,
    FloatProperty& Property,
    float speed,
    float v_min,
    float v_max
) {
    return ImGui::DragFloat(label.data(), Property.data, speed, v_min, v_max);
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
