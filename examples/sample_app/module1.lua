--- @type Module
local M = {
    name = "main",
    version = 0.1
}

function M.Begin()

end

function M.End()

end

function M.BeginMainLoop()
    Scope.WindowSize = Jila_GetWindowSize()

    Scope.Prop = Create_Char_Property()

    Scope.IntValue = Create_Int_Property(42)
    Scope.FloatValue = Create_Float_Property(3.14)
    Scope.BoolValue = Create_Bool_Property(true)
    Scope.ColorValue = Create_ImVec4(1.0, 0.5, 0.2, 1.0)
    Scope.ProgressValue = Create_Float_Property(0.5)
    Scope.Opened = Create_Bool_Property(true)
end

function M.Render(time)
    ImSetNextWindowPos(0, 0)
    ImSetNextWindowSize(Scope.WindowSize)
    ImBegin("ImGui Demo", Scope.Opened)

    ImSeparator("Basic widgets")

    -- TreeNode и CollapsingHeader
    if ImTreeNode("Tree and collapsible") then
        ImText("Test")
        if ImCollapsingHeader("Collapsing Header") then
            ImText("Test")
        end

        ImTreePop()
    end

    -- InputInt
    if ImInputInt("Integer (InputInt)", Scope.IntValue, 1, 10) then
        if Scope.IntValue.value > 1000 then
            Scope.IntValue.value = 1000
        end

        if Scope.IntValue.value < -1000 then
            Scope.IntValue.value = -1000
        end

        print("IntValue changed to: " .. tostring(Scope.IntValue.value))
    end

    -- FloatProperty
    if ImSliderFloat("Slider (SliderFloat)", Scope.FloatValue, 0.0, 100, "%.2f") then
        if Scope.FloatValue.value > 100 then
            Scope.FloatValue.value = 100
        end

        if Scope.FloatValue.value < 0 then
            Scope.FloatValue.value = 0.0
        end

        print("FloatValue changed to: " .. tostring(Scope.FloatValue.value))
    end

    if ImDragFloat("Drag Float", Scope.FloatValue, 0.01, 0.0, 100) then
        if Scope.FloatValue.value > 100 then
            Scope.FloatValue.value = 100
        end

        if Scope.FloatValue.value < 0 then
            Scope.FloatValue.value = 0.0
        end

        print("FloatValue changed to: " .. tostring(Scope.FloatValue.value))
    end

    -- Color pickers
    if ImColorEdit3("3-color (ColorEdit3)", Scope.ColorValue) then
        print("Color changed!")
    end

    if ImColorEdit4("4-color (ColorEdit4)", Scope.ColorValue, ImGuiColorEditFlags_NoInputs) then
        print("4-color changed!")
    end

    ImSeparator("Progress bar and styles")

    -- Progress bar
    ImProgressBar(Scope.ProgressValue, Create_ImVec2(200, 30))
    ImSameLine()
    ImText("Progress: " .. tostring(Scope.ProgressValue.value))

    ImBullet()
    ImText("Bullet point")

    ImSameLine()

    local windowSize = ImGetWindowSize()
    local windowPos = ImGetWindowPos()
    ImText("Widnow size: " .. tostring(windowSize.x) .. ", " .. tostring(windowSize.y))
    ImText("Window pos: " .. tostring(windowPos.x) .. ", " .. tostring(windowPos.y))

    local availSpace = ImGetContentRegionAvail()
    ImText("Available space: " .. tostring(availSpace.x) .. ", " .. tostring(availSpace.y))

    ImSeparator("Input")
    if ImIsKeyPressed(ImGuiKey_Space) then
        ImText("Typing space!")
    end

    if ImBeginListBox("Test") then
        for i = 1, 10, 1 do
            if ImSelectable("Test##" .. tostring(i), Scope.BoolValue) then
                print("Hello", i)
            end
        end

        ImScrollWhenDragging()
        ImEndListBox()
    end

    if ImIsMouseDown(ImGuiMouseButton_Left) then
        local mousePos = ImGetMousePos()
        ImText("Left mouse click pos: " .. tostring(mousePos.x) .. ", " .. tostring(mousePos.y))
    end

    Scope.ProgressValue.value = (Scope.ProgressValue.value + 0.001) % 1.0

    ImScrollWhenDragging()
    ImEnd()
end

---@param event Jila_Event
function M.Event(event)
    if event.type == Jila_EventType.Jila_EVENT_WINDOW_PIXEL_SIZE_CHANGED then
        Scope.WindowSize.x = event.window.data1
        Scope.WindowSize.y = event.window.data2
    end
end

return M -- Required!!!
