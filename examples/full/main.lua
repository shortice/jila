--- All functions demo.
---
--- @type Module
local M = {
    name = "main",
    version = 0.1
}

function M.Begin()
    Scope.Error = Create_Char_Property()
end

function M.End()

end

function M.BeginMainLoop()
    Scope.WindowSize = Jila_GetWindowSize()
end

function M.Render(time)
    ImSetNextWindowSize(
        Create_ImVec2(
            Scope.WindowSize.x,
            Scope.WindowSize.y - 28
        )
    )
    ImSetNextWindowPos(Create_ImVec2(0, 28))
    ImBegin(
        "All function demo!",
        ImGuiWindowFlags_MenuBar
    )

    ImText("If sometimes wrong click here")

    if ImButton("Get error") then
        Scope.Error.str = Jila_GetError()
    end

    ImSeparator("Current error: ")
    ImTextWrapped(Scope.Error.str)

    if ImCollapsingHeader("All widgets") then
        Jila_GetModule("all_widgets").Render(time)
    end

    if ImCollapsingHeader("Sdl powered stuff +custom") then
        Jila_GetModule("sdl").Render(time)
    end

    if ImCollapsingHeader("Threads") then
        Jila_GetModule("threads").Render(time)
    end

    if ImCollapsingHeader("DataBase") then
        Jila_GetModule("database").Render(time)
    end

    if ImCollapsingHeader("Network") then
        Jila_GetModule("network").Render(time)
    end

    if ImCollapsingHeader("Information") then
        Jila_GetModule("information").Render(time)
    end

    ImScrollWhenDragging()
    ImEnd()
end

---@param event Jila_Event
function M.Event(event)
    if event.type == Jila_EventType.Jila_EVENT_WINDOW_PIXEL_SIZE_CHANGED then
        Scope.WindowSize.x = event.window.data1
        Scope.WindowSize.y = event.window.data2
    end

    Jila_GetModule("threads").Event(event)
    Jila_GetModule("sdl").Event(event)
end

return M -- Required!!!

