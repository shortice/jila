#include "imgui.h"
#include "imgui_internal.h"
#include "components/imgui/c_io.hpp"

namespace Jila {

static std::string_view selectedText;

// Called every frame multiple times (Input/SelectableText function count 
// + 1 for reset state every frame)
void UpdateSelectedText(std::string_view currentText) {
    if (currentText.empty()) {
        selectedText = {};
        return;
    }

    ImGuiContext& g = *GImGui;

    if (g.ActiveId == 0 || g.ActiveId != g.LastItemData.ID) {
        return;
    }

    ImGuiInputTextState* state = ImGui::GetInputTextState(g.ActiveId);

    if (!state) return;

    if (!state->HasSelection()) return;
    
    int start_select = state->GetSelectionStart();
    int end_select = state->GetSelectionEnd();

    if (start_select == end_select) return;

    // Ensure start < end
    if (start_select > end_select) {
        int temp = start_select;
        start_select = end_select;
        end_select = temp;
    }

    if (selectedText.size() == (size_t)(end_select - start_select)) {
        return;
    }

    selectedText = currentText.substr(
        start_select, end_select - start_select
    );
}

void bindImIO(sol::state* state) {
    state->set_function(
        "GetClipboardText",
        []() {
            return (std::string_view)ImGui::GetClipboardText();
        }
    );

    state->set(
        "GetSelectedText",
        []() {
        	return selectedText;
        }
    );
}

}
