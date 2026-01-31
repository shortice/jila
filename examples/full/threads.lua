---
--- @type Module
local M = {
    name = "threads",
    version = 0.1
}

function M.Begin()
    Scope.Int = "0"
    Scope.Running = false
end

function M.End() end

function Lol()
    local i = 1

    while i < 99 do
        i = i + 2
        Jila_PushThreadMessage("Lol", i)
        Jila_Sleep(2)
    end
end

function M.Render(time)
    if ImButton("Start thread") then
        if Scope.Running == false then
            Jila_Go(Lol, "Lol")

            Scope.Running = true
        end
    end

    ImSeparator("Result in thread:")
    ImText(Scope.Int)
end

function M.Event(event)
    if event.type == Jila_EventType.Jila_EVENT_USER then
        if event.user.code == 1002 then
            local th = Jila_GetThreadMessage(event.user)

            Scope.Int = tostring(th.var)
        end
    end
end

return M -- Required!!!

