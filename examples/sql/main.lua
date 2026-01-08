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
    Scope.Code = Create_Char_Property()
    Scope.Sql = Data_Connect("./data.db")
    Scope.Err = "Nothing"
end

function M.Render(time)
    SetNextWindowPos(0, 0)
    SetNextWindowSize(Scope.WindowSize)
    Begin("Sqlite3 sample")

    Separator()
    InputTextMultiline("##SQL_query", Scope.Code)

    if Button("Send query") then
        if Data_Exec(Scope.Sql, Scope.Code.str) == false then
            Scope.Err = SDL_GetError()
        else
            Scope.Err = "Nothing"
        end
    end

    Separator("Error: ")
    TextWrapped(Scope.Err)

    local m = Scope.Sql.objects

    Separator("Query output (" .. #m .. "):")

    for l, v in pairs(m) do
        Text(v[1] .. " = " .. v[2])
    end

    End()
end

function M.Event(event)
    if event.type == SDL_EventType.SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED then
        Scope.WindowSize.x = event.window.data1
        Scope.WindowSize.y = event.window.data2
    end
end

return M
