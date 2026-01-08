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
    Scope.ParamsCount = 0

    ---@type table<number, [CharProperty, CharProperty]>
    Scope.Params = {}
    Scope.Response = "None"
end

---@param number number
function RenderOneParam(number)
    TableNextColumn()
    InputText("##param-" .. number .. "key", Scope.Params[number][1])
    TableNextColumn()
    InputText("##param-" .. number .. "value", Scope.Params[number][2])
    TableNextColumn()

    if Button(ICON_FA_X .. "##param-" .. number) then
        table.remove(Scope.Params, number)
        Scope.ParamsCount = Scope.ParamsCount - 1
    end
end

function RenderParams()
    local i = 0

    while i < Scope.ParamsCount do
        RenderOneParam(i + 1)
        i = i + 1
    end
end

---@return table
function GetParamsAsTable()
    local tbl = {}

    for k, v in pairs(Scope.Params) do
        tbl[v[1].str] = v[2].str
    end

    return tbl
end

---@param time number
function M.Render(time)
    SetNextWindowPos(Create_ImVec2())
    SetNextWindowSize(Scope.WindowSize)
    Begin("HTTP API")

    Text("Params count: " .. tostring(Scope.ParamsCount))

    if BeginTable("Params", 3) then
        TableSetupColumn("Key")
        TableSetupColumn("Value")
        TableSetupColumn("Delete?")
        TableHeadersRow()

        RenderParams()

        EndTable()
    end

    if Button("ADD PARAM", Create_ImVec2(Scope.WindowSize.x - 10, 25)) then
        Scope.ParamsCount = Scope.ParamsCount + 1

        Scope.Params[Scope.ParamsCount] = {
            Create_Char_Property(), -- key
            Create_Char_Property()  -- value
        }
    end

    if Button("POST", Create_ImVec2(Scope.WindowSize.x - 10, 25)) then
        local res = Post(
            "http://www.httpbin.org/post",
            json.encode(GetParamsAsTable())
        )
        local res_json = json.decode(res.text)
        Scope.Response = res.text .. "\nJSON: " .. json.encode(res_json["data"])
    end

    Separator("Response: ")
    TextWrapped(Scope.Response)

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
