#include "imgui.h"
#include "imgui_stdlib.h"
#include "components/properties/c_properties.hpp"
#include "components/imgui/c_widgets.hpp"
#include "components/imgui/c_io.hpp"
#ifdef JILA_IMAGES
#include "components/sdl3/images.hpp"
#endif

namespace Jila {

bool _ImGui_Button_V1(std::string_view label) {
    return ImGui::Button(label.data());
}

bool _ImGui_Button_V2(std::string_view label, ImVec2 &size) {
    return ImGui::Button(label.data(), size);
}

void _ImGui_SelectableText(
    std::string_view label,
    CharProperty& text,
    ImVec2& size
) {
    ImGui::PushStyleColor(
        ImGuiCol_FrameBg,
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg]
    );

    ImGui::InputTextMultiline(
        label.data(),
        &text.str, // we don't edit text
        size,
        (
            ImGuiInputTextFlags_ReadOnly |
            ImGuiInputTextFlags_AutoSelectAll |
            ImGuiInputTextFlags_WordWrap
        )
    );
    UpdateSelectedText(text.str.data());

    ImGui::PopStyleColor();
}

void _ImGui_Text(std::string_view text) {
    ImGui::Text("%s", text.data());
}

void _ImGui_TextWrapped(std::string_view text) {
    ImGui::TextWrapped("%s", text.data());
}

bool _ImGui_BeginCombo_V1(
    std::string_view label,
    std::string_view preview
) {
    return ImGui::BeginCombo(label.data(), preview.data());
}

bool _ImGui_BeginCombo_V2(
    std::string_view label,
    std::string_view preview,
    ImGuiComboFlags_ flags
) {
    return ImGui::BeginCombo(
        label.data(),
        preview.data(),
        flags
    );
}

bool _ImGui_Selectable_V1(
    std::string_view label,
    BoolProperty& opened
) {
    return ImGui::Selectable(
        label.data(),
        opened.data
    );
}

bool _ImGui_Selectable_V2(
    std::string_view label,
    BoolProperty& opened,
    ImGuiSelectableFlags flags
) {
    return ImGui::Selectable(label.data(), opened.data, flags);
}

bool _ImGui_BeginMenu(std::string_view label) {
    return ImGui::BeginMenu(label.data());
}

bool _ImGui_MenuItem_V1(std::string_view label) {
    return ImGui::MenuItem(label.data());
}

bool _ImGui_MenuItem_V2(
    std::string_view label,
    BoolProperty& selected
) {
    return ImGui::MenuItem(
        label.data(),
        NULL,
        selected.data
    );
}

bool _ImGui_MenuItem_V3(
    std::string_view label,
    std::string_view shortcut,
    BoolProperty& selected
) {
    return ImGui::MenuItem(
        label.data(),
        shortcut.data(),
        selected.data
    );
}

bool _ImGui_BeginTabBar(std::string_view label) {
    return ImGui::BeginTabBar(label.data());
}

bool _ImGui_BeginTabItem(std::string_view label) {
    return ImGui::BeginTabItem(label.data());
}

bool _ImGui_CheckBox(std::string_view label, BoolProperty& prop) {
    return ImGui::Checkbox(
        label.data(),
        &prop.data
    );
}

bool _ImGui_TreeNode_V1(std::string_view label) {
    return ImGui::TreeNode(label.data());
}

bool _ImGui_CollapsingHeader_V1(std::string_view label) {
    return ImGui::CollapsingHeader(label.data());
}

bool _ImGui_CollapsingHeader_V2(std::string_view label, BoolProperty& opened) {
    return ImGui::CollapsingHeader(label.data(), opened.data);
}

bool _ImGui_CollapsingHeader_V3(
    std::string_view label,
    BoolProperty& opened,
    ImGuiTreeNodeFlags flags
) {
    return ImGui::CollapsingHeader(
        label.data(), &opened.data, flags
    );
}

void _ImGui_ProgressBar(FloatProperty& fraction, ImVec2& size_arg) {
    ImGui::ProgressBar(fraction.data, size_arg);
}

void _ImGui_ProgressBar_V2(FloatProperty& fraction) {
    ImGui::ProgressBar(fraction.data);
}

void _ImGui_Bullet() {
    ImGui::Bullet();
}

bool _ImGui_BeginTable(std::string_view str_id, int column) {
    return ImGui::BeginTable(str_id.data(), column);
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

void _ImGui_TableSetupColumn(std::string_view label) {
    ImGui::TableSetupColumn(label.data());
}

void _ImGui_TableHeadersRow() {
    ImGui::TableHeadersRow();
}

bool _ImGui_BeginModal_V1(std::string_view label) {
    return ImGui::BeginPopupModal(
        label.data(),
        NULL,
        ImGuiWindowFlags_NoResize // TODO: flags arg?
    );
}

bool _ImGui_BeginModal_V2(std::string_view label, BoolProperty& opened) {
    return ImGui::BeginPopupModal(
        label.data(),
        &opened.data,
        ImGuiWindowFlags_NoResize
    );
}

void _ImGui_OpenPopup(std::string_view label) {
    ImGui::OpenPopup(label.data());
}

bool _ImGui_BeginListBox(std::string_view label) {
    return ImGui::BeginListBox(label.data());
}

void _ImGui_EndListBox() {
    ImGui::EndListBox();
}

#ifdef JILA_IMAGES
void _ImGui_Image(Texture texture, ImVec2& imageSize) {
    ImGui::Image(
        (intptr_t)texture.get(),
        imageSize
    );
}

bool _ImGui_ImageButton_V1(
    std::string_view label,
    Texture texture,
    ImVec2& imageSize
) {
    return ImGui::ImageButton(
        label.data(),
        (intptr_t)texture.get(),
        imageSize
    );
}
#endif

void _ImGui_SetItemTooltip(std::string_view label) {
    return ImGui::SetItemTooltip("%s", label.data());
}

void _ImGui_SetTooltip(std::string_view label) {
    return ImGui::SetTooltip("%s", label.data());
}

void bindImWidgets(sol::state* state) {
    state -> set_function(
        "ImButton",
        sol::overload(
            &_ImGui_Button_V1,
            &_ImGui_Button_V2
        )
    );

    state -> set_function(
        "ImText",
        &_ImGui_Text
    );

    state -> set_function(
        "ImTextWrapped",
        &_ImGui_TextWrapped
    );

    state -> set_function(
        "ImSelectableText",
        &_ImGui_SelectableText
    );

    state -> set_function(
        "ImBeginCombo",
        sol::overload(
            &_ImGui_BeginCombo_V1,
            &_ImGui_BeginCombo_V2
        )
    );

    state -> set_function(
        "ImSelectable",
        sol::overload(
            &_ImGui_Selectable_V1,
            &_ImGui_Selectable_V2
        )
    );

    state -> set_function(
        "ImEndCombo",
        &ImGui::EndCombo
    );

    state -> set_function(
        "ImBeginMenuBar",
        &ImGui::BeginMenuBar
    );

    state -> set_function(
        "ImBeginMainMenuBar",
        &ImGui::BeginMainMenuBar
    );

    state -> set_function(
        "ImBeginMenu",
        &_ImGui_BeginMenu
    );

    state -> set_function(
        "ImMenuItem",
        sol::overload(
            &_ImGui_MenuItem_V1,
            &_ImGui_MenuItem_V2,
            &_ImGui_MenuItem_V3
        )
    );

    state -> set_function(
        "ImEndMenu",
        &ImGui::EndMenu
    );

    state -> set_function(
        "ImEndMenuBar",
        &ImGui::EndMenuBar
    );

    state -> set_function(
        "ImEndMainMenuBar",
        &ImGui::EndMainMenuBar
    );

    state -> set_function(
        "ImBeginTabBar",
        &_ImGui_BeginTabBar
    );

    state -> set_function(
        "ImBeginTabItem",
        &_ImGui_BeginTabItem
    );

    state -> set_function(
        "ImEndTabItem",
        &ImGui::EndTabItem
    );

    state -> set_function(
        "ImEndTabBar",
        &ImGui::EndTabBar
    );

    state -> set_function(
        "ImCheckbox",
        &_ImGui_CheckBox
    );

    state -> set_function(
        "ImOpenPopup",
        &_ImGui_OpenPopup
    );

    state -> set_function(
        "ImBeginModal",
        sol::overload(
            &_ImGui_BeginModal_V1,
            &_ImGui_BeginModal_V2
        )
    );

    state -> set_function(
        "ImEndModal",
        &ImGui::EndPopup
    );

    state->set_function(
        "ImBeginTable",
        &_ImGui_BeginTable
    );

    state->set_function(
        "ImEndTable",
        &_ImGui_EndTable
    );

    state->set_function(
        "ImTableNextRow",
        &_ImGui_TableNextRow
    );

    state->set_function(
        "ImTableNextColumn",
        &_ImGui_TableNextColumn
    );

    state->set_function(
        "ImTableSetupColumn",
        &_ImGui_TableSetupColumn
    );

    state->set_function(
        "ImTableHeadersRow",
        &_ImGui_TableHeadersRow
    );

    state->set_function(
        "ImTreeNode",
        &_ImGui_TreeNode_V1
    );

    state->set_function(
        "ImTreePop",
        &ImGui::TreePop
    );

    state->set_function(
        "ImCollapsingHeader",
        sol::overload(
            &_ImGui_CollapsingHeader_V1,
            &_ImGui_CollapsingHeader_V2,
            &_ImGui_CollapsingHeader_V3
        )
    );

    state->set_function(
        "ImProgressBar",
        sol::overload(
            &_ImGui_ProgressBar_V2,
            &_ImGui_ProgressBar
        )
    );

    state->set_function(
        "ImBullet",
        &_ImGui_Bullet
    );

    state->set_function(
        "ImBeginListBox",
        &_ImGui_BeginListBox
    );

    state->set_function(
        "ImEndListBox",
        &_ImGui_EndListBox
    );

    #ifdef JILA_IMAGES
    state -> set_function(
        "ImImage",
        &_ImGui_Image
    );

    state -> set_function(
        "ImImageButton",
        sol::overload(
            &_ImGui_ImageButton_V1
        )
    );
    #endif

    state -> set_function(
        "ImSetTooltip",
        &_ImGui_SetTooltip
    );

    state -> set_function(
        "ImSetItemTooltip",
        &_ImGui_SetItemTooltip
    );
}

}
