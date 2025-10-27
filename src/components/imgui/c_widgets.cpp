#include "imgui.h"
#include "components/properties/c_properties.hpp"
#include "components/imgui/c_widgets.hpp"

namespace Jila {

bool _ImGui_Button_V1(std::string label) {
    return ImGui::Button(label.data());
}

bool _ImGui_Button_V2(std::string label, ImVec2 &size) {
    return ImGui::Button(label.data(), size);
}

void _ImGui_Text(std::string text) {
    ImGui::Text("%s", text.data());
}

void _ImGui_TextWrapped(std::string text) {
    ImGui::TextWrapped("%s", text.data());
}

bool _ImGui_BeginCombo_V1(
    std::string label,
    std::string preview
) {
    return ImGui::BeginCombo(label.data(), preview.data());
}

bool _ImGui_BeginCombo_V2(
    std::string label,
    std::string preview,
    ImGuiComboFlags_ flags
) {
    return ImGui::BeginCombo(
        label.data(),
        preview.data(),
        flags
    );
}

bool _ImGui_Selectable_V1(
    std::string label,
    BoolProperty& opened
) {
    return ImGui::Selectable(
        label.data(),
        opened.data
    );
}

bool _ImGui_Selectable_V2(
    std::string label,
    BoolProperty& opened,
    ImGuiSelectableFlags flags
) {
    return ImGui::Selectable(label.data(), opened.data, flags);
}

bool _ImGui_BeginMenu(std::string label) {
    return ImGui::BeginMenu(label.data());
}

bool _ImGui_MenuItem_V1(std::string label) {
    return ImGui::MenuItem(label.data());
}

bool _ImGui_MenuItem_V2(
    std::string label,
    BoolProperty& selected
) {
    return ImGui::MenuItem(label.data(), NULL, selected.data);
}

bool _ImGui_MenuItem_V3(
    std::string label,
    std::string_view shortcut,
    BoolProperty& selected
) {
    return ImGui::MenuItem(
        label.data(),
        shortcut.data(),
        selected.data
    );
}

bool _ImGui_BeginTabBar(std::string label) {
    return ImGui::BeginTabBar(label.data());
}

bool _ImGui_BeginTabItem(std::string label) {
    return ImGui::BeginTabItem(label.data());
}

bool _ImGui_CheckBox(std::string label, BoolProperty& prop) {
    return ImGui::Checkbox(
        label.data(),
        prop.data
    );
}

bool _ImGui_TreeNode_V1(std::string label) {
    return ImGui::TreeNode(label.data());
}

bool _ImGui_CollapsingHeader_V1(std::string label) {
    return ImGui::CollapsingHeader(label.data());
}

bool _ImGui_CollapsingHeader_V2(std::string label, BoolProperty& opened) {
    return ImGui::CollapsingHeader(label.data(), opened.data);
}

bool _ImGui_CollapsingHeader_V3(
    std::string label,
    BoolProperty& opened,
    ImGuiTreeNodeFlags flags
) {
    return ImGui::CollapsingHeader(label.data(), opened.data, flags);
}

void _ImGui_ProgressBar(float fraction, ImVec2& size_arg) {
    ImGui::ProgressBar(fraction, size_arg);
}

void _ImGui_ProgressBar_V2(float fraction) {
    ImGui::ProgressBar(fraction);
}

void _ImGui_Bullet() {
    ImGui::Bullet();
}

bool _ImGui_BeginTable(const std::string& str_id, int column) {
    return ImGui::BeginTable(str_id.c_str(), column);
}

void _ImGui_EndTable() {
    ImGui::EndTable();
}

void _ImGui_TableNextRow() {
    ImGui::TableNextRow();
}

bool _ImGui_TableNextColumn() {
    return ImGui::TableNextColumn();
}

void _ImGui_TableSetupColumn(const std::string& label) {
    ImGui::TableSetupColumn(label.c_str());
}

void _ImGui_TableHeadersRow() {
    ImGui::TableHeadersRow();
}

bool _ImGui_BeginModal_V1(const std::string& label) {
    return ImGui::BeginPopupModal(
        label.data(),
        NULL,
        ImGuiWindowFlags_NoResize // TODO: flags arg?
    );
}

bool _ImGui_BeginModal_V2(const std::string& label, BoolProperty& opened) {
    return ImGui::BeginPopupModal(label.data(), opened.data, ImGuiWindowFlags_NoResize);
}

void _ImGui_OpenPopup(const std::string& label) {
    ImGui::OpenPopup(label.data());
}

void bindImWidgets(sol::state* state) {
    state -> set_function(
        "Button",
        sol::overload(
            &_ImGui_Button_V1,
            &_ImGui_Button_V2
        )
    );

    state -> set_function(
        "Text",
        &_ImGui_Text
    );

    state -> set_function(
        "TextWrapped",
        &_ImGui_TextWrapped
    );

    state -> set_function(
        "BeginCombo",
        sol::overload(
            &_ImGui_BeginCombo_V1,
            &_ImGui_BeginCombo_V2
        )
    );

    state -> set_function(
        "Selectable",
        sol::overload(
            &_ImGui_Selectable_V1,
            &_ImGui_Selectable_V2
        )
    );

    state -> set_function(
        "EndCombo",
        &ImGui::EndCombo
    );

    state -> set_function(
        "BeginMenuBar",
        &ImGui::BeginMenuBar
    );

    state -> set_function(
        "BeginMainMenuBar",
        &ImGui::BeginMainMenuBar
    );

    state -> set_function(
        "BeginMenu",
        &_ImGui_BeginMenu
    );

    state -> set_function(
        "MenuItem",
        sol::overload(
            &_ImGui_MenuItem_V1,
            &_ImGui_MenuItem_V2,
            &_ImGui_MenuItem_V3
        )
    );

    state -> set_function(
        "EndMenu",
        &ImGui::EndMenu
    );

    state -> set_function(
        "EndMenuBar",
        &ImGui::EndMenuBar
    );

    state -> set_function(
        "EndMainMenuBar",
        &ImGui::EndMainMenuBar
    );

    state -> set_function(
        "BeginTabBar",
        &_ImGui_BeginTabBar
    );

    state -> set_function(
        "BeginTabItem",
        &_ImGui_BeginTabItem
    );

    state -> set_function(
        "EndTabItem",
        &ImGui::EndTabItem
    );

    state -> set_function(
        "EndTabBar",
        &ImGui::EndTabBar
    );

    state -> set_function(
        "Checkbox",
        &_ImGui_CheckBox
    );

    state -> set_function(
        "OpenPopup",
        &_ImGui_OpenPopup
    );

    state -> set_function(
        "BeginModal",
        sol::overload(
            &_ImGui_BeginModal_V1,
            &_ImGui_BeginModal_V2
        )
    );

    state -> set_function(
        "EndModal",
        &ImGui::EndPopup
    );

    state->set_function(
        "BeginTable",
        &_ImGui_BeginTable
    );

    state->set_function(
        "EndTable",
        &_ImGui_EndTable
    );

    state->set_function(
        "TableNextRow",
        &_ImGui_TableNextRow
    );

    state->set_function(
        "TableNextColumn",
        &_ImGui_TableNextColumn
    );

    state->set_function(
        "TableSetupColumn",
        &_ImGui_TableSetupColumn
    );

    state->set_function(
        "TableHeadersRow",
        &_ImGui_TableHeadersRow
    );

    state->set_function(
        "TreeNode",
        &_ImGui_TreeNode_V1
    );

    state->set_function(
        "TreePop",
        &ImGui::TreePop
    );

    state->set_function(
        "CollapsingHeader",
        sol::overload(
            &_ImGui_CollapsingHeader_V1,
            &_ImGui_CollapsingHeader_V2,
            &_ImGui_CollapsingHeader_V3
        )
    );

    state->set_function(
        "ProgressBar",
        sol::overload(
            &_ImGui_ProgressBar_V2,
            &_ImGui_ProgressBar
        )
    );

    state->set_function(
        "Bullet",
        &_ImGui_Bullet
    );
}

}
