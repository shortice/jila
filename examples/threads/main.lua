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
    Scope.Int = "0"
    Scope.Running = false
end

function Lol()
    local i = 1

    while i < 999999 do
        i = i + 1
        Jila_PushThreadMessage("Lol", i)
        Jila_Sleep(0.1)
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
    ImText(Scope.Int)

    ImEnd()
end

---@param event Jila_Event
function M.Event(event)
    if event.type == Jila_EventType.Jila_EVENT_WINDOW_PIXEL_SIZE_CHANGED then
        Scope.WindowSize.x = event.window.data1
        Scope.WindowSize.y = event.window.data2
    end

    if event.type == Jila_EventType.Jila_EVENT_USER then
        if event.user.code == 1002 then
            local th = Jila_GetThreadMessage(event.user)

            Scope.Int = tostring(th.var)
        end
    end
end

return M -- Required!!!
