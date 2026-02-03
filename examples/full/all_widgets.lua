---
--- @type Module
local M = {
    name = "all_widgets",
    version = 0.1
}

-- Data for widgets will be stored in Scope
function M.Begin()
    Scope.check_prop = Create_Bool_Property(false)
    Scope.int_prop = Create_Int_Property(10)
    Scope.float_prop = Create_Float_Property(0.5)
    Scope.char_prop = Create_Char_Property("Hello Jila!")
    Scope.multiline_prop = Create_Char_Property("Line 1\nLine 2\nLine 3")
    Scope.color_vec4 = Create_ImVec4(1.0, 0.0, 0.0, 1.0)
    Scope.progress_prop = Create_Float_Property(0.0)
    Scope.combo_selected = Create_Bool_Property(false)
    Scope.selectable_bool = Create_Bool_Property(false)
    Scope.texture = nil --- TODO: <-
    Scope.demo_window_display = Create_Bool_Property(false)
    Scope.debug_window_display = Create_Bool_Property(false)

    Scope.opened_modal = Create_Bool_Property(false)
end

function M.End() end

function M.Render(time)
    -- Update progress bar for demo
    Scope.progress_prop.value = (time % 5.0) / 5.0

    if ImBeginTabBar("MainTabs") then

        -- SECTION 1: BASIC WIDGETS (c_widgets.lua)
        if ImBeginTabItem("Basic Widgets") then
            ImText("This is ImText")
            ImTextWrapped("This is ImTextWrapped, which will wrap when it reaches the edge of the window or container.")

            if ImButton("ImButton") then
                print("Button clicked!")
            end
            ImSameLine()
            ImButton("Sized Button", Create_ImVec2(120, 40))

            ImCheckbox("ImCheckbox", Scope.check_prop)

            ImBullet()
            ImText("ImBullet used here")

            ImSeparator()

            ImProgressBar(Scope.progress_prop, Create_ImVec2(-1, 0))

            if ImCollapsingHeader("Collapsing Header") then
                ImText("Content inside collapsing header")
                ImBullet()
                ImText("More content")
            end

            if ImTreeNode("Tree Node") then
                ImText("Tree content")
                if ImTreeNode("Sub Node") then
                    ImText("Sub content")
                    ImTreePop()
                end
                ImTreePop()
            end

            ImEndTabItem()
        end

        -- SECTION 2: INPUTS (c_input.lua)
        if ImBeginTabItem("Inputs") then
            ImInputText("ImInputText", Scope.char_prop)
            ImInputTextMultiline("ImInputTextMultiline", Scope.multiline_prop, Create_ImVec2(-1, 100))

            ImSeparator()

            ImInputInt("ImInputInt", Scope.int_prop)
            ImSliderInt("ImSliderInt", Scope.int_prop, 0, 100)

            ImSeparator()

            ImDragFloat("ImDragFloat", Scope.float_prop)
            ImSliderFloat("ImSliderFloat", Scope.float_prop, 0.0, 1.0)

            ImSeparator()

            ImColorEdit3("ImColorEdit3", Scope.color_vec4)
            ImColorEdit4("ImColorEdit4", Scope.color_vec4)

            ImEndTabItem()
        end

        -- SECTION 3: SELECTIONS & MENUS (c_widgets.lua)
        if ImBeginTabItem("Selections & Menus") then

            ImText("Selectables:")
            ImSelectable("ImSelectable", Scope.selectable_bool)
            ImSelectableText("ImSelectableText (Label)", Scope.char_prop, Create_ImVec2(0, 0))

            ImSeparator()

            if ImBeginCombo("ImBeginCombo", "Preview Text") then
                if ImSelectable("Option 1", Scope.combo_selected) then end
                if ImSelectable("Option 2", Scope.combo_selected) then end
                ImEndCombo()
            end

            ImSeparator()

            ImText("ListBox:")
            if ImBeginListBox("ImListBox") then
                ImSelectable("Item 1", Scope.selectable_bool)
                ImSelectable("Item 2", Scope.combo_selected)
                ImEndListBox()
            end

            ImSeparator("Menu: ")

            if ImBeginMenuBar() then
                if ImBeginMenu("Menu") then
                    if ImMenuItem("Open") then end
                    if ImMenuItem("Save", "Ctrl+S", Create_Bool_Property(false)) then end
                    ImEndMenu()
                end

                ImEndMenuBar()
            end

            ImEndTabItem()
        end

        -- SECTION 4: TABLES (c_widgets.lua)
        if ImBeginTabItem("Tables") then
            if ImBeginTable("DemoTable", 3) then
                ImTableSetupColumn("ID")
                ImTableSetupColumn("Name")
                ImTableSetupColumn("Value")
                ImTableHeadersRow()

                for i = 1, 3 do
                    ImTableNextRow()
                    ImTableNextColumn()
                    ImText(tostring(i))
                    ImTableNextColumn()
                    ImText("Item " .. i)
                    ImTableNextColumn()
                    ImText(tostring(i * 10))
                end
                ImEndTable()
            end
            ImEndTabItem()
        end

        -- SECTION 5: UTILS & MODALS (c_utils.lua & c_widgets.lua)
        if ImBeginTabItem("Utils & Modals") then
            if ImButton("Open Modal") then
                ImOpenPopup("Modal Window")
                Scope.opened_modal.value = true
            end

            if ImBeginModal("Modal Window", Scope.opened_modal) then
                ImText("This is a modal window.")
                if ImButton("Close") then
                    Scope.opened_modal.value = false
                end
                ImEndModal()
            end

            ImSeparator("Labeled Separator")

            if Scope.demo_window_display.value then
                ImShowDemoWindow()
            end

            if ImButton("Show Demo Window") then
                if Scope.demo_window_display.value then
                    Scope.demo_window_display.value = false
                else
                    Scope.demo_window_display.value = true
                end
            end

            if Scope.debug_window_display.value then
                ImShowMetricsWindow()
            end

            ImSameLine()

            if ImButton("Show Metrics Window") then
                if Scope.debug_window_display.value then
                    Scope.debug_window_display.value = false
                else
                    Scope.debug_window_display.value = true
                end
            end

            ImSeparator()

            ImText("ImCalcTextSize for 'Hello Jila!': x=" .. tostring(ImCalcTextSize("Hello Jila!").x) .. " y=" .. tostring(ImCalcTextSize("Hello Jila!").y))

            ImSeparator()

            ImText("Scroll When Dragging demo (drag mouse with button held):")
            ImScrollWhenDragging()

            ImEndTabItem()
        end

        -- SECTION 6: IMAGES (c_widgets.lua)
        if ImBeginTabItem("Images") then
            if Scope.texture then
                ImText("ImImage:")
                ImImage(Scope.texture, Create_ImVec2(128, 128))

                ImSeparator()

                ImText("ImImageButton:")
                if ImImageButton("ImageBtn", Scope.texture, Create_ImVec2(64, 64)) then
                    print("Image button clicked!")
                end
            else
                ImText("Texture not loaded.")
            end
            ImEndTabItem()
        end

        -- SECTION 7: MAIN MENU BAR (c_widgets.lua)
        if ImBeginTabItem("Main Menu Bar") then
            ImText("Look at the very top of the window (if not hidden) to see the Main Menu Bar demo.")
            if ImBeginMainMenuBar() then
                if ImBeginMenu("Jila Demo") then
                    if ImMenuItem("Item 1") then end
                    if ImMenuItem("Item 2", Create_Bool_Property(true)) then end -- Using BoolProperty
                    ImEndMenu()
                end
                ImEndMainMenuBar()
            end
            ImEndTabItem()
        end

        ImEndTabBar()
    end
end

return M
