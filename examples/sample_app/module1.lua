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
    Scope.WindowSize = SDL_GetWindowSize()

    Scope.Prop = Create_Char_Property()

    Scope.IntValue = Create_Int_Property(42)
    Scope.FloatValue = Create_Float_Property(3.14)
    Scope.BoolValue = Create_Bool_Property(true)
    Scope.ColorValue = Create_ImVec4(1.0, 0.5, 0.2, 1.0)
    Scope.ProgressValue = Create_Float_Property(0.5)
    Scope.Opened = Create_Bool_Property(true)
end

function M.Render(time)
    SetNextWindowPos(0, 0)
    SetNextWindowSize(Scope.WindowSize)
    Begin("ImGui Demo", Scope.Opened)

    Separator("Basic widgets")

    -- TreeNode и CollapsingHeader
    if TreeNode("Tree and collapsible") then
        Text("Test")
        if CollapsingHeader("Collapsing Header") then
            Text("Test")
        end

        TreePop()
    end

    -- InputInt
    if InputInt("Integer (InputInt)", Scope.IntValue, 1, 10) then
        if Scope.IntValue.value > 1000 then
            Scope.IntValue.value = 1000
        end

        if Scope.IntValue.value < -1000 then
            Scope.IntValue.value = -1000
        end

        print("IntValue changed to: " .. tostring(Scope.IntValue.value))
    end

    -- FloatProperty
    if SliderFloat("Slider (SliderFloat)", Scope.FloatValue, 0.0, 100, "%.2f") then
        if Scope.FloatValue.value > 100 then
            Scope.FloatValue.value = 100
        end

        if Scope.FloatValue.value < 0 then
            Scope.FloatValue.value = 0.0
        end

        print("FloatValue changed to: " .. tostring(Scope.FloatValue.value))
    end

    if DragFloat("Drag Float", Scope.FloatValue, 0.01, 0.0, 100) then
        if Scope.FloatValue.value > 100 then
            Scope.FloatValue.value = 100
        end

        if Scope.FloatValue.value < 0 then
            Scope.FloatValue.value = 0.0
        end

        print("FloatValue changed to: " .. tostring(Scope.FloatValue.value))
    end

    -- Color pickers
    if ColorEdit3("3-color (ColorEdit3)", Scope.ColorValue) then
        print("Color changed!")
    end

    if ColorEdit4("4-color (ColorEdit4)", Scope.ColorValue, ImGuiColorEditFlags_NoInputs) then
        print("4-color changed!")
    end

    Separator("Progress bar and styles")

    -- Progress bar
    ProgressBar(Scope.ProgressValue, Create_ImVec2(200, 30))
    SameLine()
    Text("Progress: " .. tostring(Scope.ProgressValue.value))

    Bullet()
    Text("Bullet point")

    SameLine()

    local windowSize = GetWindowSize()
    local windowPos = GetWindowPos()
    Text("Widnow size: " .. tostring(windowSize.x) .. ", " .. tostring(windowSize.y))
    Text("Window pos: " .. tostring(windowPos.x) .. ", " .. tostring(windowPos.y))

    local availSpace = GetContentRegionAvail()
    Text("Available space: " .. tostring(availSpace.x) .. ", " .. tostring(availSpace.y))

    Separator("Input")
    if IsKeyPressed(ImGuiKey_Space) then
        Text("Typing space!")
    end

    if BeginListBox("Test") then
        for i = 1, 10, 1 do
            if Selectable("Test##" .. tostring(i), Scope.BoolValue) then
                print("Hello", i)
            end
        end

        ScrollWhenDragging()
        EndListBox()
    end

    if IsMouseDown(ImGuiMouseButton_Left) then
        local mousePos = GetMousePos()
        Text("Left mouse click pos: " .. tostring(mousePos.x) .. ", " .. tostring(mousePos.y))
    end

    Scope.ProgressValue.value = (Scope.ProgressValue.value + 0.001) % 1.0

    ScrollWhenDragging()
    End()
end

---@param event SDL_Event
function M.Event(event)
    if event.type == SDL_EventType.SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED then
        Scope.WindowSize.x = event.window.data1
        Scope.WindowSize.y = event.window.data2
    end
end

return M -- Required!!!
