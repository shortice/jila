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
    Scope.Running = false
    Scope.MyValue = SharedScope_CreateC("myvar", "")
end

function Lol()
    local m = 0
    local i = SharedScope_GetC("myvar")

    if i == nil then return end

    while m < 999999 do
        m = m + 1
        i.value = i.value .. tostring(m)
        Jila_Sleep(300)
    end
end

function M.Render(time)
    ImSetNextWindowPos(0, 0)
    ImSetNextWindowSize(Scope.WindowSize)
    ImBegin("Threads")

    if ImButton("Start thread") then
        if Scope.Running == false then
            Jila_Go(Lol, "Lol")
            Scope.Running = true
        end
    end

    ImSeparator("Result in thread:")
    ImTextWrapped(Scope.MyValue.value)

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
