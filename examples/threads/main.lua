--- @type Module
local M = {
    name = "main",
    version = 0.1
}

Scope.Int = "0"
Scope.Running = false

function M.Begin()

end

function M.End()

end

function M.BeginMainLoop()
    Scope.WindowSize = SDL_GetWindowSize()
end

function Lol()
    local i = 1

    while i < 999999 do
        i = i + 1
        PushThreadMessage("Lol", i)
        SDL_Delay(0.1)
    end
end

function M.Render(time)
    SetNextWindowPos(0, 0)
    SetNextWindowSize(Scope.WindowSize)
    Begin("Threads")

    if Button("Start thread") then
        if Scope.Running == false then
            Go(Lol, "Lol")

            Scope.Running = true
        end
    end

    Separator("Result in thread:")
    Text(Scope.Int)

    End()
end

---@param event SDL_Event
function M.Event(event)
    if event.type == SDL_EventType.SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED then
        Scope.WindowSize.x = event.window.data1
        Scope.WindowSize.y = event.window.data2
    end

    if event.type == SDL_EventType.SDL_EVENT_USER then
        if event.user.code == 1002 then
            local th = GetThreadMessage(event.user)

            Scope.Int = tostring(th.var)
        end
    end
end

return M -- Required!!!
