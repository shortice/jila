---
--- @type Module
local M = {
    name = "threads",
    version = 0.1
}

function M.Begin()
    Scope.Int = SharedScope_CreateI("myvar", 1)
    Scope.Running = false
end

function M.End() end

function Lol()
    local i = SharedScope_GetI("myvar")

    if i == nil then
        return
    end

    print(Scope.Dwdwdwd + 131)

    while i.value < 99 do
        i.value = i.value + 2
        Jila_Sleep(200)
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
    ImText(tostring(Scope.Int.value))
end

return M -- Required!!!

