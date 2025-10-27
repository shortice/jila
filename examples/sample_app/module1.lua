local M = {}

M.name = "main"
M.version = 0.1

-- Current - Max

Prop = CharProperty.new(50)

IntValue = IntProperty.new(42)
FloatValue = FloatProperty.new(3.14)
BoolValue = BoolProperty.new(true)
ColorValue = ImVec4.new(1.0, 0.5, 0.2, 1.0)
ProgressValue = 0.5

function M.Begin()

end

function M.End()

end

LastTime = 0
M.Opened = BoolProperty.new(true)
Selected = {}

Title = CharProperty.new(50)
Message = CharProperty.new(50)

function M.BeginMainLoop()
    Scope.WindowSize = SDL_GetWindowSize()
end

function M.Render(time)
    SetNextWindowPos(0, 0)
    SetNextWindowSize(Scope.WindowSize)
    Begin("ImGui Demo", M.Opened)

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
    if InputInt("Integer (InputInt)", IntValue, 1, 10) then
        print("IntValue changed to: " .. tostring(IntValue.value))
    end

    -- FloatProperty
    if SliderFloat("Slider (SliderFloat)", FloatValue, 0.0, 1.0, "%.2f") then
        print("FloatValue changed to: " .. tostring(FloatValue.value))
    end

    if DragFloat("Drag Float", FloatValue, 0.01, 0.0, 100.0) then
        print("FloatValue changed to: " .. tostring(FloatValue.value))
    end

    -- Color pickers
    if ColorEdit3("3-color (ColorEdit3)", ColorValue) then
        print("Color changed!")
    end

    if ColorEdit4("4-color (ColorEdit4)", ColorValue, ImGuiColorEditFlags_NoInputs) then
        print("4-color changed!")
    end

    Separator("Progress bar and styles")

    -- Progress bar
    ProgressBar(ProgressValue, ImVec2.new(200, 30))
    SameLine()
    Text("Progress: " .. tostring(ProgressValue))

    Bullet()
    Text("Bullet point")

    SameLine()

    -- Информация о окне
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

    if IsMouseDown(ImGuiMouseButton_Left) then
        local mousePos = GetMousePos()
        Text("Left mouse click pos: " .. tostring(mousePos.x) .. ", " .. tostring(mousePos.y))
    end

    ProgressValue = (ProgressValue + 0.001) % 1.0

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
