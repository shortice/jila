#include "imgui.h"
#include "imgui_internal.h"
#include "components/imgui/c_io.hpp"

namespace Jila {

static std::string selectedText;

// Called every frame multiple times (Input/SelectableText function count 
// + 1 for reset state every frame)
void UpdateSelectedText(std::string_view currentText) {
    // TODO: Try change logic to avoid copying
    if (currentText.empty()) {
        selectedText.clear();
        return;
    }

    ImGuiContext& g = *GImGui;

    ImGuiInputTextState* state = ImGui::GetInputTextState(g.ActiveId);

    if (!state) return;

    if (!state->HasSelection()) return;

    int start_select = state->GetSelectionEnd();
    int end_select = state->GetSelectionStart();

    if (start_select == end_select) return;

    // Because may (start > end)
    // see: imstb_textedit.h file comments in STB_TexteditState struct 
    // select_start/select_end fields
    // [END]            [START]
    if (start_select > end_select) {
        int temp = start_select;

        start_select = end_select;
        end_select = temp;
        // [START]      [END]
    }

    selectedText = currentText.substr(
        start_select, end_select - start_select
    );
}

void bindImIO(sol::state* state) {
    state->set_function(
        "GetClipboardText",
        []() {
            (std::string_view)ImGui::GetClipboardText();
        }
    );

    state->set(
        "GetSelectedText",
        []() {
            return std::string_view(
                selectedText.data()
            );
        }
    );
}

}
