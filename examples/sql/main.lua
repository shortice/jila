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
    Scope.Code = Create_Char_Property()
    Scope.Sql = Jila_Data_Connect("./data.db")
    Scope.Err = "Nothing"
end

function M.Render(time)
    ImSetNextWindowPos(0, 0)
    ImSetNextWindowSize(Scope.WindowSize)
    ImBegin("Sqlite3 sample")

    ImSeparator()
    ImInputTextMultiline("##SQL_query", Scope.Code)

    if ImButton("Send query") then
        if Jila_Data_Exec(Scope.Sql, Scope.Code.str) == false then
            Scope.Err = Jila_GetError()
        else
            Scope.Err = "Nothing"
        end
    end

    ImSeparator("Error: ")
    ImTextWrapped(Scope.Err)

    local m = Scope.Sql.objects

    ImSeparator("Query output (" .. #m .. "):")

    for l, v in pairs(m) do
        ImText(v[1] .. " = " .. v[2])
    end

    ImEnd()
end

function M.Event(event)
    if event.type == Jila_EventType.Jila_EVENT_WINDOW_PIXEL_SIZE_CHANGED then
        Scope.WindowSize.x = event.window.data1
        Scope.WindowSize.y = event.window.data2
    end
end

return M
